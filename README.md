# CrossLink

面向 Minecraft Bedrock 的**数据包转发网关**：客户端只连接 CrossLink，CrossLink 为每个玩家维护一条到当前后端 BDS 的连接，在玩家跨服时替换这条后端连接，而客户端的会话、UDP 五元组和 UI 状态保持不变。

拓扑是**一个大厅 + N 个子服**。CrossLink 本体**只做协议包转发**，不含任何业务逻辑；无缝跨服传送由插件实现（见 [CrossLinkTransfer](../CrossLinkTransfer)）。

## 设计边界

| 组件 | 职责 |
| --- | --- |
| `crosslink_core.dll` | 前端监听、每玩家后端 leg、双腿独立终止加密与压缩、路由、包管线、控制通道、DLL 插件宿主。这也是插件的**稳定 ABI 边界** |
| `crosslink.exe` | 命令行入口，装配配置、插件与监听 |
| `plugins/<name>/` | 插件目录，每个插件一个 `manifest.json` + DLL |
| BDS 侧 LeviLamina 插件 | 通过 TCP/JSON Lines 控制通道与网关协作：冻结玩家、保存并释放、恢复状态 |

## 模块

- **协议层** — 统一的包基类 `crosslink::proto::Packet`：始终以完整序列化形式持有自身，转发不需要重新编码；需要特殊处理的包各自拆成一组 `.hpp/.cpp`（Login、StartGame、ChangeDimension、Respawn、加载屏、资源包、区块、runtime id 族……）。编解码表 `PacketCodecs` 可由插件注册或替换。
- **传输层** — `net::Transport` / `Connection` / `InboundListener` 抽象，当前实现是 `bedrock-raknet`。Minecraft 自 26.60 起强制 nethernet，届时作为第二种实现接入，路由、会话、插件 API 与插件本身都不需要改动。
- **插件系统** — 参照 LeviLamina 的加载模型：manifest 依赖（`dependencies` / `optionalDependencies` / `conflicts` / `loadBefore`，npm 风格版本区间）、拓扑排序 + 环检测、生命周期回调、按插件归属自动回收订阅。插件 DLL 只需导出 `cl_plugin_api_version` 与 `cl_plugin_load`。
- **控制通道** — 常驻 TCP，JSON Lines 分帧，双向请求/应答与通知。宿主只处理 `hello` / `ping`，其余 kind 全部由插件注册。

## 构建

Windows x64、xmake 3.x、MSVC（VS 2026）或 clang-cl。不使用 git submodule：BedrockProtocol、RakNet、Reflection、JSONC 由 [xmake/deps.lua](xmake/deps.lua) 按固定 commit 拉取到 `.deps/`（首次构建需联网，之后可离线重建），其余依赖走 xrepo。

```powershell
xmake f -a x64 -m release -p windows -y
xmake -y
```

产物在 `bin/`（`crosslink.exe` + `crosslink_core.dll`）。协议版本默认跟随所固定的 BedrockProtocol 提交（1001 / 26.30），可用 `--protocol_version=` 与 `--game_version=` 覆盖，CrossLink 不会改写依赖源码。

## 运行

```powershell
copy config\crosslink.example.json config\crosslink.json
:: 把 control.token 换成至少 32 字符的随机串
bin\crosslink.exe --config config\crosslink.json
```

配置为 JSON，含监听地址、大厅标识、子服列表、插件目录、网络参数与控制通道参数，字段说明见 [config/crosslink.example.json](config/crosslink.example.json)。

后端 BDS 需要 `online-mode=false`，并且建议 `client-side-chunk-generation-enabled=false`；玩家只应能访问网关端口，后端游戏端口用防火墙限制在网关所在网段。

## 用到的项目

- [SculkCatalystMC/BedrockProtocol](https://github.com/SculkCatalystMC/BedrockProtocol)（MPL-2.0）及其依赖 [RakNet](https://github.com/SculkCatalystMC/RakNet)、[Reflection](https://github.com/SculkCatalystMC/Reflection)、[JSONC](https://github.com/SculkCatalystMC/JSONC)
- xmake / xrepo：openssl3、zlib、snappy、cpp-httplib、magic_enum、boost.pfr、fmt、concurrentqueue、parallel-hashmap、nlohmann_json
- [LiteLDev/LeviLamina](https://github.com/LiteLDev/LeviLamina)：插件加载模型的参照，以及 BDS 侧插件的宿主
- [Mojang bedrock-protocol-docs](https://github.com/Mojang/bedrock-protocol-docs)、[WaterdogPE](https://github.com/WaterdogPE/WaterdogPE)：跨服思路参考

## 许可证

MIT。第三方依赖仍遵循各自许可证，分发二进制时请一并保留其声明。
