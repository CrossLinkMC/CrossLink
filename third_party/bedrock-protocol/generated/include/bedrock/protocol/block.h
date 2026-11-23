#pragma once

#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/nbt.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/network.h>

namespace bedrock::protocol {

struct EntityNetId {
    constexpr EntityNetId() = default;
    explicit constexpr EntityNetId(std::uint32_t value) : value_(value) {}
    constexpr operator std::uint32_t() const { return value_; }
    friend constexpr bool operator==(const EntityNetId &, const EntityNetId &) = default;
    friend constexpr auto operator<=>(const EntityNetId &, const EntityNetId &) = default;

  private:
    std::uint32_t value_{};
};

struct RegistryHandle {
    constexpr RegistryHandle() = default;
    explicit constexpr RegistryHandle(std::uint16_t value) : value_(value) {}
    constexpr operator std::uint16_t() const { return value_; }
    friend constexpr bool operator==(const RegistryHandle &, const RegistryHandle &) = default;
    friend constexpr auto operator<=>(const RegistryHandle &, const RegistryHandle &) = default;

  private:
    std::uint16_t value_{};
};

struct BlockPickRequestPacket {
    static constexpr int Id = 34;
    BlockPos pos{};
    bool with_data{};
    std::uint8_t max_slots{};
};

namespace ActorBlockSyncMessage_nested {

enum class MessageId : std::uint32_t {
    None = 0,
    Create = 1,
    Destroy = 2,
};

}  // namespace ActorBlockSyncMessage_nested

struct ActorBlockSyncMessage {
    using MessageId = ActorBlockSyncMessage_nested::MessageId;
};

struct RemoveVolumeEntityPacket {
    static constexpr int Id = 167;
    EntityNetId entity_net_id{};
    DimensionType dimension_type{};
};

struct SerializableCells {
    std::uint8_t x_size{};
    std::uint8_t y_size{};
    std::uint8_t z_size{};
    std::vector<std::uint8_t> storage{};
};

struct SerializableVoxelShape {
    SerializableCells cells{};
    std::vector<float> x_coords{};
    std::vector<float> y_coords{};
    std::vector<float> z_coords{};
};

struct LevelEventPacket {
    static constexpr int Id = 25;
    std::int32_t event_id{};
    Vec3 pos{};
    std::int32_t data{};
};

struct LevelEventGenericPacket {
    static constexpr int Id = 124;
    std::int32_t event_id{};
    CompoundTag data{};
};

struct SpawnParticleEffectPacket {
    static constexpr int Id = 118;
    std::uint8_t vanilla_dimension_id{};
    ActorUniqueID actor_id{};
    Vec3 pos{};
    std::string effect_name{};
    std::optional<std::string> molang_variables{};
};

namespace base {

struct AnvilDamagePacket {
    static constexpr int Id = 141;
    std::int32_t damage{};
    base::NetworkBlockPosition position{};
};

struct UpdateBlockPacket {
    static constexpr int Id = 21;
    base::NetworkBlockPosition pos{};
    BlockRuntimeId runtime_id{};
    std::uint8_t update_flags{};
    std::uint32_t layer{};
};

struct BlockEventPacket {
    static constexpr int Id = 26;
    base::NetworkBlockPosition pos{};
    std::int32_t b0{};
    std::int32_t b1{};
};

struct BlockActorDataPacket {
    static constexpr int Id = 56;
    base::NetworkBlockPosition pos{};
    CompoundTag data{};
};

struct UpdateBlockSyncedPacket {
    static constexpr int Id = 110;
    base::NetworkBlockPosition pos{};
    BlockRuntimeId runtime_id{};
    std::uint8_t update_flags{};
    std::uint32_t layer{};
    ActorUniqueID entity_unique_id{};
    ActorBlockSyncMessage::MessageId message{};
};

struct LecternUpdatePacket {
    static constexpr int Id = 125;
    std::int32_t page{};
    std::int32_t total_pages{};
    base::NetworkBlockPosition pos{};
};

struct OpenSignPacket {
    static constexpr int Id = 303;
    base::NetworkBlockPosition pos{};
    bool is_front_side{};
};

struct UpdateSubChunkNetworkBlockInfo {
    base::NetworkBlockPosition pos{};
    BlockRuntimeId runtime_id{};
    std::uint8_t update_flags{};
    ActorUniqueID entity_unique_id{};
    ActorBlockSyncMessage::MessageId message{};
};

struct UpdateSubChunkBlocksChangedInfo {
    std::vector<base::UpdateSubChunkNetworkBlockInfo> standards{};
    std::vector<base::UpdateSubChunkNetworkBlockInfo> extras{};
};

struct UpdateSubChunkBlocksPacket {
    static constexpr int Id = 172;
    base::NetworkBlockPosition sub_chunk_block_position{};
    base::UpdateSubChunkBlocksChangedInfo blocks_changed{};
};

struct AddVolumeEntityPacket {
    static constexpr int Id = 166;
    EntityNetId entity_net_id{};
    CompoundTag components{};
    std::string json_identifier{};
    std::string instance_name{};
    base::NetworkBlockPosition min_bounds{};
    base::NetworkBlockPosition max_bounds{};
    DimensionType dimension_type{};
    std::string min_engine_version{};
};

}  // namespace base

namespace v748 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v748

namespace v766 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v766

namespace v776 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v776

namespace v786 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v786

namespace v800 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v800

namespace v818 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v818

namespace v827 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v827

namespace v844 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v844

namespace v859 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v859

namespace v898 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

}  // namespace v898

namespace v924 {

using AnvilDamagePacket = base::AnvilDamagePacket;

using UpdateBlockPacket = base::UpdateBlockPacket;

using BlockEventPacket = base::BlockEventPacket;

using BlockActorDataPacket = base::BlockActorDataPacket;

using UpdateBlockSyncedPacket = base::UpdateBlockSyncedPacket;

using LecternUpdatePacket = base::LecternUpdatePacket;

using OpenSignPacket = base::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = base::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = base::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = base::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = base::AddVolumeEntityPacket;

struct VoxelShapesPacket {
    static constexpr int Id = 337;
    std::vector<SerializableVoxelShape> shapes{};
    std::map<std::string, RegistryHandle> name_map{};
};

}  // namespace v924

namespace v944 {

struct AnvilDamagePacket {
    static constexpr int Id = 141;
    std::int32_t damage{};
    BlockPos position{};
};

struct UpdateBlockPacket {
    static constexpr int Id = 21;
    BlockPos pos{};
    BlockRuntimeId runtime_id{};
    std::uint8_t update_flags{};
    std::uint32_t layer{};
};

struct BlockEventPacket {
    static constexpr int Id = 26;
    BlockPos pos{};
    std::int32_t b0{};
    std::int32_t b1{};
};

struct BlockActorDataPacket {
    static constexpr int Id = 56;
    BlockPos pos{};
    CompoundTag data{};
};

struct UpdateBlockSyncedPacket {
    static constexpr int Id = 110;
    BlockPos pos{};
    BlockRuntimeId runtime_id{};
    std::uint8_t update_flags{};
    std::uint32_t layer{};
    ActorUniqueID entity_unique_id{};
    ActorBlockSyncMessage::MessageId message{};
};

struct LecternUpdatePacket {
    static constexpr int Id = 125;
    std::int32_t page{};
    std::int32_t total_pages{};
    BlockPos pos{};
};

struct OpenSignPacket {
    static constexpr int Id = 303;
    BlockPos pos{};
    bool is_front_side{};
};

struct UpdateSubChunkNetworkBlockInfo {
    BlockPos pos{};
    BlockRuntimeId runtime_id{};
    std::uint8_t update_flags{};
    ActorUniqueID entity_unique_id{};
    ActorBlockSyncMessage::MessageId message{};
};

struct UpdateSubChunkBlocksChangedInfo {
    std::vector<v944::UpdateSubChunkNetworkBlockInfo> standards{};
    std::vector<v944::UpdateSubChunkNetworkBlockInfo> extras{};
};

struct UpdateSubChunkBlocksPacket {
    static constexpr int Id = 172;
    BlockPos sub_chunk_block_position{};
    v944::UpdateSubChunkBlocksChangedInfo blocks_changed{};
};

struct AddVolumeEntityPacket {
    static constexpr int Id = 166;
    EntityNetId entity_net_id{};
    CompoundTag components{};
    std::string json_identifier{};
    std::string instance_name{};
    BlockPos min_bounds{};
    BlockPos max_bounds{};
    DimensionType dimension_type{};
    std::string min_engine_version{};
};

struct VoxelShapesPacket {
    static constexpr int Id = 337;
    std::vector<SerializableVoxelShape> shapes{};
    std::map<std::string, RegistryHandle> name_map{};
    std::uint16_t custom_shape_count{};
};

}  // namespace v944

namespace v975 {

using AnvilDamagePacket = v944::AnvilDamagePacket;

using UpdateBlockPacket = v944::UpdateBlockPacket;

using BlockEventPacket = v944::BlockEventPacket;

using BlockActorDataPacket = v944::BlockActorDataPacket;

using UpdateBlockSyncedPacket = v944::UpdateBlockSyncedPacket;

using LecternUpdatePacket = v944::LecternUpdatePacket;

using OpenSignPacket = v944::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = v944::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = v944::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = v944::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = v944::AddVolumeEntityPacket;

using VoxelShapesPacket = v944::VoxelShapesPacket;

}  // namespace v975

namespace v1001 {

using AnvilDamagePacket = v944::AnvilDamagePacket;

using UpdateBlockPacket = v944::UpdateBlockPacket;

using BlockEventPacket = v944::BlockEventPacket;

using BlockActorDataPacket = v944::BlockActorDataPacket;

using UpdateBlockSyncedPacket = v944::UpdateBlockSyncedPacket;

using LecternUpdatePacket = v944::LecternUpdatePacket;

using OpenSignPacket = v944::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = v944::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = v944::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = v944::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = v944::AddVolumeEntityPacket;

using VoxelShapesPacket = v944::VoxelShapesPacket;

}  // namespace v1001

namespace v2168 {

struct AnvilDamagePacket {
    static constexpr int Id = 141;
    BlockPos position{};
};

using UpdateBlockPacket = v944::UpdateBlockPacket;

using BlockEventPacket = v944::BlockEventPacket;

using BlockActorDataPacket = v944::BlockActorDataPacket;

using UpdateBlockSyncedPacket = v944::UpdateBlockSyncedPacket;

using LecternUpdatePacket = v944::LecternUpdatePacket;

using OpenSignPacket = v944::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = v944::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = v944::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = v944::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = v944::AddVolumeEntityPacket;

using VoxelShapesPacket = v944::VoxelShapesPacket;

}  // namespace v2168

namespace v2193 {

using AnvilDamagePacket = v2168::AnvilDamagePacket;

using UpdateBlockPacket = v944::UpdateBlockPacket;

using BlockEventPacket = v944::BlockEventPacket;

using BlockActorDataPacket = v944::BlockActorDataPacket;

using UpdateBlockSyncedPacket = v944::UpdateBlockSyncedPacket;

using LecternUpdatePacket = v944::LecternUpdatePacket;

using OpenSignPacket = v944::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = v944::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = v944::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = v944::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = v944::AddVolumeEntityPacket;

using VoxelShapesPacket = v944::VoxelShapesPacket;

}  // namespace v2193

namespace v2225 {

using AnvilDamagePacket = v2168::AnvilDamagePacket;

using UpdateBlockPacket = v944::UpdateBlockPacket;

using BlockEventPacket = v944::BlockEventPacket;

using BlockActorDataPacket = v944::BlockActorDataPacket;

using UpdateBlockSyncedPacket = v944::UpdateBlockSyncedPacket;

using LecternUpdatePacket = v944::LecternUpdatePacket;

using OpenSignPacket = v944::OpenSignPacket;

using UpdateSubChunkNetworkBlockInfo = v944::UpdateSubChunkNetworkBlockInfo;

using UpdateSubChunkBlocksChangedInfo = v944::UpdateSubChunkBlocksChangedInfo;

using UpdateSubChunkBlocksPacket = v944::UpdateSubChunkBlocksPacket;

using AddVolumeEntityPacket = v944::AddVolumeEntityPacket;

using VoxelShapesPacket = v944::VoxelShapesPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct AnvilDamagePacket_;

template <int V> requires (V < 944)
struct AnvilDamagePacket_<V> { using type = base::AnvilDamagePacket; };

template <int V> requires (V >= 944 && V < 2168)
struct AnvilDamagePacket_<V> { using type = v944::AnvilDamagePacket; };

template <int V> requires (V >= 2168)
struct AnvilDamagePacket_<V> { using type = v2168::AnvilDamagePacket; };

template <int V>
struct UpdateBlockPacket_;

template <int V> requires (V < 944)
struct UpdateBlockPacket_<V> { using type = base::UpdateBlockPacket; };

template <int V> requires (V >= 944)
struct UpdateBlockPacket_<V> { using type = v944::UpdateBlockPacket; };

template <int V>
struct BlockEventPacket_;

template <int V> requires (V < 944)
struct BlockEventPacket_<V> { using type = base::BlockEventPacket; };

template <int V> requires (V >= 944)
struct BlockEventPacket_<V> { using type = v944::BlockEventPacket; };

template <int V>
struct BlockActorDataPacket_;

template <int V> requires (V < 944)
struct BlockActorDataPacket_<V> { using type = base::BlockActorDataPacket; };

template <int V> requires (V >= 944)
struct BlockActorDataPacket_<V> { using type = v944::BlockActorDataPacket; };

template <int V>
struct UpdateBlockSyncedPacket_;

template <int V> requires (V < 944)
struct UpdateBlockSyncedPacket_<V> { using type = base::UpdateBlockSyncedPacket; };

template <int V> requires (V >= 944)
struct UpdateBlockSyncedPacket_<V> { using type = v944::UpdateBlockSyncedPacket; };

template <int V>
struct LecternUpdatePacket_;

template <int V> requires (V < 944)
struct LecternUpdatePacket_<V> { using type = base::LecternUpdatePacket; };

template <int V> requires (V >= 944)
struct LecternUpdatePacket_<V> { using type = v944::LecternUpdatePacket; };

template <int V>
struct OpenSignPacket_;

template <int V> requires (V < 944)
struct OpenSignPacket_<V> { using type = base::OpenSignPacket; };

template <int V> requires (V >= 944)
struct OpenSignPacket_<V> { using type = v944::OpenSignPacket; };

template <int V>
struct UpdateSubChunkNetworkBlockInfo_;

template <int V> requires (V < 944)
struct UpdateSubChunkNetworkBlockInfo_<V> { using type = base::UpdateSubChunkNetworkBlockInfo; };

template <int V> requires (V >= 944)
struct UpdateSubChunkNetworkBlockInfo_<V> { using type = v944::UpdateSubChunkNetworkBlockInfo; };

template <int V>
struct UpdateSubChunkBlocksChangedInfo_;

template <int V> requires (V < 944)
struct UpdateSubChunkBlocksChangedInfo_<V> { using type = base::UpdateSubChunkBlocksChangedInfo; };

template <int V> requires (V >= 944)
struct UpdateSubChunkBlocksChangedInfo_<V> { using type = v944::UpdateSubChunkBlocksChangedInfo; };

template <int V>
struct UpdateSubChunkBlocksPacket_;

template <int V> requires (V < 944)
struct UpdateSubChunkBlocksPacket_<V> { using type = base::UpdateSubChunkBlocksPacket; };

template <int V> requires (V >= 944)
struct UpdateSubChunkBlocksPacket_<V> { using type = v944::UpdateSubChunkBlocksPacket; };

template <int V>
struct AddVolumeEntityPacket_;

template <int V> requires (V < 944)
struct AddVolumeEntityPacket_<V> { using type = base::AddVolumeEntityPacket; };

template <int V> requires (V >= 944)
struct AddVolumeEntityPacket_<V> { using type = v944::AddVolumeEntityPacket; };

template <int V>
struct VoxelShapesPacket_;

template <int V> requires (V >= 924 && V < 944)
struct VoxelShapesPacket_<V> { using type = v924::VoxelShapesPacket; };

template <int V> requires (V >= 944)
struct VoxelShapesPacket_<V> { using type = v944::VoxelShapesPacket; };

}  // namespace detail

template <int V> using AnvilDamagePacket_ = typename detail::AnvilDamagePacket_<V>::type;
template <int V> using UpdateBlockPacket_ = typename detail::UpdateBlockPacket_<V>::type;
template <int V> using BlockEventPacket_ = typename detail::BlockEventPacket_<V>::type;
template <int V> using BlockActorDataPacket_ = typename detail::BlockActorDataPacket_<V>::type;
template <int V> using UpdateBlockSyncedPacket_ = typename detail::UpdateBlockSyncedPacket_<V>::type;
template <int V> using LecternUpdatePacket_ = typename detail::LecternUpdatePacket_<V>::type;
template <int V> using OpenSignPacket_ = typename detail::OpenSignPacket_<V>::type;
template <int V> using UpdateSubChunkNetworkBlockInfo_ = typename detail::UpdateSubChunkNetworkBlockInfo_<V>::type;
template <int V> using UpdateSubChunkBlocksChangedInfo_ = typename detail::UpdateSubChunkBlocksChangedInfo_<V>::type;
template <int V> using UpdateSubChunkBlocksPacket_ = typename detail::UpdateSubChunkBlocksPacket_<V>::type;
template <int V> using AddVolumeEntityPacket_ = typename detail::AddVolumeEntityPacket_<V>::type;
template <int V> using VoxelShapesPacket_ = typename detail::VoxelShapesPacket_<V>::type;

template <int V>
struct packet_of<V, 21> { using type = UpdateBlockPacket_<V>; };

template <int V>
struct packet_of<V, 25> { using type = LevelEventPacket; };

template <int V>
struct packet_of<V, 26> { using type = BlockEventPacket_<V>; };

template <int V>
struct packet_of<V, 34> { using type = BlockPickRequestPacket; };

template <int V>
struct packet_of<V, 56> { using type = BlockActorDataPacket_<V>; };

template <int V>
struct packet_of<V, 110> { using type = UpdateBlockSyncedPacket_<V>; };

template <int V>
struct packet_of<V, 118> { using type = SpawnParticleEffectPacket; };

template <int V>
struct packet_of<V, 124> { using type = LevelEventGenericPacket; };

template <int V>
struct packet_of<V, 125> { using type = LecternUpdatePacket_<V>; };

template <int V>
struct packet_of<V, 141> { using type = AnvilDamagePacket_<V>; };

template <int V>
struct packet_of<V, 166> { using type = AddVolumeEntityPacket_<V>; };

template <int V>
struct packet_of<V, 167> { using type = RemoveVolumeEntityPacket; };

template <int V>
struct packet_of<V, 172> { using type = UpdateSubChunkBlocksPacket_<V>; };

template <int V>
struct packet_of<V, 303> { using type = OpenSignPacket_<V>; };

template <int V> requires (V >= 924)
struct packet_of<V, 337> { using type = VoxelShapesPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<ActorBlockSyncMessage::MessageId, 3> values_v<ActorBlockSyncMessage::MessageId>{{
    ActorBlockSyncMessage::MessageId::None,
    ActorBlockSyncMessage::MessageId::Create,
    ActorBlockSyncMessage::MessageId::Destroy,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<ActorBlockSyncMessage::MessageId>{{
    "none",
    "create",
    "destroy",
}};

template <>
inline constexpr std::string_view type_name_v<ActorBlockSyncMessage::MessageId>{"ActorBlockSyncMessage::MessageId"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::AnvilDamagePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AnvilDamagePacket>{"AnvilDamagePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::AnvilDamagePacket>{{
    "damage",
    "position",
}};

template <>
struct field_accessor<base::AnvilDamagePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.damage;
        }
        else {
            return value.position;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::AnvilDamagePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::AnvilDamagePacket>{"AnvilDamagePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::AnvilDamagePacket>{{
    "damage",
    "position",
}};

template <>
struct field_accessor<v944::AnvilDamagePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.damage;
        }
        else {
            return value.position;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::AnvilDamagePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::AnvilDamagePacket>{"AnvilDamagePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::AnvilDamagePacket>{{
    "position",
}};

template <>
struct field_accessor<v2168::AnvilDamagePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.position;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateBlockPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateBlockPacket>{"UpdateBlockPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::UpdateBlockPacket>{{
    "pos",
    "runtime_id",
    "update_flags",
    "layer",
}};

template <>
struct field_accessor<base::UpdateBlockPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.update_flags;
        }
        else {
            return value.layer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::UpdateBlockPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::UpdateBlockPacket>{"UpdateBlockPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::UpdateBlockPacket>{{
    "pos",
    "runtime_id",
    "update_flags",
    "layer",
}};

template <>
struct field_accessor<v944::UpdateBlockPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.update_flags;
        }
        else {
            return value.layer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BlockEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BlockEventPacket>{"BlockEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::BlockEventPacket>{{
    "pos",
    "b0",
    "b1",
}};

template <>
struct field_accessor<base::BlockEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.b0;
        }
        else {
            return value.b1;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::BlockEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::BlockEventPacket>{"BlockEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::BlockEventPacket>{{
    "pos",
    "b0",
    "b1",
}};

template <>
struct field_accessor<v944::BlockEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.b0;
        }
        else {
            return value.b1;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BlockPickRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<BlockPickRequestPacket>{"BlockPickRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<BlockPickRequestPacket>{{
    "pos",
    "with_data",
    "max_slots",
}};

template <>
struct field_accessor<BlockPickRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.with_data;
        }
        else {
            return value.max_slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BlockActorDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BlockActorDataPacket>{"BlockActorDataPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::BlockActorDataPacket>{{
    "pos",
    "data",
}};

template <>
struct field_accessor<base::BlockActorDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::BlockActorDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::BlockActorDataPacket>{"BlockActorDataPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::BlockActorDataPacket>{{
    "pos",
    "data",
}};

template <>
struct field_accessor<v944::BlockActorDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ActorBlockSyncMessage> = true;

template <>
inline constexpr std::string_view struct_name_v<ActorBlockSyncMessage>{"ActorBlockSyncMessage"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<ActorBlockSyncMessage>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateBlockSyncedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateBlockSyncedPacket>{"UpdateBlockSyncedPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::UpdateBlockSyncedPacket>{{
    "pos",
    "runtime_id",
    "update_flags",
    "layer",
    "entity_unique_id",
    "message",
}};

template <>
struct field_accessor<base::UpdateBlockSyncedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.update_flags;
        }
        else if constexpr (I == 3) {
            return value.layer;
        }
        else if constexpr (I == 4) {
            return value.entity_unique_id;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::UpdateBlockSyncedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::UpdateBlockSyncedPacket>{"UpdateBlockSyncedPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v944::UpdateBlockSyncedPacket>{{
    "pos",
    "runtime_id",
    "update_flags",
    "layer",
    "entity_unique_id",
    "message",
}};

template <>
struct field_accessor<v944::UpdateBlockSyncedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.update_flags;
        }
        else if constexpr (I == 3) {
            return value.layer;
        }
        else if constexpr (I == 4) {
            return value.entity_unique_id;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LecternUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LecternUpdatePacket>{"LecternUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::LecternUpdatePacket>{{
    "page",
    "total_pages",
    "pos",
}};

template <>
struct field_accessor<base::LecternUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.page;
        }
        else if constexpr (I == 1) {
            return value.total_pages;
        }
        else {
            return value.pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::LecternUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::LecternUpdatePacket>{"LecternUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::LecternUpdatePacket>{{
    "page",
    "total_pages",
    "pos",
}};

template <>
struct field_accessor<v944::LecternUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.page;
        }
        else if constexpr (I == 1) {
            return value.total_pages;
        }
        else {
            return value.pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::OpenSignPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::OpenSignPacket>{"OpenSignPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::OpenSignPacket>{{
    "pos",
    "is_front_side",
}};

template <>
struct field_accessor<base::OpenSignPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else {
            return value.is_front_side;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::OpenSignPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::OpenSignPacket>{"OpenSignPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::OpenSignPacket>{{
    "pos",
    "is_front_side",
}};

template <>
struct field_accessor<v944::OpenSignPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else {
            return value.is_front_side;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateSubChunkNetworkBlockInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateSubChunkNetworkBlockInfo>{"UpdateSubChunkNetworkBlockInfo"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::UpdateSubChunkNetworkBlockInfo>{{
    "pos",
    "runtime_id",
    "update_flags",
    "entity_unique_id",
    "message",
}};

template <>
struct field_accessor<base::UpdateSubChunkNetworkBlockInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.update_flags;
        }
        else if constexpr (I == 3) {
            return value.entity_unique_id;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::UpdateSubChunkNetworkBlockInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::UpdateSubChunkNetworkBlockInfo>{"UpdateSubChunkNetworkBlockInfo"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v944::UpdateSubChunkNetworkBlockInfo>{{
    "pos",
    "runtime_id",
    "update_flags",
    "entity_unique_id",
    "message",
}};

template <>
struct field_accessor<v944::UpdateSubChunkNetworkBlockInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.update_flags;
        }
        else if constexpr (I == 3) {
            return value.entity_unique_id;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateSubChunkBlocksChangedInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateSubChunkBlocksChangedInfo>{"UpdateSubChunkBlocksChangedInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::UpdateSubChunkBlocksChangedInfo>{{
    "standards",
    "extras",
}};

template <>
struct field_accessor<base::UpdateSubChunkBlocksChangedInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.standards;
        }
        else {
            return value.extras;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::UpdateSubChunkBlocksChangedInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::UpdateSubChunkBlocksChangedInfo>{"UpdateSubChunkBlocksChangedInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::UpdateSubChunkBlocksChangedInfo>{{
    "standards",
    "extras",
}};

template <>
struct field_accessor<v944::UpdateSubChunkBlocksChangedInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.standards;
        }
        else {
            return value.extras;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateSubChunkBlocksPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateSubChunkBlocksPacket>{"UpdateSubChunkBlocksPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::UpdateSubChunkBlocksPacket>{{
    "sub_chunk_block_position",
    "blocks_changed",
}};

template <>
struct field_accessor<base::UpdateSubChunkBlocksPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_block_position;
        }
        else {
            return value.blocks_changed;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::UpdateSubChunkBlocksPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::UpdateSubChunkBlocksPacket>{"UpdateSubChunkBlocksPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::UpdateSubChunkBlocksPacket>{{
    "sub_chunk_block_position",
    "blocks_changed",
}};

template <>
struct field_accessor<v944::UpdateSubChunkBlocksPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_block_position;
        }
        else {
            return value.blocks_changed;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<RemoveVolumeEntityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RemoveVolumeEntityPacket>{"RemoveVolumeEntityPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<RemoveVolumeEntityPacket>{{
    "entity_net_id",
    "dimension_type",
}};

template <>
struct field_accessor<RemoveVolumeEntityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_net_id;
        }
        else {
            return value.dimension_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AddVolumeEntityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AddVolumeEntityPacket>{"AddVolumeEntityPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::AddVolumeEntityPacket>{{
    "entity_net_id",
    "components",
    "json_identifier",
    "instance_name",
    "min_bounds",
    "max_bounds",
    "dimension_type",
    "min_engine_version",
}};

template <>
struct field_accessor<base::AddVolumeEntityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_net_id;
        }
        else if constexpr (I == 1) {
            return value.components;
        }
        else if constexpr (I == 2) {
            return value.json_identifier;
        }
        else if constexpr (I == 3) {
            return value.instance_name;
        }
        else if constexpr (I == 4) {
            return value.min_bounds;
        }
        else if constexpr (I == 5) {
            return value.max_bounds;
        }
        else if constexpr (I == 6) {
            return value.dimension_type;
        }
        else {
            return value.min_engine_version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::AddVolumeEntityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::AddVolumeEntityPacket>{"AddVolumeEntityPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v944::AddVolumeEntityPacket>{{
    "entity_net_id",
    "components",
    "json_identifier",
    "instance_name",
    "min_bounds",
    "max_bounds",
    "dimension_type",
    "min_engine_version",
}};

template <>
struct field_accessor<v944::AddVolumeEntityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_net_id;
        }
        else if constexpr (I == 1) {
            return value.components;
        }
        else if constexpr (I == 2) {
            return value.json_identifier;
        }
        else if constexpr (I == 3) {
            return value.instance_name;
        }
        else if constexpr (I == 4) {
            return value.min_bounds;
        }
        else if constexpr (I == 5) {
            return value.max_bounds;
        }
        else if constexpr (I == 6) {
            return value.dimension_type;
        }
        else {
            return value.min_engine_version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SerializableCells> = true;

template <>
inline constexpr std::string_view struct_name_v<SerializableCells>{"SerializableCells"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<SerializableCells>{{
    "x_size",
    "y_size",
    "z_size",
    "storage",
}};

template <>
struct field_accessor<SerializableCells> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.x_size;
        }
        else if constexpr (I == 1) {
            return value.y_size;
        }
        else if constexpr (I == 2) {
            return value.z_size;
        }
        else {
            return value.storage;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SerializableVoxelShape> = true;

template <>
inline constexpr std::string_view struct_name_v<SerializableVoxelShape>{"SerializableVoxelShape"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<SerializableVoxelShape>{{
    "cells",
    "x_coords",
    "y_coords",
    "z_coords",
}};

template <>
struct field_accessor<SerializableVoxelShape> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cells;
        }
        else if constexpr (I == 1) {
            return value.x_coords;
        }
        else if constexpr (I == 2) {
            return value.y_coords;
        }
        else {
            return value.z_coords;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::VoxelShapesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::VoxelShapesPacket>{"VoxelShapesPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::VoxelShapesPacket>{{
    "shapes",
    "name_map",
}};

template <>
struct field_accessor<v924::VoxelShapesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.shapes;
        }
        else {
            return value.name_map;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::VoxelShapesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::VoxelShapesPacket>{"VoxelShapesPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::VoxelShapesPacket>{{
    "shapes",
    "name_map",
    "custom_shape_count",
}};

template <>
struct field_accessor<v944::VoxelShapesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.shapes;
        }
        else if constexpr (I == 1) {
            return value.name_map;
        }
        else {
            return value.custom_shape_count;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<LevelEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<LevelEventPacket>{"LevelEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<LevelEventPacket>{{
    "event_id",
    "pos",
    "data",
}};

template <>
struct field_accessor<LevelEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.event_id;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<LevelEventGenericPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<LevelEventGenericPacket>{"LevelEventGenericPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<LevelEventGenericPacket>{{
    "event_id",
    "data",
}};

template <>
struct field_accessor<LevelEventGenericPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.event_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SpawnParticleEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SpawnParticleEffectPacket>{"SpawnParticleEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<SpawnParticleEffectPacket>{{
    "vanilla_dimension_id",
    "actor_id",
    "pos",
    "effect_name",
    "molang_variables",
}};

template <>
struct field_accessor<SpawnParticleEffectPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.vanilla_dimension_id;
        }
        else if constexpr (I == 1) {
            return value.actor_id;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.effect_name;
        }
        else {
            return value.molang_variables;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::AnvilDamagePacket> {
    static void serialize(BinaryWriter &stream, const base::AnvilDamagePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AnvilDamagePacket, std::error_code>;
};

template <>
struct Serializer<v944::AnvilDamagePacket> {
    static void serialize(BinaryWriter &stream, const v944::AnvilDamagePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::AnvilDamagePacket, std::error_code>;
};

template <>
struct Serializer<v2168::AnvilDamagePacket> {
    static void serialize(BinaryWriter &stream, const v2168::AnvilDamagePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::AnvilDamagePacket, std::error_code>;
};

template <>
struct Serializer<base::UpdateBlockPacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateBlockPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateBlockPacket, std::error_code>;
};

template <>
struct Serializer<v944::UpdateBlockPacket> {
    static void serialize(BinaryWriter &stream, const v944::UpdateBlockPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::UpdateBlockPacket, std::error_code>;
};

template <>
struct Serializer<base::BlockEventPacket> {
    static void serialize(BinaryWriter &stream, const base::BlockEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BlockEventPacket, std::error_code>;
};

template <>
struct Serializer<v944::BlockEventPacket> {
    static void serialize(BinaryWriter &stream, const v944::BlockEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::BlockEventPacket, std::error_code>;
};

template <>
struct Serializer<BlockPickRequestPacket> {
    static void serialize(BinaryWriter &stream, const BlockPickRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BlockPickRequestPacket, std::error_code>;
};

template <>
struct Serializer<base::BlockActorDataPacket> {
    static void serialize(BinaryWriter &stream, const base::BlockActorDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BlockActorDataPacket, std::error_code>;
};

template <>
struct Serializer<v944::BlockActorDataPacket> {
    static void serialize(BinaryWriter &stream, const v944::BlockActorDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::BlockActorDataPacket, std::error_code>;
};

template <>
struct Serializer<base::UpdateBlockSyncedPacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateBlockSyncedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateBlockSyncedPacket, std::error_code>;
};

template <>
struct Serializer<v944::UpdateBlockSyncedPacket> {
    static void serialize(BinaryWriter &stream, const v944::UpdateBlockSyncedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::UpdateBlockSyncedPacket, std::error_code>;
};

template <>
struct Serializer<base::LecternUpdatePacket> {
    static void serialize(BinaryWriter &stream, const base::LecternUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LecternUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v944::LecternUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v944::LecternUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::LecternUpdatePacket, std::error_code>;
};

template <>
struct Serializer<base::OpenSignPacket> {
    static void serialize(BinaryWriter &stream, const base::OpenSignPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::OpenSignPacket, std::error_code>;
};

template <>
struct Serializer<v944::OpenSignPacket> {
    static void serialize(BinaryWriter &stream, const v944::OpenSignPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::OpenSignPacket, std::error_code>;
};

template <>
struct Serializer<base::UpdateSubChunkNetworkBlockInfo> {
    static void serialize(BinaryWriter &stream, const base::UpdateSubChunkNetworkBlockInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateSubChunkNetworkBlockInfo, std::error_code>;
};

template <>
struct Serializer<v944::UpdateSubChunkNetworkBlockInfo> {
    static void serialize(BinaryWriter &stream, const v944::UpdateSubChunkNetworkBlockInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::UpdateSubChunkNetworkBlockInfo, std::error_code>;
};

template <>
struct Serializer<base::UpdateSubChunkBlocksChangedInfo> {
    static void serialize(BinaryWriter &stream, const base::UpdateSubChunkBlocksChangedInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateSubChunkBlocksChangedInfo, std::error_code>;
};

template <>
struct Serializer<v944::UpdateSubChunkBlocksChangedInfo> {
    static void serialize(BinaryWriter &stream, const v944::UpdateSubChunkBlocksChangedInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::UpdateSubChunkBlocksChangedInfo, std::error_code>;
};

template <>
struct Serializer<base::UpdateSubChunkBlocksPacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateSubChunkBlocksPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateSubChunkBlocksPacket, std::error_code>;
};

template <>
struct Serializer<v944::UpdateSubChunkBlocksPacket> {
    static void serialize(BinaryWriter &stream, const v944::UpdateSubChunkBlocksPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::UpdateSubChunkBlocksPacket, std::error_code>;
};

template <>
struct Serializer<RemoveVolumeEntityPacket> {
    static void serialize(BinaryWriter &stream, const RemoveVolumeEntityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RemoveVolumeEntityPacket, std::error_code>;
};

template <>
struct Serializer<base::AddVolumeEntityPacket> {
    static void serialize(BinaryWriter &stream, const base::AddVolumeEntityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AddVolumeEntityPacket, std::error_code>;
};

template <>
struct Serializer<v944::AddVolumeEntityPacket> {
    static void serialize(BinaryWriter &stream, const v944::AddVolumeEntityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::AddVolumeEntityPacket, std::error_code>;
};

template <>
struct Serializer<SerializableCells> {
    static void serialize(BinaryWriter &stream, const SerializableCells &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SerializableCells, std::error_code>;
};

template <>
struct Serializer<SerializableVoxelShape> {
    static void serialize(BinaryWriter &stream, const SerializableVoxelShape &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SerializableVoxelShape, std::error_code>;
};

template <>
struct Serializer<v924::VoxelShapesPacket> {
    static void serialize(BinaryWriter &stream, const v924::VoxelShapesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::VoxelShapesPacket, std::error_code>;
};

template <>
struct Serializer<v944::VoxelShapesPacket> {
    static void serialize(BinaryWriter &stream, const v944::VoxelShapesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::VoxelShapesPacket, std::error_code>;
};

template <>
struct Serializer<LevelEventPacket> {
    static void serialize(BinaryWriter &stream, const LevelEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<LevelEventPacket, std::error_code>;
};

template <>
struct Serializer<LevelEventGenericPacket> {
    static void serialize(BinaryWriter &stream, const LevelEventGenericPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<LevelEventGenericPacket, std::error_code>;
};

template <>
struct Serializer<SpawnParticleEffectPacket> {
    static void serialize(BinaryWriter &stream, const SpawnParticleEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SpawnParticleEffectPacket, std::error_code>;
};
using AnvilDamagePacket = AnvilDamagePacket_<2225>;
using UpdateBlockPacket = UpdateBlockPacket_<2225>;
using BlockEventPacket = BlockEventPacket_<2225>;
using BlockActorDataPacket = BlockActorDataPacket_<2225>;
using UpdateBlockSyncedPacket = UpdateBlockSyncedPacket_<2225>;
using LecternUpdatePacket = LecternUpdatePacket_<2225>;
using OpenSignPacket = OpenSignPacket_<2225>;
using UpdateSubChunkNetworkBlockInfo = UpdateSubChunkNetworkBlockInfo_<2225>;
using UpdateSubChunkBlocksChangedInfo = UpdateSubChunkBlocksChangedInfo_<2225>;
using UpdateSubChunkBlocksPacket = UpdateSubChunkBlocksPacket_<2225>;
using AddVolumeEntityPacket = AddVolumeEntityPacket_<2225>;
using VoxelShapesPacket = VoxelShapesPacket_<2225>;

}  // namespace bedrock::protocol
