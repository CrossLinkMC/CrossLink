#include <bedrock/protocol/skin.h>

namespace bedrock::protocol {


void Serializer<ArmSizeType>::serialize(BinaryWriter &stream, ArmSizeType value)
{
    stream.write(enum_name(value));
}

auto Serializer<ArmSizeType>::deserialize(BinaryReader &stream) -> std::expected<ArmSizeType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<ArmSizeType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<base::PieceType>::serialize(BinaryWriter &stream, base::PieceType value)
{
    stream.write(enum_name(value));
}

auto Serializer<base::PieceType>::deserialize(BinaryReader &stream) -> std::expected<base::PieceType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<base::PieceType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v2225::PieceType>::serialize(BinaryWriter &stream, v2225::PieceType value)
{
    stream.write(enum_name(value));
}

auto Serializer<v2225::PieceType>::deserialize(BinaryReader &stream) -> std::expected<v2225::PieceType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v2225::PieceType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<legacy::PieceType>::serialize(BinaryWriter &stream, legacy::PieceType value)
{
    stream.write(enum_name(value));
}

auto Serializer<legacy::PieceType>::deserialize(BinaryReader &stream) -> std::expected<legacy::PieceType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<legacy::PieceType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<TrustedSkinFlag>::serialize(BinaryWriter &stream, TrustedSkinFlag value)
{
    stream.write(enum_name(value));
}

auto Serializer<TrustedSkinFlag>::deserialize(BinaryReader &stream) -> std::expected<TrustedSkinFlag, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<TrustedSkinFlag>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<SkinImage>::serialize(BinaryWriter &stream, const SkinImage &value)
{
    stream.write<std::uint32_t>(value.width);
    stream.write<std::uint32_t>(value.height);
    stream.write(value.image_bytes);
}

auto Serializer<SkinImage>::deserialize(BinaryReader &stream) -> std::expected<SkinImage, std::error_code>
{
    SkinImage out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.width = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.image_bytes = *v;
    }
    return out;
}

void Serializer<AnimatedImageData>::serialize(BinaryWriter &stream, const AnimatedImageData &value)
{
    Serializer<SkinImage>::serialize(stream, value.image);
    stream.writeVarInt<std::uint32_t>(value.type);
    stream.write<float>(value.frames);
    stream.writeVarInt<std::uint32_t>(value.animation_expression);
}

auto Serializer<AnimatedImageData>::deserialize(BinaryReader &stream) -> std::expected<AnimatedImageData, std::error_code>
{
    AnimatedImageData out;
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.image = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<AnimatedTextureType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.frames = static_cast<float>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.animation_expression = static_cast<AnimationExpression>(*v);
    }
    return out;
}

void Serializer<legacy::AnimatedImageData>::serialize(BinaryWriter &stream, const legacy::AnimatedImageData &value)
{
    stream.write<std::uint32_t>(value.image_width);
    stream.write<std::uint32_t>(value.image_height);
    stream.write(value.image_bytes);
    stream.write<std::uint32_t>(value.type);
    stream.write<float>(value.frames);
    stream.write<std::uint32_t>(value.animation_expression);
}

auto Serializer<legacy::AnimatedImageData>::deserialize(BinaryReader &stream) -> std::expected<legacy::AnimatedImageData, std::error_code>
{
    legacy::AnimatedImageData out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.image_width = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.image_height = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.image_bytes = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<AnimatedTextureType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.frames = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.animation_expression = static_cast<AnimationExpression>(*v);
    }
    return out;
}

void Serializer<base::SerializedPersonaPieceHandle>::serialize(BinaryWriter &stream, const base::SerializedPersonaPieceHandle &value)
{
    stream.write(value.piece_id);
    stream.write<std::uint32_t>(value.piece_type);
    Serializer<UUID>::serialize(stream, value.pack_id);
    stream.write<bool>(value.is_default_piece);
    stream.write(value.product_id);
}

auto Serializer<base::SerializedPersonaPieceHandle>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedPersonaPieceHandle, std::error_code>
{
    base::SerializedPersonaPieceHandle out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.piece_id = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.piece_type = static_cast<base::PieceType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_default_piece = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.product_id = *v;
    }
    return out;
}

void Serializer<v2225::SerializedPersonaPieceHandle>::serialize(BinaryWriter &stream, const v2225::SerializedPersonaPieceHandle &value)
{
    stream.write(value.piece_id);
    stream.write<std::uint32_t>(value.piece_type);
    Serializer<UUID>::serialize(stream, value.pack_id);
    stream.write<bool>(value.is_default_piece);
    stream.write(value.product_id);
}

auto Serializer<v2225::SerializedPersonaPieceHandle>::deserialize(BinaryReader &stream) -> std::expected<v2225::SerializedPersonaPieceHandle, std::error_code>
{
    v2225::SerializedPersonaPieceHandle out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.piece_id = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.piece_type = static_cast<v2225::PieceType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_default_piece = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.product_id = *v;
    }
    return out;
}

void Serializer<legacy::SerializedPersonaPieceHandle>::serialize(BinaryWriter &stream, const legacy::SerializedPersonaPieceHandle &value)
{
    stream.write(value.piece_id);
    Serializer<legacy::PieceType>::serialize(stream, value.piece_type);
    stream.write(value.pack_id);
    stream.write<bool>(value.is_default_piece);
    stream.write(value.product_id);
}

auto Serializer<legacy::SerializedPersonaPieceHandle>::deserialize(BinaryReader &stream) -> std::expected<legacy::SerializedPersonaPieceHandle, std::error_code>
{
    legacy::SerializedPersonaPieceHandle out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.piece_id = *v;
    }
    {
        auto v = Serializer<legacy::PieceType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.piece_type = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_default_piece = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.product_id = *v;
    }
    return out;
}

void Serializer<TintMapColor>::serialize(BinaryWriter &stream, const TintMapColor &value)
{
    for (const auto &e0 : value.colors) {
        stream.write<std::int32_t>(e0);
    }
}

auto Serializer<TintMapColor>::deserialize(BinaryReader &stream) -> std::expected<TintMapColor, std::error_code>
{
    TintMapColor out;
    {
        for (std::size_t i0 = 0; i0 < 4; ++i0) {
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.colors[i0] = static_cast<Color>(*v);
        }
    }
    return out;
}

void Serializer<legacy::TintMapColor>::serialize(BinaryWriter &stream, const legacy::TintMapColor &value)
{
    Serializer<legacy::PieceType>::serialize(stream, value.piece_type);
    stream.write<std::uint32_t>(value.colors.size());
    for (const auto &e0 : value.colors) {
        stream.write(e0);
    }
}

auto Serializer<legacy::TintMapColor>::deserialize(BinaryReader &stream) -> std::expected<legacy::TintMapColor, std::error_code>
{
    legacy::TintMapColor out;
    {
        auto v = Serializer<legacy::PieceType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.piece_type = *v;
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.colors.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.colors.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.colors.back() = *v;
        }
    }
    return out;
}

void Serializer<legacy::SerializedSkinRef>::serialize(BinaryWriter &stream, const legacy::SerializedSkinRef &value)
{
    stream.write(value.id);
    stream.write(value.play_fab_id);
    stream.write(value.resource_patch);
    stream.write<std::uint32_t>(value.image_width);
    stream.write<std::uint32_t>(value.image_height);
    stream.write(value.image_bytes);
    stream.write<std::uint32_t>(value.animated_image_data.size());
    for (const auto &e0 : value.animated_image_data) {
        Serializer<legacy::AnimatedImageData>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.cape_image_width);
    stream.write<std::uint32_t>(value.cape_image_height);
    stream.write(value.cape_image_bytes);
    stream.write(value.geometry_data);
    stream.write(value.geometry_data_min_engine_version);
    stream.write(value.animation_data);
    stream.write(value.cape_id);
    stream.write(value.full_id);
    Serializer<ArmSizeType>::serialize(stream, value.arm_size);
    stream.write(value.skin_color);
    stream.write<std::uint32_t>(value.persona_pieces.size());
    for (const auto &e0 : value.persona_pieces) {
        Serializer<legacy::SerializedPersonaPieceHandle>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.piece_tint_colors.size());
    for (const auto &e0 : value.piece_tint_colors) {
        Serializer<legacy::TintMapColor>::serialize(stream, e0);
    }
    stream.write<bool>(value.is_premium);
    stream.write<bool>(value.is_persona);
    stream.write<bool>(value.is_persona_cape_on_classic_skin);
    stream.write<bool>(value.is_primary_user);
    stream.write<bool>(value.overrides_player_appearance);
}

auto Serializer<legacy::SerializedSkinRef>::deserialize(BinaryReader &stream) -> std::expected<legacy::SerializedSkinRef, std::error_code>
{
    legacy::SerializedSkinRef out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.play_fab_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_patch = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.image_width = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.image_height = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.image_bytes = *v;
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.animated_image_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.animated_image_data.emplace_back();
            auto v = Serializer<legacy::AnimatedImageData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.animated_image_data.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.cape_image_width = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.cape_image_height = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cape_image_bytes = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data_min_engine_version = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.animation_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cape_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.full_id = *v;
    }
    {
        auto v = Serializer<ArmSizeType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.arm_size = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.skin_color = *v;
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.persona_pieces.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.persona_pieces.emplace_back();
            auto v = Serializer<legacy::SerializedPersonaPieceHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.persona_pieces.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.piece_tint_colors.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.piece_tint_colors.emplace_back();
            auto v = Serializer<legacy::TintMapColor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.piece_tint_colors.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_premium = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona_cape_on_classic_skin = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_primary_user = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.overrides_player_appearance = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::SerializedSkinRef>::serialize(BinaryWriter &stream, const base::SerializedSkinRef &value)
{
    stream.write(value.id);
    stream.write(value.play_fab_id);
    stream.write(value.resource_patch);
    Serializer<SkinImage>::serialize(stream, value.image_data);
    stream.writeVarInt<std::uint32_t>(value.animated_image_data.size());
    for (const auto &e0 : value.animated_image_data) {
        Serializer<AnimatedImageData>::serialize(stream, e0);
    }
    Serializer<SkinImage>::serialize(stream, value.cape_image_data);
    stream.write(value.geometry_data);
    stream.write(value.geometry_data_min_engine_version);
    stream.write(value.animation_data);
    stream.write(value.cape_id);
    stream.write(value.full_id);
    stream.write<std::uint8_t>(value.arm_size);
    stream.write<std::int32_t>(value.skin_color);
    stream.writeVarInt<std::uint32_t>(value.persona_pieces.size());
    for (const auto &e0 : value.persona_pieces) {
        Serializer<base::SerializedPersonaPieceHandle>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.piece_tint_colors.size());
    for (const auto &[k0, v0] : value.piece_tint_colors) {
        Serializer<base::PieceType>::serialize(stream, k0);
        Serializer<TintMapColor>::serialize(stream, v0);
    }
    stream.write<bool>(value.is_premium);
    stream.write<bool>(value.is_persona);
    stream.write<bool>(value.is_persona_cape_on_classic_skin);
    stream.write<bool>(value.is_primary_user);
    stream.write<bool>(value.overrides_player_appearance);
    Serializer<TrustedSkinFlag>::serialize(stream, value.trusted_skin_flag);
}

auto Serializer<base::SerializedSkinRef>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedSkinRef, std::error_code>
{
    base::SerializedSkinRef out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.play_fab_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_patch = *v;
    }
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.image_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.animated_image_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.animated_image_data.emplace_back();
            auto v = Serializer<AnimatedImageData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.animated_image_data.back() = *v;
        }
    }
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.cape_image_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data_min_engine_version = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.animation_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cape_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.full_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.arm_size = static_cast<ArmSizeType>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.skin_color = static_cast<Color>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.persona_pieces.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.persona_pieces.emplace_back();
            auto v = Serializer<base::SerializedPersonaPieceHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.persona_pieces.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.piece_tint_colors.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            base::PieceType key0{};
            {
                auto v = Serializer<base::PieceType>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<TintMapColor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.piece_tint_colors[key0] = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_premium = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona_cape_on_classic_skin = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_primary_user = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.overrides_player_appearance = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<TrustedSkinFlag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.trusted_skin_flag = *v;
    }
    return out;
}

void Serializer<v2168::SerializedSkinRef>::serialize(BinaryWriter &stream, const v2168::SerializedSkinRef &value)
{
    stream.write(value.id);
    stream.write(value.play_fab_id);
    stream.write(value.resource_patch);
    Serializer<SkinImage>::serialize(stream, value.image_data);
    stream.writeVarInt<std::uint32_t>(value.animated_image_data.size());
    for (const auto &e0 : value.animated_image_data) {
        Serializer<AnimatedImageData>::serialize(stream, e0);
    }
    Serializer<SkinImage>::serialize(stream, value.cape_image_data);
    stream.write(value.geometry_data);
    stream.write(value.geometry_data_min_engine_version);
    stream.write(value.animation_data);
    stream.write(value.cape_id);
    stream.write(value.full_id);
    stream.write<std::uint8_t>(value.arm_size);
    stream.write<std::int32_t>(value.skin_color);
    stream.writeVarInt<std::uint32_t>(value.persona_pieces.size());
    for (const auto &e0 : value.persona_pieces) {
        Serializer<base::SerializedPersonaPieceHandle>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.piece_tint_colors.size());
    for (const auto &[k0, v0] : value.piece_tint_colors) {
        Serializer<base::PieceType>::serialize(stream, k0);
        Serializer<TintMapColor>::serialize(stream, v0);
    }
    stream.write<bool>(value.is_premium);
    stream.write<bool>(value.is_persona);
    stream.write<bool>(value.is_persona_cape_on_classic_skin);
    stream.write<bool>(value.is_primary_user);
    stream.write<bool>(value.overrides_player_appearance);
    Serializer<TrustedSkinFlag>::serialize(stream, value.trusted_skin_flag);
    stream.write(value.profile_hash);
}

auto Serializer<v2168::SerializedSkinRef>::deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedSkinRef, std::error_code>
{
    v2168::SerializedSkinRef out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.play_fab_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_patch = *v;
    }
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.image_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.animated_image_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.animated_image_data.emplace_back();
            auto v = Serializer<AnimatedImageData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.animated_image_data.back() = *v;
        }
    }
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.cape_image_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data_min_engine_version = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.animation_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cape_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.full_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.arm_size = static_cast<ArmSizeType>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.skin_color = static_cast<Color>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.persona_pieces.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.persona_pieces.emplace_back();
            auto v = Serializer<base::SerializedPersonaPieceHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.persona_pieces.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.piece_tint_colors.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            base::PieceType key0{};
            {
                auto v = Serializer<base::PieceType>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<TintMapColor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.piece_tint_colors[key0] = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_premium = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona_cape_on_classic_skin = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_primary_user = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.overrides_player_appearance = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<TrustedSkinFlag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.trusted_skin_flag = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.profile_hash = *v;
    }
    return out;
}

void Serializer<v2225::SerializedSkinRef>::serialize(BinaryWriter &stream, const v2225::SerializedSkinRef &value)
{
    stream.write(value.id);
    stream.write(value.resource_patch);
    Serializer<SkinImage>::serialize(stream, value.image_data);
    stream.writeVarInt<std::uint32_t>(value.animated_image_data.size());
    for (const auto &e0 : value.animated_image_data) {
        Serializer<AnimatedImageData>::serialize(stream, e0);
    }
    Serializer<SkinImage>::serialize(stream, value.cape_image_data);
    stream.write(value.geometry_data);
    stream.write(value.geometry_data_min_engine_version);
    stream.write(value.animation_data);
    stream.write(value.cape_id);
    stream.write(value.full_id);
    stream.write<std::uint8_t>(value.arm_size);
    stream.write<std::int32_t>(value.skin_color);
    stream.writeVarInt<std::uint32_t>(value.persona_pieces.size());
    for (const auto &e0 : value.persona_pieces) {
        Serializer<v2225::SerializedPersonaPieceHandle>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.piece_tint_colors.size());
    for (const auto &[k0, v0] : value.piece_tint_colors) {
        Serializer<v2225::PieceType>::serialize(stream, k0);
        Serializer<TintMapColor>::serialize(stream, v0);
    }
    stream.write<bool>(value.is_premium);
    stream.write<bool>(value.is_persona);
    stream.write<bool>(value.is_persona_cape_on_classic_skin);
    stream.write<bool>(value.is_primary_user);
    stream.write<bool>(value.overrides_player_appearance);
    Serializer<TrustedSkinFlag>::serialize(stream, value.trusted_skin_flag);
    stream.write(value.profile_hash);
}

auto Serializer<v2225::SerializedSkinRef>::deserialize(BinaryReader &stream) -> std::expected<v2225::SerializedSkinRef, std::error_code>
{
    v2225::SerializedSkinRef out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_patch = *v;
    }
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.image_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.animated_image_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.animated_image_data.emplace_back();
            auto v = Serializer<AnimatedImageData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.animated_image_data.back() = *v;
        }
    }
    {
        auto v = Serializer<SkinImage>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.cape_image_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.geometry_data_min_engine_version = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.animation_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cape_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.full_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.arm_size = static_cast<ArmSizeType>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.skin_color = static_cast<Color>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.persona_pieces.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.persona_pieces.emplace_back();
            auto v = Serializer<v2225::SerializedPersonaPieceHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.persona_pieces.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.piece_tint_colors.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            v2225::PieceType key0{};
            {
                auto v = Serializer<v2225::PieceType>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<TintMapColor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.piece_tint_colors[key0] = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_premium = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_persona_cape_on_classic_skin = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_primary_user = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.overrides_player_appearance = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<TrustedSkinFlag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.trusted_skin_flag = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.profile_hash = *v;
    }
    return out;
}

void Serializer<base::PlayerSkinPacket>::serialize(BinaryWriter &stream, const base::PlayerSkinPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    Serializer<legacy::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write(value.localized_new_skin_name);
    stream.write(value.localized_old_skin_name);
    stream.write<bool>(value.trusted_skin);
}

auto Serializer<base::PlayerSkinPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerSkinPacket, std::error_code>
{
    base::PlayerSkinPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = Serializer<legacy::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_new_skin_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_old_skin_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.trusted_skin = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::PlayerSkinPacket>::serialize(BinaryWriter &stream, const v944::PlayerSkinPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    Serializer<base::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write(value.localized_new_skin_name);
    stream.write(value.localized_old_skin_name);
}

auto Serializer<v944::PlayerSkinPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::PlayerSkinPacket, std::error_code>
{
    v944::PlayerSkinPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = Serializer<base::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_new_skin_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_old_skin_name = *v;
    }
    return out;
}

void Serializer<v2168::PlayerSkinPacket>::serialize(BinaryWriter &stream, const v2168::PlayerSkinPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    Serializer<v2168::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write(value.localized_new_skin_name);
    stream.write(value.localized_old_skin_name);
}

auto Serializer<v2168::PlayerSkinPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerSkinPacket, std::error_code>
{
    v2168::PlayerSkinPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = Serializer<v2168::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_new_skin_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_old_skin_name = *v;
    }
    return out;
}

void Serializer<v2225::PlayerSkinPacket>::serialize(BinaryWriter &stream, const v2225::PlayerSkinPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    Serializer<v2225::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write(value.localized_new_skin_name);
    stream.write(value.localized_old_skin_name);
}

auto Serializer<v2225::PlayerSkinPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerSkinPacket, std::error_code>
{
    v2225::PlayerSkinPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = Serializer<v2225::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_new_skin_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.localized_old_skin_name = *v;
    }
    return out;
}

void Serializer<EmotePacket>::serialize(BinaryWriter &stream, const EmotePacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.piece_id);
    stream.writeVarInt<std::uint32_t>(value.emote_ticks);
    stream.write(value.xuid);
    stream.write(value.platform_id);
    stream.write<std::uint8_t>(value.flags);
}

auto Serializer<EmotePacket>::deserialize(BinaryReader &stream) -> std::expected<EmotePacket, std::error_code>
{
    EmotePacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.piece_id = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.emote_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.flags = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<EmoteListPacket>::serialize(BinaryWriter &stream, const EmoteListPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.emote_piece_ids.size());
    for (const auto &e0 : value.emote_piece_ids) {
        Serializer<UUID>::serialize(stream, e0);
    }
}

auto Serializer<EmoteListPacket>::deserialize(BinaryReader &stream) -> std::expected<EmoteListPacket, std::error_code>
{
    EmoteListPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.emote_piece_ids.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.emote_piece_ids.emplace_back();
            auto v = Serializer<UUID>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.emote_piece_ids.back() = *v;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
