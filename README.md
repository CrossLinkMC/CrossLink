# CrossLink

面向 Minecraft Bedrock 的**数据包转发网关**：客户端只连接 CrossLink，CrossLink 为每个玩家维护一条到当前后端 BDS 的连接，在玩家跨服时替换这条后端连接，而客户端的会话、UDP 五元组和 UI 状态保持不变。

拓扑是**一个大厅 + N 个子服**。CrossLink 本体**只做协议包转发**，不含任何业务逻辑；无缝跨服传送由插件实现（见 [CrossLinkTransfer](../CrossLinkTransfer)）。

## 设计边界

| 组件 | 职责 |
| --- | --- |
| `crosslink_core.dll` | 前端监听、每玩家后端 leg、双腿独立终止 DTLS 与压缩、路由、包管线、控制通道、DLL 插件宿主。这也是插件的**稳定 ABI 边界** |
| `crosslink.exe` | 命令行入口，装配配置、插件与监听 |
| `plugins/<name>/` | 插件目录，每个插件一个 `manifest.json` + DLL |
| BDS 侧 LeviLamina 插件 | 通过 TCP/JSON Lines 控制通道与网关协作：冻结玩家、保存并释放、恢复状态 |

## 模块

- **协议层** — 统一的包基类 `crosslink::proto::Packet`：始终以完整序列化形式持有自身，转发不需要重新编码；需要特殊处理的包各自拆成一组 `.hpp/.cpp`（Login、StartGame、ChangeDimension、Respawn、加载屏、资源包、区块、runtime id 族……）。编解码表 `PacketCodecs` 可由插件注册或替换。
- **传输层** — `net::Transport` / `Connection` / `InboundListener` 抽象，实现是 `bedrock-nethernet`（Minecraft 自 26.60 起强制）。NetherNet 即 WebRTC：TCP 上的 HTTP 信令（`GET /v1/join` 探测、`POST /v1/join/{networkId}` 交换 SDP）加 ICE/DTLS/SCTP 两条数据通道。ICE/DTLS/SCTP 由 libdatachannel 承担，信令、SDP 的 `a=identity` 断言、NetherNet 分片帧与 Bedrock 批处理层在 `src/net/nethernet/` 与 `src/proto/BatchCodec.cpp`。DTLS 之外，BDS 1.26.60 **仍然跑 Bedrock 自己的加密握手**，网关照常双腿独立终止。路由、会话、插件 API 与插件本身都不感知传输实现。
- **身份绑定** — NetherNet 下 SDP 的 `a=identity` 与 Login 里的客户端公钥必须是**同一把密钥**，否则后端认为一个玩家有两个身份而拒绝登录。`Transport::identityKeyPair()` 暴露传输层的长期身份密钥，`GatewaySession` 用它重签 Login。
- **插件系统** — 参照 LeviLamina 的加载模型：manifest 依赖（`dependencies` / `optionalDependencies` / `conflicts` / `loadBefore`，npm 风格版本区间）、拓扑排序 + 环检测、生命周期回调、按插件归属自动回收订阅。插件 DLL 只需导出 `cl_plugin_api_version` 与 `cl_plugin_load`。
- **控制通道** — 常驻 TCP，JSON Lines 分帧，双向请求/应答与通知。宿主只处理 `hello` / `ping`，其余 kind 全部由插件注册。

尚未实现：NetherNet 的 LAN 发现广播（UDP 7551）与 Xbox Live 信令。玩家用「添加服务器」直连网关 IP 时走的是 HTTP 信令，不需要这两者；要在服务器列表里自动出现或走好友联机才需要补。

## 构建

Windows x64、xmake 3.x、MSVC（VS 2026）或 clang-cl。不使用 git submodule：协议编解码以预生成 C++ 的形式 vendored 在 [third_party/bedrock-protocol](third_party/bedrock-protocol/VENDOR.md)（构建不需要 Python），其余依赖全部走 xrepo。

```powershell
xmake f -a x64 -m release -p windows -y
xmake -y
```

产物在 `bin/`（`crosslink.exe` + `crosslink_core.dll`）。协议版本默认跟随所 vendored 的编解码提交（2225 / 1.26.60），可用 `--protocol_version=` 与 `--game_version=` 覆盖，CrossLink 不会改写依赖源码。

## 运行

```powershell
copy config\crosslink.example.json config\crosslink.json
:: 把 control.token 换成至少 32 字符的随机串
bin\crosslink.exe --config config\crosslink.json
```

配置为 JSON，含监听地址、大厅标识、子服列表、插件目录、网络参数与控制通道参数，字段说明见 [config/crosslink.example.json](config/crosslink.example.json)。

NetherNet 的端口需求与 RakNet 不同：`network.listenPort` 上跑的是 **TCP** HTTP 信令，媒体走 ICE 协商出的 **UDP** 端口（范围由 `nethernet.icePortBegin/icePortEnd` 决定，默认 1024–65535）。防火墙要同时放行这两者；只放 UDP 19132 会让客户端连不上。首次启动会在 `nethernet.identityKeyFile` 生成一把长期 P-384 身份密钥，用于给 SDP 的 `a=identity` 断言签名——删掉它等于换了一个网关身份。

后端 BDS 需要 `online-mode=false`，并且建议 `client-side-chunk-generation-enabled=false`；玩家只应能访问网关端口，后端游戏端口用防火墙限制在网关所在网段。

## 用到的项目

- [EndstoneMC/bedrock-protocol](https://github.com/EndstoneMC/bedrock-protocol)（MIT）：协议编解码，vendored 于 `third_party/`
- [libdatachannel](https://github.com/paullouisageneau/libdatachannel)（MPL-2.0）及其后端 libjuice（MPL-2.0）、usrsctp（BSD-3-Clause）：NetherNet 的 ICE/DTLS/SCTP/DCEP
- xmake / xrepo：openssl3、zlib、snappy、magic_enum、fmt、nlohmann_json
- [LiteLDev/LeviLamina](https://github.com/LiteLDev/LeviLamina)：插件加载模型的参照，以及 BDS 侧插件的宿主
- [Mojang bedrock-protocol-docs](https://github.com/Mojang/bedrock-protocol-docs)、[CloudburstMC/Network](https://github.com/CloudburstMC/Network)（Apache-2.0，nethernet 分支）、[WaterdogPE](https://github.com/WaterdogPE/WaterdogPE)：NetherNet 与跨服思路参考

## 许可证

MIT。第三方依赖仍遵循各自许可证，分发二进制时请一并保留其声明。

注意 libdatachannel 与 libjuice 是 **MPL-2.0**（文件级 copyleft）：它们可以静态链接进 MIT 二进制，但分发时需要一并给出这些 MPL 文件的源码（或获取方式），并保留其声明。CrossLink 自己的源码不受影响。
