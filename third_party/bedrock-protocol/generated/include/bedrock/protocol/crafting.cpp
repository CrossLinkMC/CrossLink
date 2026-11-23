#include <bedrock/protocol/crafting.h>

namespace bedrock::protocol {


void Serializer<RecipeNetId>::serialize(BinaryWriter &stream, const RecipeNetId &value)
{
    stream.writeVarInt<std::uint32_t>(value.raw_id);
}

auto Serializer<RecipeNetId>::deserialize(BinaryReader &stream) -> std::expected<RecipeNetId, std::error_code>
{
    RecipeNetId out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<CreativeItemNetId>::serialize(BinaryWriter &stream, const CreativeItemNetId &value)
{
    stream.writeVarInt<std::uint32_t>(value.raw_id);
}

auto Serializer<CreativeItemNetId>::deserialize(BinaryReader &stream) -> std::expected<CreativeItemNetId, std::error_code>
{
    CreativeItemNetId out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(BinaryWriter &stream, const base::SerializedNetworkItemInstanceDescriptor &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if ((value.id) != (0)) {
        stream.write<std::uint16_t>(value.stack_size);
        stream.writeVarInt<std::uint32_t>(value.aux_value);
        stream.writeVarInt<std::int32_t>(value.block_runtime_id);
        stream.write(value.user_data_buffer);
    }
}

auto Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedNetworkItemInstanceDescriptor, std::error_code>
{
    base::SerializedNetworkItemInstanceDescriptor out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if ((out.id) != (0)) {
        {
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.stack_size = static_cast<std::uint16_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.aux_value = static_cast<std::uint32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.block_runtime_id = static_cast<BlockRuntimeId>(*v);
        }
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.user_data_buffer = *v;
        }
    }
    return out;
}

void Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::serialize(BinaryWriter &stream, const v2168::SerializedNetworkItemInstanceDescriptor &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    stream.write<std::uint16_t>(value.stack_size);
    stream.writeVarInt<std::uint32_t>(value.aux_value);
    stream.writeVarInt<std::int32_t>(value.block_runtime_id);
    stream.write(value.user_data_buffer);
}

auto Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedNetworkItemInstanceDescriptor, std::error_code>
{
    v2168::SerializedNetworkItemInstanceDescriptor out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.aux_value = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.block_runtime_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.user_data_buffer = *v;
    }
    return out;
}

void Serializer<base::ItemDescriptor>::serialize(BinaryWriter &stream, const base::ItemDescriptor &value)
{
    stream.write<std::uint8_t>(value.internal_type);
    if ((value.internal_type) == (base::ItemDescriptor::InternalType::Default)) {
        stream.write<std::int16_t>(value.id);
    }
    if (((value.internal_type) == (base::ItemDescriptor::InternalType::Molang)) || ((value.internal_type) == (base::ItemDescriptor::InternalType::ItemTag)) || ((value.internal_type) == (base::ItemDescriptor::InternalType::Deferred)) || ((value.internal_type) == (base::ItemDescriptor::InternalType::ComplexAlias))) {
        stream.write(value.name);
    }
    if ((value.internal_type) == (base::ItemDescriptor::InternalType::Molang)) {
        stream.write<std::uint8_t>(value.molang_version);
    }
    if (((value.internal_type) == (base::ItemDescriptor::InternalType::Deferred)) || (((value.internal_type) == (base::ItemDescriptor::InternalType::Default)) && ((value.id) != (0)))) {
        stream.write<std::int16_t>(value.aux_value);
    }
}

auto Serializer<base::ItemDescriptor>::deserialize(BinaryReader &stream) -> std::expected<base::ItemDescriptor, std::error_code>
{
    base::ItemDescriptor out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.internal_type = static_cast<base::ItemDescriptor::InternalType>(*v);
    }
    if ((out.internal_type) == (base::ItemDescriptor::InternalType::Default)) {
        {
            auto v = stream.read<std::int16_t>();
            if (!v) return std::unexpected(v.error());
            out.id = static_cast<std::int16_t>(*v);
        }
    }
    if (((out.internal_type) == (base::ItemDescriptor::InternalType::Molang)) || ((out.internal_type) == (base::ItemDescriptor::InternalType::ItemTag)) || ((out.internal_type) == (base::ItemDescriptor::InternalType::Deferred)) || ((out.internal_type) == (base::ItemDescriptor::InternalType::ComplexAlias))) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.name = *v;
        }
    }
    if ((out.internal_type) == (base::ItemDescriptor::InternalType::Molang)) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.molang_version = static_cast<std::uint8_t>(*v);
        }
    }
    if (((out.internal_type) == (base::ItemDescriptor::InternalType::Deferred)) || (((out.internal_type) == (base::ItemDescriptor::InternalType::Default)) && ((out.id) != (0)))) {
        {
            auto v = stream.read<std::int16_t>();
            if (!v) return std::unexpected(v.error());
            out.aux_value = static_cast<std::int16_t>(*v);
        }
    }
    return out;
}

void Serializer<base::SerializedRecipeIngredient>::serialize(BinaryWriter &stream, const base::SerializedRecipeIngredient &value)
{
    Serializer<base::ItemDescriptor>::serialize(stream, value.descriptor);
    stream.writeVarInt<std::int32_t>(value.stack_size);
}

auto Serializer<base::SerializedRecipeIngredient>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedRecipeIngredient, std::error_code>
{
    base::SerializedRecipeIngredient out;
    {
        auto v = Serializer<base::ItemDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.descriptor = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    return out;
}

void Serializer<v2168::SerializedRecipeIngredient>::serialize(BinaryWriter &stream, const v2168::SerializedRecipeIngredient &value)
{
    stream.writeVarInt<std::uint32_t>(value.descriptor.size());
    for (const auto &[k0, v0] : value.descriptor) {
        stream.write(k0);
        stream.write(v0);
    }
    stream.writeVarInt<std::int32_t>(value.aux_value);
    stream.writeVarInt<std::int32_t>(value.stack_size);
}

auto Serializer<v2168::SerializedRecipeIngredient>::deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedRecipeIngredient, std::error_code>
{
    v2168::SerializedRecipeIngredient out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.descriptor.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.descriptor[key0] = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.aux_value = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    return out;
}

void Serializer<base::SerializedRecipeUnlockingRequirement>::serialize(BinaryWriter &stream, const base::SerializedRecipeUnlockingRequirement &value)
{
    stream.write<std::uint8_t>(value.context);
    if ((value.context) == (base::SerializedRecipeUnlockingRequirement::UnlockingContext::None)) {
        stream.writeVarInt<std::uint32_t>(value.ingredients.size());
        for (const auto &e0 : value.ingredients) {
            Serializer<base::SerializedRecipeIngredient>::serialize(stream, e0);
        }
    }
}

auto Serializer<base::SerializedRecipeUnlockingRequirement>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedRecipeUnlockingRequirement, std::error_code>
{
    base::SerializedRecipeUnlockingRequirement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.context = static_cast<base::SerializedRecipeUnlockingRequirement::UnlockingContext>(*v);
    }
    if ((out.context) == (base::SerializedRecipeUnlockingRequirement::UnlockingContext::None)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.ingredients.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.ingredients.emplace_back();
                auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.ingredients.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v2168::SerializedRecipeUnlockingRequirement>::serialize(BinaryWriter &stream, const v2168::SerializedRecipeUnlockingRequirement &value)
{
    stream.writeVarInt<std::int32_t>(value.context);
    stream.write<bool>(value.ingredients.has_value());
    if (value.ingredients.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.ingredients).size());
        for (const auto &e0 : (*value.ingredients)) {
            Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, e0);
        }
    }
}

auto Serializer<v2168::SerializedRecipeUnlockingRequirement>::deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedRecipeUnlockingRequirement, std::error_code>
{
    v2168::SerializedRecipeUnlockingRequirement out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.context = static_cast<v2168::SerializedRecipeUnlockingRequirement::UnlockingContext>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::SerializedRecipeIngredient> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.ingredients = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::ShapedRecipePayload>::serialize(BinaryWriter &stream, const base::ShapedRecipePayload &value)
{
    stream.write(value.recipe_id);
    stream.writeVarInt<std::int32_t>(value.width);
    stream.writeVarInt<std::int32_t>(value.height);
    for (const auto &e0 : value.ingredients) {
        Serializer<base::SerializedRecipeIngredient>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.results.size());
    for (const auto &e0 : value.results) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.tag);
    stream.writeVarInt<std::int32_t>(value.priority);
    stream.write<bool>(value.assume_symmetry);
    Serializer<base::SerializedRecipeUnlockingRequirement>::serialize(stream, value.unlocking_requirement);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<base::ShapedRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<base::ShapedRecipePayload, std::error_code>
{
    base::ShapedRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<std::int32_t>(*v);
    }
    {
        out.ingredients.clear();
        for (auto rep0 = (out.width) * (out.height); rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.results.emplace_back();
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.results.back() = *v;
        }
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.assume_symmetry = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<base::SerializedRecipeUnlockingRequirement>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.unlocking_requirement = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<v2168::ShapedRecipePayload>::serialize(BinaryWriter &stream, const v2168::ShapedRecipePayload &value)
{
    stream.write(value.recipe_id);
    stream.writeVarInt<std::int32_t>(value.width);
    stream.writeVarInt<std::int32_t>(value.height);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.results.size());
    for (const auto &e0 : value.results) {
        Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.tag);
    stream.writeVarInt<std::int32_t>(value.priority);
    stream.write<bool>(value.assume_symmetry);
    stream.write<bool>(value.unlocking_requirement.has_value());
    if (value.unlocking_requirement.has_value()) {
        Serializer<v2168::SerializedRecipeUnlockingRequirement>::serialize(stream, (*value.unlocking_requirement));
    }
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<v2168::ShapedRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::ShapedRecipePayload, std::error_code>
{
    v2168::ShapedRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.results.emplace_back();
            auto v = Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.results.back() = *v;
        }
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.assume_symmetry = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::SerializedRecipeUnlockingRequirement staged{};
            auto v = Serializer<v2168::SerializedRecipeUnlockingRequirement>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.unlocking_requirement = std::move(staged);
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<base::ShapelessRecipePayload>::serialize(BinaryWriter &stream, const base::ShapelessRecipePayload &value)
{
    stream.write(value.recipe_id);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<base::SerializedRecipeIngredient>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.results.size());
    for (const auto &e0 : value.results) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.tag);
    stream.writeVarInt<std::int32_t>(value.priority);
    Serializer<base::SerializedRecipeUnlockingRequirement>::serialize(stream, value.unlocking_requirement);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<base::ShapelessRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<base::ShapelessRecipePayload, std::error_code>
{
    base::ShapelessRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.results.emplace_back();
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.results.back() = *v;
        }
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::SerializedRecipeUnlockingRequirement>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.unlocking_requirement = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<v2168::ShapelessRecipePayload>::serialize(BinaryWriter &stream, const v2168::ShapelessRecipePayload &value)
{
    stream.write(value.recipe_id);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.results.size());
    for (const auto &e0 : value.results) {
        Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.tag);
    stream.writeVarInt<std::int32_t>(value.priority);
    stream.write<bool>(value.unlocking_requirement.has_value());
    if (value.unlocking_requirement.has_value()) {
        Serializer<v2168::SerializedRecipeUnlockingRequirement>::serialize(stream, (*value.unlocking_requirement));
    }
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<v2168::ShapelessRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::ShapelessRecipePayload, std::error_code>
{
    v2168::ShapelessRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.results.emplace_back();
            auto v = Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.results.back() = *v;
        }
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::SerializedRecipeUnlockingRequirement staged{};
            auto v = Serializer<v2168::SerializedRecipeUnlockingRequirement>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.unlocking_requirement = std::move(staged);
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<MultiRecipePayload>::serialize(BinaryWriter &stream, const MultiRecipePayload &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<MultiRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<MultiRecipePayload, std::error_code>
{
    MultiRecipePayload out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<base::SmithingTransformRecipePayload>::serialize(BinaryWriter &stream, const base::SmithingTransformRecipePayload &value)
{
    stream.write(value.recipe_id);
    Serializer<base::SerializedRecipeIngredient>::serialize(stream, value.template_ingredient);
    Serializer<base::SerializedRecipeIngredient>::serialize(stream, value.base_ingredient);
    Serializer<base::SerializedRecipeIngredient>::serialize(stream, value.addition_ingredient);
    Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.result);
    stream.write(value.tag);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<base::SmithingTransformRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<base::SmithingTransformRecipePayload, std::error_code>
{
    base::SmithingTransformRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.template_ingredient = *v;
    }
    {
        auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.base_ingredient = *v;
    }
    {
        auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.addition_ingredient = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.result = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<v2168::SmithingTransformRecipePayload>::serialize(BinaryWriter &stream, const v2168::SmithingTransformRecipePayload &value)
{
    stream.write(value.recipe_id);
    Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, value.template_ingredient);
    Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, value.base_ingredient);
    Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, value.addition_ingredient);
    Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.result);
    stream.write(value.tag);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<v2168::SmithingTransformRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::SmithingTransformRecipePayload, std::error_code>
{
    v2168::SmithingTransformRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.template_ingredient = *v;
    }
    {
        auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.base_ingredient = *v;
    }
    {
        auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.addition_ingredient = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.result = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<base::SmithingTrimRecipePayload>::serialize(BinaryWriter &stream, const base::SmithingTrimRecipePayload &value)
{
    stream.write(value.recipe_id);
    Serializer<base::SerializedRecipeIngredient>::serialize(stream, value.template_ingredient);
    Serializer<base::SerializedRecipeIngredient>::serialize(stream, value.base_ingredient);
    Serializer<base::SerializedRecipeIngredient>::serialize(stream, value.addition_ingredient);
    stream.write(value.tag);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<base::SmithingTrimRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<base::SmithingTrimRecipePayload, std::error_code>
{
    base::SmithingTrimRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.template_ingredient = *v;
    }
    {
        auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.base_ingredient = *v;
    }
    {
        auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.addition_ingredient = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<v2168::SmithingTrimRecipePayload>::serialize(BinaryWriter &stream, const v2168::SmithingTrimRecipePayload &value)
{
    stream.write(value.recipe_id);
    Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, value.template_ingredient);
    Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, value.base_ingredient);
    Serializer<v2168::SerializedRecipeIngredient>::serialize(stream, value.addition_ingredient);
    stream.write(value.tag);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<v2168::SmithingTrimRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::SmithingTrimRecipePayload, std::error_code>
{
    v2168::SmithingTrimRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.template_ingredient = *v;
    }
    {
        auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.base_ingredient = *v;
    }
    {
        auto v = Serializer<v2168::SerializedRecipeIngredient>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.addition_ingredient = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<PotionMixDataEntry>::serialize(BinaryWriter &stream, const PotionMixDataEntry &value)
{
    stream.writeVarInt<std::int32_t>(value.from_item_id);
    stream.writeVarInt<std::int32_t>(value.from_item_aux);
    stream.writeVarInt<std::int32_t>(value.reagent_item_id);
    stream.writeVarInt<std::int32_t>(value.reagent_item_aux);
    stream.writeVarInt<std::int32_t>(value.to_item_id);
    stream.writeVarInt<std::int32_t>(value.to_item_aux);
}

auto Serializer<PotionMixDataEntry>::deserialize(BinaryReader &stream) -> std::expected<PotionMixDataEntry, std::error_code>
{
    PotionMixDataEntry out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.from_item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.from_item_aux = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reagent_item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reagent_item_aux = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.to_item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.to_item_aux = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<ContainerMixDataEntry>::serialize(BinaryWriter &stream, const ContainerMixDataEntry &value)
{
    stream.writeVarInt<std::int32_t>(value.from_item_id);
    stream.writeVarInt<std::int32_t>(value.reagent_item_id);
    stream.writeVarInt<std::int32_t>(value.to_item_id);
}

auto Serializer<ContainerMixDataEntry>::deserialize(BinaryReader &stream) -> std::expected<ContainerMixDataEntry, std::error_code>
{
    ContainerMixDataEntry out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.from_item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reagent_item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.to_item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<MaterialReducerEntryOutput>::serialize(BinaryWriter &stream, const MaterialReducerEntryOutput &value)
{
    stream.writeVarInt<std::int32_t>(value.item_id);
    stream.writeVarInt<std::int32_t>(value.item_count);
}

auto Serializer<MaterialReducerEntryOutput>::deserialize(BinaryReader &stream) -> std::expected<MaterialReducerEntryOutput, std::error_code>
{
    MaterialReducerEntryOutput out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_count = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<MaterialReducerDataEntry>::serialize(BinaryWriter &stream, const MaterialReducerDataEntry &value)
{
    stream.writeVarInt<std::int32_t>(value.from_item_key);
    stream.writeVarInt<std::uint32_t>(value.to_item_ids_and_counts.size());
    for (const auto &e0 : value.to_item_ids_and_counts) {
        Serializer<MaterialReducerEntryOutput>::serialize(stream, e0);
    }
}

auto Serializer<MaterialReducerDataEntry>::deserialize(BinaryReader &stream) -> std::expected<MaterialReducerDataEntry, std::error_code>
{
    MaterialReducerDataEntry out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.from_item_key = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.to_item_ids_and_counts.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.to_item_ids_and_counts.emplace_back();
            auto v = Serializer<MaterialReducerEntryOutput>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.to_item_ids_and_counts.back() = *v;
        }
    }
    return out;
}

void Serializer<base::ShapedChemistryRecipePayload>::serialize(BinaryWriter &stream, const base::ShapedChemistryRecipePayload &value)
{
    stream.write(value.recipe_id);
    stream.writeVarInt<std::int32_t>(value.width);
    stream.writeVarInt<std::int32_t>(value.height);
    for (const auto &e0 : value.ingredients) {
        Serializer<base::SerializedRecipeIngredient>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.results.size());
    for (const auto &e0 : value.results) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.tag);
    stream.writeVarInt<std::int32_t>(value.priority);
    stream.write<bool>(value.assume_symmetry);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<base::ShapedChemistryRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<base::ShapedChemistryRecipePayload, std::error_code>
{
    base::ShapedChemistryRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<std::int32_t>(*v);
    }
    {
        out.ingredients.clear();
        for (auto rep0 = (out.width) * (out.height); rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.results.emplace_back();
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.results.back() = *v;
        }
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.assume_symmetry = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<base::ShapelessChemistryRecipePayload>::serialize(BinaryWriter &stream, const base::ShapelessChemistryRecipePayload &value)
{
    stream.write(value.recipe_id);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<base::SerializedRecipeIngredient>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.results.size());
    for (const auto &e0 : value.results) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.tag);
    stream.writeVarInt<std::int32_t>(value.priority);
    Serializer<RecipeNetId>::serialize(stream, value.net_id);
}

auto Serializer<base::ShapelessChemistryRecipePayload>::deserialize(BinaryReader &stream) -> std::expected<base::ShapelessChemistryRecipePayload, std::error_code>
{
    base::ShapelessChemistryRecipePayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.recipe_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.results.emplace_back();
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.results.back() = *v;
        }
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.net_id = *v;
    }
    return out;
}

void Serializer<base::CraftingDataEntry>::serialize(BinaryWriter &stream, const base::CraftingDataEntry &value)
{
    stream.writeVarInt<std::int32_t>(value.entry_type);
    if ((value.entry_type) == (base::CraftingDataEntryType::ShapelessRecipe)) {
        Serializer<base::ShapelessRecipePayload>::serialize(stream, value.shapeless_recipe);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::ShapelessChemistryRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::UserDataShapelessRecipe))) {
        Serializer<base::ShapelessChemistryRecipePayload>::serialize(stream, value.shapeless_chemistry_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::ShapedRecipe)) {
        Serializer<base::ShapedRecipePayload>::serialize(stream, value.shaped_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::ShapedChemistryRecipe)) {
        Serializer<base::ShapedChemistryRecipePayload>::serialize(stream, value.shaped_chemistry_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::MultiRecipe)) {
        Serializer<MultiRecipePayload>::serialize(stream, value.multi_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::SmithingTransformRecipe)) {
        Serializer<base::SmithingTransformRecipePayload>::serialize(stream, value.smithing_transform_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::SmithingTrimRecipe)) {
        Serializer<base::SmithingTrimRecipePayload>::serialize(stream, value.smithing_trim_recipe);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        stream.writeVarInt<std::int32_t>(value.item_data);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe)) {
        stream.writeVarInt<std::int32_t>(value.item_aux);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.item_result);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        stream.write(value.tag);
    }
}

auto Serializer<base::CraftingDataEntry>::deserialize(BinaryReader &stream) -> std::expected<base::CraftingDataEntry, std::error_code>
{
    base::CraftingDataEntry out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entry_type = static_cast<base::CraftingDataEntryType>(*v);
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::ShapelessRecipe)) {
        {
            auto v = Serializer<base::ShapelessRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_recipe = *v;
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::ShapelessChemistryRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::UserDataShapelessRecipe))) {
        {
            auto v = Serializer<base::ShapelessChemistryRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_chemistry_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::ShapedRecipe)) {
        {
            auto v = Serializer<base::ShapedRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::ShapedChemistryRecipe)) {
        {
            auto v = Serializer<base::ShapedChemistryRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_chemistry_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::MultiRecipe)) {
        {
            auto v = Serializer<MultiRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.multi_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::SmithingTransformRecipe)) {
        {
            auto v = Serializer<base::SmithingTransformRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_transform_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::SmithingTrimRecipe)) {
        {
            auto v = Serializer<base::SmithingTrimRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_trim_recipe = *v;
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.item_data = static_cast<std::int32_t>(*v);
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.item_aux = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        {
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_result = *v;
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.tag = *v;
        }
    }
    return out;
}

void Serializer<v748::CraftingDataEntry>::serialize(BinaryWriter &stream, const v748::CraftingDataEntry &value)
{
    stream.writeVarInt<std::int32_t>(value.entry_type);
    if (((value.entry_type) == (base::CraftingDataEntryType::ShapelessRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::UserDataShapelessRecipe))) {
        Serializer<base::ShapelessRecipePayload>::serialize(stream, value.shapeless_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::ShapelessChemistryRecipe)) {
        Serializer<base::ShapelessChemistryRecipePayload>::serialize(stream, value.shapeless_chemistry_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::ShapedRecipe)) {
        Serializer<base::ShapedRecipePayload>::serialize(stream, value.shaped_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::ShapedChemistryRecipe)) {
        Serializer<base::ShapedChemistryRecipePayload>::serialize(stream, value.shaped_chemistry_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::MultiRecipe)) {
        Serializer<MultiRecipePayload>::serialize(stream, value.multi_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::SmithingTransformRecipe)) {
        Serializer<base::SmithingTransformRecipePayload>::serialize(stream, value.smithing_transform_recipe);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::SmithingTrimRecipe)) {
        Serializer<base::SmithingTrimRecipePayload>::serialize(stream, value.smithing_trim_recipe);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        stream.writeVarInt<std::int32_t>(value.item_data);
    }
    if ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe)) {
        stream.writeVarInt<std::int32_t>(value.item_aux);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.item_result);
    }
    if (((value.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((value.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        stream.write(value.tag);
    }
}

auto Serializer<v748::CraftingDataEntry>::deserialize(BinaryReader &stream) -> std::expected<v748::CraftingDataEntry, std::error_code>
{
    v748::CraftingDataEntry out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entry_type = static_cast<base::CraftingDataEntryType>(*v);
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::ShapelessRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::UserDataShapelessRecipe))) {
        {
            auto v = Serializer<base::ShapelessRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::ShapelessChemistryRecipe)) {
        {
            auto v = Serializer<base::ShapelessChemistryRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_chemistry_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::ShapedRecipe)) {
        {
            auto v = Serializer<base::ShapedRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::ShapedChemistryRecipe)) {
        {
            auto v = Serializer<base::ShapedChemistryRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_chemistry_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::MultiRecipe)) {
        {
            auto v = Serializer<MultiRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.multi_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::SmithingTransformRecipe)) {
        {
            auto v = Serializer<base::SmithingTransformRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_transform_recipe = *v;
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::SmithingTrimRecipe)) {
        {
            auto v = Serializer<base::SmithingTrimRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_trim_recipe = *v;
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.item_data = static_cast<std::int32_t>(*v);
        }
    }
    if ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.item_aux = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        {
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.item_result = *v;
        }
    }
    if (((out.entry_type) == (base::CraftingDataEntryType::FurnaceRecipe)) || ((out.entry_type) == (base::CraftingDataEntryType::FurnaceAuxRecipe))) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.tag = *v;
        }
    }
    return out;
}

void Serializer<v975::CraftingDataEntry>::serialize(BinaryWriter &stream, const v975::CraftingDataEntry &value)
{
    stream.writeVarInt<std::int32_t>(value.entry_type);
    if (((value.entry_type) == (v975::CraftingDataEntryType::ShapelessRecipe)) || ((value.entry_type) == (v975::CraftingDataEntryType::UserDataShapelessRecipe))) {
        Serializer<base::ShapelessRecipePayload>::serialize(stream, value.shapeless_recipe);
    }
    if ((value.entry_type) == (v975::CraftingDataEntryType::ShapelessChemistryRecipe)) {
        Serializer<base::ShapelessChemistryRecipePayload>::serialize(stream, value.shapeless_chemistry_recipe);
    }
    if ((value.entry_type) == (v975::CraftingDataEntryType::ShapedRecipe)) {
        Serializer<base::ShapedRecipePayload>::serialize(stream, value.shaped_recipe);
    }
    if ((value.entry_type) == (v975::CraftingDataEntryType::ShapedChemistryRecipe)) {
        Serializer<base::ShapedChemistryRecipePayload>::serialize(stream, value.shaped_chemistry_recipe);
    }
    if ((value.entry_type) == (v975::CraftingDataEntryType::MultiRecipe)) {
        Serializer<MultiRecipePayload>::serialize(stream, value.multi_recipe);
    }
    if ((value.entry_type) == (v975::CraftingDataEntryType::SmithingTransformRecipe)) {
        Serializer<base::SmithingTransformRecipePayload>::serialize(stream, value.smithing_transform_recipe);
    }
    if ((value.entry_type) == (v975::CraftingDataEntryType::SmithingTrimRecipe)) {
        Serializer<base::SmithingTrimRecipePayload>::serialize(stream, value.smithing_trim_recipe);
    }
}

auto Serializer<v975::CraftingDataEntry>::deserialize(BinaryReader &stream) -> std::expected<v975::CraftingDataEntry, std::error_code>
{
    v975::CraftingDataEntry out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entry_type = static_cast<v975::CraftingDataEntryType>(*v);
    }
    if (((out.entry_type) == (v975::CraftingDataEntryType::ShapelessRecipe)) || ((out.entry_type) == (v975::CraftingDataEntryType::UserDataShapelessRecipe))) {
        {
            auto v = Serializer<base::ShapelessRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_recipe = *v;
        }
    }
    if ((out.entry_type) == (v975::CraftingDataEntryType::ShapelessChemistryRecipe)) {
        {
            auto v = Serializer<base::ShapelessChemistryRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_chemistry_recipe = *v;
        }
    }
    if ((out.entry_type) == (v975::CraftingDataEntryType::ShapedRecipe)) {
        {
            auto v = Serializer<base::ShapedRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_recipe = *v;
        }
    }
    if ((out.entry_type) == (v975::CraftingDataEntryType::ShapedChemistryRecipe)) {
        {
            auto v = Serializer<base::ShapedChemistryRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_chemistry_recipe = *v;
        }
    }
    if ((out.entry_type) == (v975::CraftingDataEntryType::MultiRecipe)) {
        {
            auto v = Serializer<MultiRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.multi_recipe = *v;
        }
    }
    if ((out.entry_type) == (v975::CraftingDataEntryType::SmithingTransformRecipe)) {
        {
            auto v = Serializer<base::SmithingTransformRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_transform_recipe = *v;
        }
    }
    if ((out.entry_type) == (v975::CraftingDataEntryType::SmithingTrimRecipe)) {
        {
            auto v = Serializer<base::SmithingTrimRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_trim_recipe = *v;
        }
    }
    return out;
}

void Serializer<base::CraftingDataPacket>::serialize(BinaryWriter &stream, const base::CraftingDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.crafting_entries.size());
    for (const auto &e0 : value.crafting_entries) {
        Serializer<base::CraftingDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.potion_mix_entries.size());
    for (const auto &e0 : value.potion_mix_entries) {
        Serializer<PotionMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.container_mix_entries.size());
    for (const auto &e0 : value.container_mix_entries) {
        Serializer<ContainerMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.material_reducer_entries.size());
    for (const auto &e0 : value.material_reducer_entries) {
        Serializer<MaterialReducerDataEntry>::serialize(stream, e0);
    }
    stream.write<bool>(value.clear_recipes);
}

auto Serializer<base::CraftingDataPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CraftingDataPacket, std::error_code>
{
    base::CraftingDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.crafting_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.crafting_entries.emplace_back();
            auto v = Serializer<base::CraftingDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.crafting_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.potion_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.potion_mix_entries.emplace_back();
            auto v = Serializer<PotionMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.potion_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.container_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.container_mix_entries.emplace_back();
            auto v = Serializer<ContainerMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.container_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.material_reducer_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.material_reducer_entries.emplace_back();
            auto v = Serializer<MaterialReducerDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.material_reducer_entries.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.clear_recipes = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v748::CraftingDataPacket>::serialize(BinaryWriter &stream, const v748::CraftingDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.crafting_entries.size());
    for (const auto &e0 : value.crafting_entries) {
        Serializer<v748::CraftingDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.potion_mix_entries.size());
    for (const auto &e0 : value.potion_mix_entries) {
        Serializer<PotionMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.container_mix_entries.size());
    for (const auto &e0 : value.container_mix_entries) {
        Serializer<ContainerMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.material_reducer_entries.size());
    for (const auto &e0 : value.material_reducer_entries) {
        Serializer<MaterialReducerDataEntry>::serialize(stream, e0);
    }
    stream.write<bool>(value.clear_recipes);
}

auto Serializer<v748::CraftingDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::CraftingDataPacket, std::error_code>
{
    v748::CraftingDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.crafting_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.crafting_entries.emplace_back();
            auto v = Serializer<v748::CraftingDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.crafting_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.potion_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.potion_mix_entries.emplace_back();
            auto v = Serializer<PotionMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.potion_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.container_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.container_mix_entries.emplace_back();
            auto v = Serializer<ContainerMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.container_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.material_reducer_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.material_reducer_entries.emplace_back();
            auto v = Serializer<MaterialReducerDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.material_reducer_entries.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.clear_recipes = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v975::CraftingDataPacket>::serialize(BinaryWriter &stream, const v975::CraftingDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.crafting_entries.size());
    for (const auto &e0 : value.crafting_entries) {
        Serializer<v975::CraftingDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.potion_mix_entries.size());
    for (const auto &e0 : value.potion_mix_entries) {
        Serializer<PotionMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.container_mix_entries.size());
    for (const auto &e0 : value.container_mix_entries) {
        Serializer<ContainerMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.material_reducer_entries.size());
    for (const auto &e0 : value.material_reducer_entries) {
        Serializer<MaterialReducerDataEntry>::serialize(stream, e0);
    }
    stream.write<bool>(value.clear_recipes);
}

auto Serializer<v975::CraftingDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::CraftingDataPacket, std::error_code>
{
    v975::CraftingDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.crafting_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.crafting_entries.emplace_back();
            auto v = Serializer<v975::CraftingDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.crafting_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.potion_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.potion_mix_entries.emplace_back();
            auto v = Serializer<PotionMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.potion_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.container_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.container_mix_entries.emplace_back();
            auto v = Serializer<ContainerMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.container_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.material_reducer_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.material_reducer_entries.emplace_back();
            auto v = Serializer<MaterialReducerDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.material_reducer_entries.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.clear_recipes = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::CraftingDataPacket>::serialize(BinaryWriter &stream, const v2168::CraftingDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shaped_recipes.size());
    for (const auto &e0 : value.shaped_recipes) {
        Serializer<v2168::ShapedRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.shapeless_recipes.size());
    for (const auto &e0 : value.shapeless_recipes) {
        Serializer<v2168::ShapelessRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.multi_recipes.size());
    for (const auto &e0 : value.multi_recipes) {
        Serializer<MultiRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.user_data_shapeless_recipes.size());
    for (const auto &e0 : value.user_data_shapeless_recipes) {
        Serializer<v2168::ShapelessRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.shapeless_chemistry_recipes.size());
    for (const auto &e0 : value.shapeless_chemistry_recipes) {
        Serializer<v2168::ShapelessRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.shaped_chemistry_recipes.size());
    for (const auto &e0 : value.shaped_chemistry_recipes) {
        Serializer<v2168::ShapedRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.smithing_transform_recipes.size());
    for (const auto &e0 : value.smithing_transform_recipes) {
        Serializer<v2168::SmithingTransformRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.smithing_trim_recipes.size());
    for (const auto &e0 : value.smithing_trim_recipes) {
        Serializer<v2168::SmithingTrimRecipePayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.potion_mix_entries.size());
    for (const auto &e0 : value.potion_mix_entries) {
        Serializer<PotionMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.container_mix_entries.size());
    for (const auto &e0 : value.container_mix_entries) {
        Serializer<ContainerMixDataEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.material_reducer_entries.size());
    for (const auto &e0 : value.material_reducer_entries) {
        Serializer<MaterialReducerDataEntry>::serialize(stream, e0);
    }
    stream.write<bool>(value.clear_recipes);
}

auto Serializer<v2168::CraftingDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::CraftingDataPacket, std::error_code>
{
    v2168::CraftingDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shaped_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shaped_recipes.emplace_back();
            auto v = Serializer<v2168::ShapedRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapeless_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapeless_recipes.emplace_back();
            auto v = Serializer<v2168::ShapelessRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.multi_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.multi_recipes.emplace_back();
            auto v = Serializer<MultiRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.multi_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.user_data_shapeless_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.user_data_shapeless_recipes.emplace_back();
            auto v = Serializer<v2168::ShapelessRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.user_data_shapeless_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapeless_chemistry_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapeless_chemistry_recipes.emplace_back();
            auto v = Serializer<v2168::ShapelessRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapeless_chemistry_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shaped_chemistry_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shaped_chemistry_recipes.emplace_back();
            auto v = Serializer<v2168::ShapedRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shaped_chemistry_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.smithing_transform_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.smithing_transform_recipes.emplace_back();
            auto v = Serializer<v2168::SmithingTransformRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_transform_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.smithing_trim_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.smithing_trim_recipes.emplace_back();
            auto v = Serializer<v2168::SmithingTrimRecipePayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.smithing_trim_recipes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.potion_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.potion_mix_entries.emplace_back();
            auto v = Serializer<PotionMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.potion_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.container_mix_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.container_mix_entries.emplace_back();
            auto v = Serializer<ContainerMixDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.container_mix_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.material_reducer_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.material_reducer_entries.emplace_back();
            auto v = Serializer<MaterialReducerDataEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.material_reducer_entries.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.clear_recipes = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v776::CreativeGroupInfoPayload>::serialize(BinaryWriter &stream, const v776::CreativeGroupInfoPayload &value)
{
    stream.write<std::int32_t>(value.creative_item_category);
    stream.write(value.name);
    Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.icon);
}

auto Serializer<v776::CreativeGroupInfoPayload>::deserialize(BinaryReader &stream) -> std::expected<v776::CreativeGroupInfoPayload, std::error_code>
{
    v776::CreativeGroupInfoPayload out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.creative_item_category = static_cast<CreativeItemCategory>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.icon = *v;
    }
    return out;
}

void Serializer<v2168::CreativeGroupInfoPayload>::serialize(BinaryWriter &stream, const v2168::CreativeGroupInfoPayload &value)
{
    stream.write<std::uint8_t>(value.creative_item_category);
    stream.write(value.name);
    Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.icon);
}

auto Serializer<v2168::CreativeGroupInfoPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::CreativeGroupInfoPayload, std::error_code>
{
    v2168::CreativeGroupInfoPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.creative_item_category = static_cast<CreativeItemCategory>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.icon = *v;
    }
    return out;
}

void Serializer<base::CreativeItemEntryPayload>::serialize(BinaryWriter &stream, const base::CreativeItemEntryPayload &value)
{
    Serializer<CreativeItemNetId>::serialize(stream, value.creative_item_net_id);
    Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.item_descriptor);
}

auto Serializer<base::CreativeItemEntryPayload>::deserialize(BinaryReader &stream) -> std::expected<base::CreativeItemEntryPayload, std::error_code>
{
    base::CreativeItemEntryPayload out;
    {
        auto v = Serializer<CreativeItemNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.creative_item_net_id = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item_descriptor = *v;
    }
    return out;
}

void Serializer<v776::CreativeItemEntryPayload>::serialize(BinaryWriter &stream, const v776::CreativeItemEntryPayload &value)
{
    Serializer<CreativeItemNetId>::serialize(stream, value.creative_item_net_id);
    Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.item_descriptor);
    stream.writeVarInt<std::uint32_t>(value.group_index);
}

auto Serializer<v776::CreativeItemEntryPayload>::deserialize(BinaryReader &stream) -> std::expected<v776::CreativeItemEntryPayload, std::error_code>
{
    v776::CreativeItemEntryPayload out;
    {
        auto v = Serializer<CreativeItemNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.creative_item_net_id = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item_descriptor = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.group_index = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<v2168::CreativeItemEntryPayload>::serialize(BinaryWriter &stream, const v2168::CreativeItemEntryPayload &value)
{
    Serializer<CreativeItemNetId>::serialize(stream, value.creative_item_net_id);
    Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::serialize(stream, value.item_descriptor);
    stream.writeVarInt<std::uint32_t>(value.group_index);
}

auto Serializer<v2168::CreativeItemEntryPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::CreativeItemEntryPayload, std::error_code>
{
    v2168::CreativeItemEntryPayload out;
    {
        auto v = Serializer<CreativeItemNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.creative_item_net_id = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item_descriptor = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.group_index = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<base::CreativeContentPacket>::serialize(BinaryWriter &stream, const base::CreativeContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.entries.size());
    for (const auto &e0 : value.entries) {
        Serializer<base::CreativeItemEntryPayload>::serialize(stream, e0);
    }
}

auto Serializer<base::CreativeContentPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CreativeContentPacket, std::error_code>
{
    base::CreativeContentPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entries.emplace_back();
            auto v = Serializer<base::CreativeItemEntryPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entries.back() = *v;
        }
    }
    return out;
}

void Serializer<v776::CreativeContentPacket>::serialize(BinaryWriter &stream, const v776::CreativeContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.groups.size());
    for (const auto &e0 : value.groups) {
        Serializer<v776::CreativeGroupInfoPayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entries.size());
    for (const auto &e0 : value.entries) {
        Serializer<v776::CreativeItemEntryPayload>::serialize(stream, e0);
    }
}

auto Serializer<v776::CreativeContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::CreativeContentPacket, std::error_code>
{
    v776::CreativeContentPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.groups.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.groups.emplace_back();
            auto v = Serializer<v776::CreativeGroupInfoPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.groups.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entries.emplace_back();
            auto v = Serializer<v776::CreativeItemEntryPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entries.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::CreativeContentPacket>::serialize(BinaryWriter &stream, const v2168::CreativeContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.groups.size());
    for (const auto &e0 : value.groups) {
        Serializer<v2168::CreativeGroupInfoPayload>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entries.size());
    for (const auto &e0 : value.entries) {
        Serializer<v2168::CreativeItemEntryPayload>::serialize(stream, e0);
    }
}

auto Serializer<v2168::CreativeContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::CreativeContentPacket, std::error_code>
{
    v2168::CreativeContentPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.groups.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.groups.emplace_back();
            auto v = Serializer<v2168::CreativeGroupInfoPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.groups.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entries.emplace_back();
            auto v = Serializer<v2168::CreativeItemEntryPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entries.back() = *v;
        }
    }
    return out;
}

void Serializer<LabTablePacket>::serialize(BinaryWriter &stream, const LabTablePacket &value)
{
    stream.write<std::uint8_t>(value.type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<std::uint8_t>(value.reaction);
}

auto Serializer<LabTablePacket>::deserialize(BinaryReader &stream) -> std::expected<LabTablePacket, std::error_code>
{
    LabTablePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<LabTablePacket::Type>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.reaction = static_cast<LabTableReactionType>(*v);
    }
    return out;
}

void Serializer<UnlockedRecipesPacket>::serialize(BinaryWriter &stream, const UnlockedRecipesPacket &value)
{
    stream.write<std::uint32_t>(value.packet_type);
    stream.writeVarInt<std::uint32_t>(value.unlocked_recipes.size());
    for (const auto &e0 : value.unlocked_recipes) {
        stream.write(e0);
    }
}

auto Serializer<UnlockedRecipesPacket>::deserialize(BinaryReader &stream) -> std::expected<UnlockedRecipesPacket, std::error_code>
{
    UnlockedRecipesPacket out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.packet_type = static_cast<UnlockedRecipesPacket::PacketType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.unlocked_recipes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.unlocked_recipes.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.unlocked_recipes.back() = *v;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
