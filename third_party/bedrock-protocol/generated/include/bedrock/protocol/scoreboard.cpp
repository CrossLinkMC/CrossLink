#include <bedrock/protocol/scoreboard.h>

namespace bedrock::protocol {


void Serializer<ScoreboardId>::serialize(BinaryWriter &stream, const ScoreboardId &value)
{
    stream.writeVarInt<std::int64_t>(value.raw_id);
}

auto Serializer<ScoreboardId>::deserialize(BinaryReader &stream) -> std::expected<ScoreboardId, std::error_code>
{
    ScoreboardId out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::int64_t>(*v);
    }
    return out;
}

void Serializer<PlayerScoreboardId>::serialize(BinaryWriter &stream, const PlayerScoreboardId &value)
{
    stream.writeVarInt<std::int64_t>(value.actor_unique_id);
}

auto Serializer<PlayerScoreboardId>::deserialize(BinaryReader &stream) -> std::expected<PlayerScoreboardId, std::error_code>
{
    PlayerScoreboardId out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_unique_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<ScorePacketInfo>::serialize(BinaryWriter &stream, const ScorePacketInfo &value)
{
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write(value.objective_name);
    stream.write<std::int32_t>(value.score_value);
    stream.write<std::uint8_t>(value.identity_type);
    if ((value.identity_type) == (IdentityDefinition::Type::Player)) {
        Serializer<PlayerScoreboardId>::serialize(stream, value.player_id);
    }
    if ((value.identity_type) == (IdentityDefinition::Type::Entity)) {
        stream.writeVarInt<std::int64_t>(value.entity_id);
    }
    if ((value.identity_type) == (IdentityDefinition::Type::FakePlayer)) {
        stream.write(value.fake_player_name);
    }
}

auto Serializer<ScorePacketInfo>::deserialize(BinaryReader &stream) -> std::expected<ScorePacketInfo, std::error_code>
{
    ScorePacketInfo out;
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score_value = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.identity_type = static_cast<IdentityDefinition::Type>(*v);
    }
    if ((out.identity_type) == (IdentityDefinition::Type::Player)) {
        {
            auto v = Serializer<PlayerScoreboardId>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.player_id = *v;
        }
    }
    if ((out.identity_type) == (IdentityDefinition::Type::Entity)) {
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.entity_id = static_cast<ActorUniqueID>(*v);
        }
    }
    if ((out.identity_type) == (IdentityDefinition::Type::FakePlayer)) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.fake_player_name = *v;
        }
    }
    return out;
}

void Serializer<v2168::RemoveScore>::serialize(BinaryWriter &stream, const v2168::RemoveScore &value)
{
    stream.write("remove");
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write<bool>(value.objective_name.has_value());
    if (value.objective_name.has_value()) {
        stream.write((*value.objective_name));
    }
}

auto Serializer<v2168::RemoveScore>::deserialize(BinaryReader &stream) -> std::expected<v2168::RemoveScore, std::error_code>
{
    v2168::RemoveScore out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "remove") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.objective_name = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::ChangePlayerScore>::serialize(BinaryWriter &stream, const v2168::ChangePlayerScore &value)
{
    stream.write("changeplayer");
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write(value.objective_name);
    stream.write<std::int32_t>(value.score_value);
    Serializer<PlayerScoreboardId>::serialize(stream, value.player_id);
}

auto Serializer<v2168::ChangePlayerScore>::deserialize(BinaryReader &stream) -> std::expected<v2168::ChangePlayerScore, std::error_code>
{
    v2168::ChangePlayerScore out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "changeplayer") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score_value = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<PlayerScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_id = *v;
    }
    return out;
}

void Serializer<v2168::ChangeEntityScore>::serialize(BinaryWriter &stream, const v2168::ChangeEntityScore &value)
{
    stream.write("changeentity");
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write(value.objective_name);
    stream.write<std::int32_t>(value.score_value);
    stream.writeVarInt<std::int64_t>(value.entity_id);
}

auto Serializer<v2168::ChangeEntityScore>::deserialize(BinaryReader &stream) -> std::expected<v2168::ChangeEntityScore, std::error_code>
{
    v2168::ChangeEntityScore out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "changeentity") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score_value = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v2168::ChangeFakePlayerScore>::serialize(BinaryWriter &stream, const v2168::ChangeFakePlayerScore &value)
{
    stream.write("changefakeplayer");
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write(value.objective_name);
    stream.write<std::int32_t>(value.score_value);
    stream.write(value.fake_player_name);
}

auto Serializer<v2168::ChangeFakePlayerScore>::deserialize(BinaryReader &stream) -> std::expected<v2168::ChangeFakePlayerScore, std::error_code>
{
    v2168::ChangeFakePlayerScore out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "changefakeplayer") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score_value = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.fake_player_name = *v;
    }
    return out;
}

void Serializer<base::ScoreboardIdentityPacketInfo>::serialize(BinaryWriter &stream, const base::ScoreboardIdentityPacketInfo &value)
{
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    Serializer<PlayerScoreboardId>::serialize(stream, value.player_id);
}

auto Serializer<base::ScoreboardIdentityPacketInfo>::deserialize(BinaryReader &stream) -> std::expected<base::ScoreboardIdentityPacketInfo, std::error_code>
{
    base::ScoreboardIdentityPacketInfo out;
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto v = Serializer<PlayerScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_id = *v;
    }
    return out;
}

void Serializer<v2168::ScoreboardIdentityPacketInfo>::serialize(BinaryWriter &stream, const v2168::ScoreboardIdentityPacketInfo &value)
{
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write<bool>(value.player_id.has_value());
    if (value.player_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.player_id));
    }
}

auto Serializer<v2168::ScoreboardIdentityPacketInfo>::deserialize(BinaryReader &stream) -> std::expected<v2168::ScoreboardIdentityPacketInfo, std::error_code>
{
    v2168::ScoreboardIdentityPacketInfo out;
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.player_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::SetScorePacket::RemovedScorePacketInfo>::serialize(BinaryWriter &stream, const base::SetScorePacket::RemovedScorePacketInfo &value)
{
    Serializer<ScoreboardId>::serialize(stream, value.scoreboard_id);
    stream.write(value.objective_name);
    stream.write<std::int32_t>(value.score_value);
}

auto Serializer<base::SetScorePacket::RemovedScorePacketInfo>::deserialize(BinaryReader &stream) -> std::expected<base::SetScorePacket::RemovedScorePacketInfo, std::error_code>
{
    base::SetScorePacket::RemovedScorePacketInfo out;
    {
        auto v = Serializer<ScoreboardId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scoreboard_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score_value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::SetScorePacket>::serialize(BinaryWriter &stream, const base::SetScorePacket &value)
{
    stream.write<std::uint8_t>(value.type);
    if ((value.type) == (ScorePacketType::Change)) {
        stream.writeVarInt<std::uint32_t>(value.score_info.size());
        for (const auto &e0 : value.score_info) {
            Serializer<ScorePacketInfo>::serialize(stream, e0);
        }
    }
    if ((value.type) == (ScorePacketType::Remove)) {
        stream.writeVarInt<std::uint32_t>(value.removed_score_info.size());
        for (const auto &e0 : value.removed_score_info) {
            Serializer<base::SetScorePacket::RemovedScorePacketInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<base::SetScorePacket>::deserialize(BinaryReader &stream) -> std::expected<base::SetScorePacket, std::error_code>
{
    base::SetScorePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<ScorePacketType>(*v);
    }
    if ((out.type) == (ScorePacketType::Change)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.score_info.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.score_info.emplace_back();
                auto v = Serializer<ScorePacketInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.score_info.back() = *v;
            }
        }
    }
    if ((out.type) == (ScorePacketType::Remove)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.removed_score_info.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.removed_score_info.emplace_back();
                auto v = Serializer<base::SetScorePacket::RemovedScorePacketInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.removed_score_info.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v2168::SetScorePacket>::serialize(BinaryWriter &stream, const v2168::SetScorePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.score_info.size());
    for (const auto &e0 : value.score_info) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v2168::RemoveScore>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v2168::ChangePlayerScore>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<v2168::ChangeEntityScore>::serialize(stream, std::get<2>(e0));
                break;
            }
            case 3: {
                Serializer<v2168::ChangeFakePlayerScore>::serialize(stream, std::get<3>(e0));
                break;
            }
        }
    }
}

auto Serializer<v2168::SetScorePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::SetScorePacket, std::error_code>
{
    v2168::SetScorePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.score_info.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.score_info.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v2168::RemoveScore, v2168::ChangePlayerScore, v2168::ChangeEntityScore, v2168::ChangeFakePlayerScore> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v2168::RemoveScore, v2168::ChangePlayerScore, v2168::ChangeEntityScore, v2168::ChangeFakePlayerScore>> alt1{};
                    {
                        auto v = Serializer<v2168::RemoveScore>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v2168::RemoveScore, v2168::ChangePlayerScore, v2168::ChangeEntityScore, v2168::ChangeFakePlayerScore>> alt1{};
                    {
                        auto v = Serializer<v2168::ChangePlayerScore>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v2168::RemoveScore, v2168::ChangePlayerScore, v2168::ChangeEntityScore, v2168::ChangeFakePlayerScore>> alt1{};
                    {
                        auto v = Serializer<v2168::ChangeEntityScore>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                case 3: {
                    std::variant_alternative_t<3, std::variant<v2168::RemoveScore, v2168::ChangePlayerScore, v2168::ChangeEntityScore, v2168::ChangeFakePlayerScore>> alt1{};
                    {
                        auto v = Serializer<v2168::ChangeFakePlayerScore>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<3>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.score_info.back() = var1;
        }
    }
    return out;
}

void Serializer<base::SetScoreboardIdentityPacket>::serialize(BinaryWriter &stream, const base::SetScoreboardIdentityPacket &value)
{
    stream.write<std::uint8_t>(value.type);
    if ((value.type) == (ScoreboardIdentityPacketType::Update)) {
        stream.writeVarInt<std::uint32_t>(value.identity_info.size());
        for (const auto &e0 : value.identity_info) {
            Serializer<base::ScoreboardIdentityPacketInfo>::serialize(stream, e0);
        }
    }
    if ((value.type) == (ScoreboardIdentityPacketType::Remove)) {
        stream.writeVarInt<std::uint32_t>(value.removed_identity_info.size());
        for (const auto &e0 : value.removed_identity_info) {
            Serializer<ScoreboardId>::serialize(stream, e0);
        }
    }
}

auto Serializer<base::SetScoreboardIdentityPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SetScoreboardIdentityPacket, std::error_code>
{
    base::SetScoreboardIdentityPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<ScoreboardIdentityPacketType>(*v);
    }
    if ((out.type) == (ScoreboardIdentityPacketType::Update)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.identity_info.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.identity_info.emplace_back();
                auto v = Serializer<base::ScoreboardIdentityPacketInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.identity_info.back() = *v;
            }
        }
    }
    if ((out.type) == (ScoreboardIdentityPacketType::Remove)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.removed_identity_info.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.removed_identity_info.emplace_back();
                auto v = Serializer<ScoreboardId>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.removed_identity_info.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v2168::SetScoreboardIdentityPacket>::serialize(BinaryWriter &stream, const v2168::SetScoreboardIdentityPacket &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.writeVarInt<std::uint32_t>(value.identity_info.size());
    for (const auto &e0 : value.identity_info) {
        Serializer<v2168::ScoreboardIdentityPacketInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2168::SetScoreboardIdentityPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::SetScoreboardIdentityPacket, std::error_code>
{
    v2168::SetScoreboardIdentityPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<ScoreboardIdentityPacketType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.identity_info.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.identity_info.emplace_back();
            auto v = Serializer<v2168::ScoreboardIdentityPacketInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.identity_info.back() = *v;
        }
    }
    return out;
}

void Serializer<RemoveObjectivePacket>::serialize(BinaryWriter &stream, const RemoveObjectivePacket &value)
{
    stream.write(value.objective_name);
}

auto Serializer<RemoveObjectivePacket>::deserialize(BinaryReader &stream) -> std::expected<RemoveObjectivePacket, std::error_code>
{
    RemoveObjectivePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    return out;
}

void Serializer<SetDisplayObjectivePacket>::serialize(BinaryWriter &stream, const SetDisplayObjectivePacket &value)
{
    stream.write(value.display_slot_name);
    stream.write(value.objective_name);
    stream.write(value.objective_display_name);
    stream.write(value.criteria_name);
    stream.writeVarInt<std::int32_t>(value.sort_order);
}

auto Serializer<SetDisplayObjectivePacket>::deserialize(BinaryReader &stream) -> std::expected<SetDisplayObjectivePacket, std::error_code>
{
    SetDisplayObjectivePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_slot_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_display_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.criteria_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.sort_order = static_cast<ObjectiveSortOrder>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
