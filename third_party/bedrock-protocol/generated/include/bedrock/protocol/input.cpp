#include <bedrock/protocol/input.h>

#include <bedrock/protocol/detail/bitset.hpp>

namespace bedrock::protocol {


void Serializer<base::PlayerBlockActionData>::serialize(BinaryWriter &stream, const base::PlayerBlockActionData &value)
{
    stream.writeVarInt<std::int32_t>(value.player_action_type);
    if (((value.player_action_type) == (base::PlayerActionType::StartDestroyBlock)) || ((value.player_action_type) == (base::PlayerActionType::AbortDestroyBlock)) || ((value.player_action_type) == (base::PlayerActionType::CrackBlock)) || ((value.player_action_type) == (base::PlayerActionType::PredictDestroyBlock)) || ((value.player_action_type) == (base::PlayerActionType::ContinueDestroyBlock))) {
        Serializer<BlockPos>::serialize(stream, value.pos);
        stream.writeVarInt<std::int32_t>(value.facing);
    }
}

auto Serializer<base::PlayerBlockActionData>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerBlockActionData, std::error_code>
{
    base::PlayerBlockActionData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_action_type = static_cast<base::PlayerActionType>(*v);
    }
    if (((out.player_action_type) == (base::PlayerActionType::StartDestroyBlock)) || ((out.player_action_type) == (base::PlayerActionType::AbortDestroyBlock)) || ((out.player_action_type) == (base::PlayerActionType::CrackBlock)) || ((out.player_action_type) == (base::PlayerActionType::PredictDestroyBlock)) || ((out.player_action_type) == (base::PlayerActionType::ContinueDestroyBlock))) {
        {
            auto v = Serializer<BlockPos>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.pos = *v;
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.facing = static_cast<std::int32_t>(*v);
        }
    }
    return out;
}

void Serializer<v748::PlayerBlockActionData>::serialize(BinaryWriter &stream, const v748::PlayerBlockActionData &value)
{
    stream.writeVarInt<std::int32_t>(value.player_action_type);
    if (((value.player_action_type) == (v748::PlayerActionType::StartDestroyBlock)) || ((value.player_action_type) == (v748::PlayerActionType::AbortDestroyBlock)) || ((value.player_action_type) == (v748::PlayerActionType::CrackBlock)) || ((value.player_action_type) == (v748::PlayerActionType::PredictDestroyBlock)) || ((value.player_action_type) == (v748::PlayerActionType::ContinueDestroyBlock))) {
        Serializer<BlockPos>::serialize(stream, value.pos);
        stream.writeVarInt<std::int32_t>(value.facing);
    }
}

auto Serializer<v748::PlayerBlockActionData>::deserialize(BinaryReader &stream) -> std::expected<v748::PlayerBlockActionData, std::error_code>
{
    v748::PlayerBlockActionData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_action_type = static_cast<v748::PlayerActionType>(*v);
    }
    if (((out.player_action_type) == (v748::PlayerActionType::StartDestroyBlock)) || ((out.player_action_type) == (v748::PlayerActionType::AbortDestroyBlock)) || ((out.player_action_type) == (v748::PlayerActionType::CrackBlock)) || ((out.player_action_type) == (v748::PlayerActionType::PredictDestroyBlock)) || ((out.player_action_type) == (v748::PlayerActionType::ContinueDestroyBlock))) {
        {
            auto v = Serializer<BlockPos>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.pos = *v;
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.facing = static_cast<std::int32_t>(*v);
        }
    }
    return out;
}

void Serializer<v2168::PlayerBlockActionData>::serialize(BinaryWriter &stream, const v2168::PlayerBlockActionData &value)
{
    stream.writeVarInt<std::int32_t>(value.player_action_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.facing);
}

auto Serializer<v2168::PlayerBlockActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerBlockActionData, std::error_code>
{
    v2168::PlayerBlockActionData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_action_type = static_cast<v2168::PlayerActionType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.facing = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const base::PackedItemUseLegacyInventoryTransaction &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if (((value.id) < (-1)) && (((value.id) & (1)) == (0))) {
        stream.writeVarInt<std::uint32_t>(value.slots.size());
        for (const auto &e0 : value.slots) {
            Serializer<base::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<legacy::base::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<base::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<base::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    base::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if (((out.id) < (-1)) && (((out.id) & (1)) == (0))) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.slots.emplace_back();
                auto v = Serializer<base::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.slots.back() = *v;
            }
        }
    }
    {
        auto v = Serializer<legacy::base::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v748::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v748::PackedItemUseLegacyInventoryTransaction &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if (((value.id) < (-1)) && (((value.id) & (1)) == (0))) {
        stream.writeVarInt<std::uint32_t>(value.slots.size());
        for (const auto &e0 : value.slots) {
            Serializer<base::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<legacy::v748::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v748::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v748::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v748::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if (((out.id) < (-1)) && (((out.id) & (1)) == (0))) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.slots.emplace_back();
                auto v = Serializer<base::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.slots.back() = *v;
            }
        }
    }
    {
        auto v = Serializer<legacy::v748::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v844::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v844::PackedItemUseLegacyInventoryTransaction &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if (((value.id) < (-1)) && (((value.id) & (1)) == (0))) {
        stream.writeVarInt<std::uint32_t>(value.slots.size());
        for (const auto &e0 : value.slots) {
            Serializer<base::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<legacy::v844::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v844::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v844::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v844::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if (((out.id) < (-1)) && (((out.id) & (1)) == (0))) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.slots.emplace_back();
                auto v = Serializer<base::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.slots.back() = *v;
            }
        }
    }
    {
        auto v = Serializer<legacy::v844::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v924::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v924::PackedItemUseLegacyInventoryTransaction &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if (((value.id) < (-1)) && (((value.id) & (1)) == (0))) {
        stream.writeVarInt<std::uint32_t>(value.slots.size());
        for (const auto &e0 : value.slots) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<legacy::v844::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v924::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v924::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v924::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if (((out.id) < (-1)) && (((out.id) & (1)) == (0))) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.slots.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.slots.back() = *v;
            }
        }
    }
    {
        auto v = Serializer<legacy::v844::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v944::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v944::PackedItemUseLegacyInventoryTransaction &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if (((value.id) < (-1)) && (((value.id) & (1)) == (0))) {
        stream.writeVarInt<std::uint32_t>(value.slots.size());
        for (const auto &e0 : value.slots) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<legacy::v944::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v944::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v944::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v944::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if (((out.id) < (-1)) && (((out.id) & (1)) == (0))) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.slots.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.slots.back() = *v;
            }
        }
    }
    {
        auto v = Serializer<legacy::v944::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v1001::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v1001::PackedItemUseLegacyInventoryTransaction &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if (((value.id) < (-1)) && (((value.id) & (1)) == (0))) {
        stream.writeVarInt<std::uint32_t>(value.slots.size());
        for (const auto &e0 : value.slots) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<legacy::v1001::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v1001::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v1001::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v1001::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if (((out.id) < (-1)) && (((out.id) & (1)) == (0))) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.slots.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.slots.back() = *v;
            }
        }
    }
    {
        auto v = Serializer<legacy::v1001::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2168::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v2168::PackedItemUseLegacyInventoryTransaction &value)
{
    Serializer<ItemStackLegacyRequestId>::serialize(stream, value.id);
    stream.write<bool>(value.slots.has_value());
    if (value.slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.slots).size());
        for (const auto &e0 : (*value.slots)) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.write<bool>(true);
    Serializer<v2168::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2168::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2168::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v2168::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = Serializer<ItemStackLegacyRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v924::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.slots = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<v2168::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2193::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v2193::PackedItemUseLegacyInventoryTransaction &value)
{
    Serializer<ItemStackLegacyRequestId>::serialize(stream, value.id);
    stream.write<bool>(value.slots.has_value());
    if (value.slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.slots).size());
        for (const auto &e0 : (*value.slots)) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<v2193::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2193::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2193::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v2193::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = Serializer<ItemStackLegacyRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v924::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.slots = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2193::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2225::PackedItemUseLegacyInventoryTransaction>::serialize(BinaryWriter &stream, const v2225::PackedItemUseLegacyInventoryTransaction &value)
{
    Serializer<ItemStackLegacyRequestId>::serialize(stream, value.id);
    stream.write<bool>(value.slots.has_value());
    if (value.slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.slots).size());
        for (const auto &e0 : (*value.slots)) {
            Serializer<v2225::LegacySetSlot>::serialize(stream, e0);
        }
    }
    Serializer<v2193::ItemUseInventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2225::PackedItemUseLegacyInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2225::PackedItemUseLegacyInventoryTransaction, std::error_code>
{
    v2225::PackedItemUseLegacyInventoryTransaction out;
    {
        auto v = Serializer<ItemStackLegacyRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2225::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2225::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.slots = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2193::ItemUseInventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<base::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const base::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<53>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    if ((value.play_mode) == (ClientPlayMode::RealityDeprecated)) {
        Serializer<Vec3>::serialize(stream, value.gaze_direction);
    }
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<base::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<base::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<base::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
}

auto Serializer<base::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerAuthInputPacket, std::error_code>
{
    base::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<53>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    if ((out.play_mode) == (ClientPlayMode::RealityDeprecated)) {
        {
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.gaze_direction = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<base::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<base::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<base::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(base::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    return out;
}

void Serializer<v748::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v748::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<58>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v748::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<base::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
}

auto Serializer<v748::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::PlayerAuthInputPacket, std::error_code>
{
    v748::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<58>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v748::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<base::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v748::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    return out;
}

void Serializer<v766::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v766::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<65>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v748::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<base::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v766::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::PlayerAuthInputPacket, std::error_code>
{
    v766::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<65>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v748::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<base::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v766::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v844::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v844::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<65>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v844::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<base::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v844::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::PlayerAuthInputPacket, std::error_code>
{
    v844::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<65>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v844::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<base::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v844::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v924::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v924::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<65>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v924::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<v924::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v924::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::PlayerAuthInputPacket, std::error_code>
{
    v924::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<65>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v924::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<v924::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v924::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v944::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v944::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<65>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v944::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<v924::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v944::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::PlayerAuthInputPacket, std::error_code>
{
    v944::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<65>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v944::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<v924::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v944::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v975::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v975::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<65>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v944::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<v975::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v975::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::PlayerAuthInputPacket, std::error_code>
{
    v975::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<65>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v944::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<v975::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v975::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v1001::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v1001::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    Serializer<std::bitset<65>>::serialize(stream, value.input_data);
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::uint32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if (value.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        Serializer<v1001::PackedItemUseLegacyInventoryTransaction>::serialize(stream, value.item_use_transaction);
    }
    if (value.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        Serializer<v975::ItemStackRequestData>::serialize(stream, value.item_stack_request);
    }
    if (value.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        stream.writeVarInt<std::int32_t>(value.player_block_actions.size());
        for (const auto &e0 : value.player_block_actions) {
            Serializer<v748::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    if (value.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rot);
        stream.writeVarInt<std::int64_t>(value.client_predicted_vehicle);
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v1001::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::PlayerAuthInputPacket, std::error_code>
{
    v1001::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<std::bitset<65>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.input_data = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if (out.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::PerformItemInteraction))) {
        {
            auto v = Serializer<v1001::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_use_transaction = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::PerformItemStackRequest))) {
        {
            auto v = Serializer<v975::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_stack_request = *v;
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::PerformBlockActions))) {
        {
            auto len0 = stream.readVarInt<std::int32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.player_block_actions.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.player_block_actions.emplace_back();
                auto v = Serializer<v748::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.player_block_actions.back() = *v;
            }
        }
    }
    if (out.input_data.test(static_cast<std::size_t>(v1001::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle))) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rot = *v;
        }
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.client_predicted_vehicle = static_cast<ActorUniqueID>(*v);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v2168::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v2168::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    stream.write<bool>(true);
    stream.writeVarInt<std::uint32_t>(value.input_data.size());
    for (const auto &e0 : value.input_data) {
        stream.writeVarInt<std::int32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::int32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    stream.write<bool>(true);
    stream.write<bool>(value.item_use_transaction.has_value());
    if (value.item_use_transaction.has_value()) {
        Serializer<v2168::PackedItemUseLegacyInventoryTransaction>::serialize(stream, (*value.item_use_transaction));
    }
    stream.write<bool>(true);
    stream.write<bool>(value.item_stack_request.has_value());
    if (value.item_stack_request.has_value()) {
        Serializer<v2168::ItemStackRequestCereal::RequestData>::serialize(stream, (*value.item_stack_request));
    }
    stream.write<bool>(true);
    stream.write<bool>(value.player_block_actions.has_value());
    if (value.player_block_actions.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.player_block_actions).size());
        for (const auto &e0 : (*value.player_block_actions)) {
            Serializer<v2168::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    stream.write<bool>(true);
    stream.write<bool>(value.vehicle_rot.has_value());
    if (value.vehicle_rot.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vehicle_rot));
    }
    stream.write<bool>(true);
    stream.write<bool>(value.client_predicted_vehicle.has_value());
    if (value.client_predicted_vehicle.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.client_predicted_vehicle));
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v2168::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerAuthInputPacket, std::error_code>
{
    v2168::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.input_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.input_data.emplace_back();
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.input_data.back() = static_cast<v2168::PlayerAuthInputPacket::InputData>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::PackedItemUseLegacyInventoryTransaction staged{};
            auto v = Serializer<v2168::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_use_transaction = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::ItemStackRequestCereal::RequestData staged{};
            auto v = Serializer<v2168::ItemStackRequestCereal::RequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_stack_request = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::PlayerBlockActionData> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.player_block_actions = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vehicle_rot = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.client_predicted_vehicle = std::move(staged);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v2193::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v2193::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    stream.writeVarInt<std::uint32_t>(value.input_data.size());
    for (const auto &e0 : value.input_data) {
        stream.writeVarInt<std::int32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::int32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    stream.write<bool>(value.item_use_transaction.has_value());
    if (value.item_use_transaction.has_value()) {
        Serializer<v2193::PackedItemUseLegacyInventoryTransaction>::serialize(stream, (*value.item_use_transaction));
    }
    stream.write<bool>(value.item_stack_request.has_value());
    if (value.item_stack_request.has_value()) {
        Serializer<v2168::ItemStackRequestCereal::RequestData>::serialize(stream, (*value.item_stack_request));
    }
    stream.write<bool>(value.player_block_actions.has_value());
    if (value.player_block_actions.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.player_block_actions).size());
        for (const auto &e0 : (*value.player_block_actions)) {
            Serializer<v2168::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    stream.write<bool>(value.vehicle_rot.has_value());
    if (value.vehicle_rot.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vehicle_rot));
    }
    stream.write<bool>(value.client_predicted_vehicle.has_value());
    if (value.client_predicted_vehicle.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.client_predicted_vehicle));
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v2193::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::PlayerAuthInputPacket, std::error_code>
{
    v2193::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.input_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.input_data.emplace_back();
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.input_data.back() = static_cast<v2193::PlayerAuthInputPacket::InputData>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2193::PackedItemUseLegacyInventoryTransaction staged{};
            auto v = Serializer<v2193::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_use_transaction = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::ItemStackRequestCereal::RequestData staged{};
            auto v = Serializer<v2168::ItemStackRequestCereal::RequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_stack_request = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::PlayerBlockActionData> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.player_block_actions = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vehicle_rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.client_predicted_vehicle = std::move(staged);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<v2225::PlayerAuthInputPacket>::serialize(BinaryWriter &stream, const v2225::PlayerAuthInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.move);
    stream.write<float>(value.y_head_rot);
    stream.writeVarInt<std::uint32_t>(value.input_data.size());
    for (const auto &e0 : value.input_data) {
        stream.writeVarInt<std::int32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.input_mode);
    stream.writeVarInt<std::uint32_t>(value.play_mode);
    stream.writeVarInt<std::int32_t>(value.new_interaction_model);
    Serializer<Vec2>::serialize(stream, value.interact_rotation);
    stream.writeVarInt<std::uint64_t>(value.client_tick);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    stream.write<bool>(value.item_use_transaction.has_value());
    if (value.item_use_transaction.has_value()) {
        Serializer<v2225::PackedItemUseLegacyInventoryTransaction>::serialize(stream, (*value.item_use_transaction));
    }
    stream.write<bool>(value.item_stack_request.has_value());
    if (value.item_stack_request.has_value()) {
        Serializer<v2225::ItemStackRequestCereal::RequestData>::serialize(stream, (*value.item_stack_request));
    }
    stream.write<bool>(value.player_block_actions.has_value());
    if (value.player_block_actions.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.player_block_actions).size());
        for (const auto &e0 : (*value.player_block_actions)) {
            Serializer<v2168::PlayerBlockActionData>::serialize(stream, e0);
        }
    }
    stream.write<bool>(value.vehicle_rot.has_value());
    if (value.vehicle_rot.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vehicle_rot));
    }
    stream.write<bool>(value.client_predicted_vehicle.has_value());
    if (value.client_predicted_vehicle.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.client_predicted_vehicle));
    }
    Serializer<Vec2>::serialize(stream, value.analog_move_vector);
    Serializer<Vec3>::serialize(stream, value.camera_orientation);
    Serializer<Vec2>::serialize(stream, value.raw_move_vector);
}

auto Serializer<v2225::PlayerAuthInputPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerAuthInputPacket, std::error_code>
{
    v2225::PlayerAuthInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.input_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.input_data.emplace_back();
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.input_data.back() = static_cast<v2225::PlayerAuthInputPacket::InputData>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_mode = static_cast<InputMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.play_mode = static_cast<ClientPlayMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.new_interaction_model = static_cast<NewInteractionModel>(*v);
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.interact_rotation = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.client_tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2225::PackedItemUseLegacyInventoryTransaction staged{};
            auto v = Serializer<v2225::PackedItemUseLegacyInventoryTransaction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_use_transaction = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2225::ItemStackRequestCereal::RequestData staged{};
            auto v = Serializer<v2225::ItemStackRequestCereal::RequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_stack_request = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::PlayerBlockActionData> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::PlayerBlockActionData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.player_block_actions = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vehicle_rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.client_predicted_vehicle = std::move(staged);
        }
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.analog_move_vector = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_orientation = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.raw_move_vector = *v;
    }
    return out;
}

void Serializer<base::PlayerActionPacket>::serialize(BinaryWriter &stream, const base::PlayerActionPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.result_pos);
    stream.writeVarInt<std::int32_t>(value.face);
}

auto Serializer<base::PlayerActionPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerActionPacket, std::error_code>
{
    base::PlayerActionPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<base::PlayerActionType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.result_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v748::PlayerActionPacket>::serialize(BinaryWriter &stream, const v748::PlayerActionPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.result_pos);
    stream.writeVarInt<std::int32_t>(value.face);
}

auto Serializer<v748::PlayerActionPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::PlayerActionPacket, std::error_code>
{
    v748::PlayerActionPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v748::PlayerActionType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.result_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v944::PlayerActionPacket>::serialize(BinaryWriter &stream, const v944::PlayerActionPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action);
    Serializer<BlockPos>::serialize(stream, value.pos);
    Serializer<BlockPos>::serialize(stream, value.result_pos);
    stream.writeVarInt<std::int32_t>(value.face);
}

auto Serializer<v944::PlayerActionPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::PlayerActionPacket, std::error_code>
{
    v944::PlayerActionPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v748::PlayerActionType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.result_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::PlayerActionPacket>::serialize(BinaryWriter &stream, const v2168::PlayerActionPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action);
    Serializer<BlockPos>::serialize(stream, value.pos);
    Serializer<BlockPos>::serialize(stream, value.result_pos);
    stream.writeVarInt<std::int32_t>(value.face);
}

auto Serializer<v2168::PlayerActionPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerActionPacket, std::error_code>
{
    v2168::PlayerActionPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v2168::PlayerActionType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.result_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::UpdateClientInputLocksPacket>::serialize(BinaryWriter &stream, const base::UpdateClientInputLocksPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.input_lock_component_data);
    Serializer<Vec3>::serialize(stream, value.server_pos);
}

auto Serializer<base::UpdateClientInputLocksPacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateClientInputLocksPacket, std::error_code>
{
    base::UpdateClientInputLocksPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_lock_component_data = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_pos = *v;
    }
    return out;
}

void Serializer<v944::UpdateClientInputLocksPacket>::serialize(BinaryWriter &stream, const v944::UpdateClientInputLocksPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.input_lock_component_data);
}

auto Serializer<v944::UpdateClientInputLocksPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::UpdateClientInputLocksPacket, std::error_code>
{
    v944::UpdateClientInputLocksPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.input_lock_component_data = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<base::PassengerJumpPacket>::serialize(BinaryWriter &stream, const base::PassengerJumpPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.jump_scale);
}

auto Serializer<base::PassengerJumpPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PassengerJumpPacket, std::error_code>
{
    base::PassengerJumpPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.jump_scale = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::PlayerInputPacket>::serialize(BinaryWriter &stream, const base::PlayerInputPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.mov);
    stream.write<bool>(value.is_jumping);
    stream.write<bool>(value.is_sneaking);
}

auto Serializer<base::PlayerInputPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerInputPacket, std::error_code>
{
    base::PlayerInputPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.mov = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_jumping = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sneaking = static_cast<bool>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
