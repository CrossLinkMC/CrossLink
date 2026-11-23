#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {

enum class AttributeModifierOperation : int {
    OperationAddition = 0,
    OperationMultiplyBase = 1,
    OperationMultiplyTotal = 2,
    OperationCap = 3,
    TotalOperations = 4,
    OperationInvalid = 4,
};

enum class AttributeOperands : int {
    OperandMin = 0,
    OperandMax = 1,
    OperandCurrent = 2,
    TotalOperands = 3,
    OperandInvalid = 3,
};

struct AttributeModifier {
    std::string id{};
    std::string name{};
    float amount{};
    AttributeModifierOperation operation{};
    AttributeOperands operand{};
    bool serialize{};
};

struct AttributeData {
    float min_value{};
    float max_value{};
    float current_value{};
    float default_min_value{};
    float default_max_value{};
    float default_value{};
    std::string name{};
    std::vector<AttributeModifier> modifiers{};
};

struct UpdateAttributesPacket {
    static constexpr int Id = 29;
    ActorRuntimeID runtime_id{};
    std::vector<AttributeData> attribute_data{};
    PlayerInputTick tick{};
};

template <int V>
struct packet_of<V, 29> { using type = UpdateAttributesPacket; };

namespace detail {

template <>
inline constexpr std::array<AttributeModifierOperation, 6> values_v<AttributeModifierOperation>{{
    AttributeModifierOperation::OperationAddition,
    AttributeModifierOperation::OperationMultiplyBase,
    AttributeModifierOperation::OperationMultiplyTotal,
    AttributeModifierOperation::OperationCap,
    AttributeModifierOperation::TotalOperations,
    AttributeModifierOperation::OperationInvalid,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<AttributeModifierOperation>{{
    "operationaddition",
    "operationmultiplybase",
    "operationmultiplytotal",
    "operationcap",
    "totaloperations",
    "operationinvalid",
}};

template <>
inline constexpr std::string_view type_name_v<AttributeModifierOperation>{"AttributeModifierOperation"};

template <>
inline constexpr std::array<AttributeOperands, 5> values_v<AttributeOperands>{{
    AttributeOperands::OperandMin,
    AttributeOperands::OperandMax,
    AttributeOperands::OperandCurrent,
    AttributeOperands::TotalOperands,
    AttributeOperands::OperandInvalid,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<AttributeOperands>{{
    "operandmin",
    "operandmax",
    "operandcurrent",
    "totaloperands",
    "operandinvalid",
}};

template <>
inline constexpr std::string_view type_name_v<AttributeOperands>{"AttributeOperands"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<AttributeModifier> = true;

template <>
inline constexpr std::string_view struct_name_v<AttributeModifier>{"AttributeModifier"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<AttributeModifier>{{
    "id",
    "name",
    "amount",
    "operation",
    "operand",
    "serialize",
}};

template <>
struct field_accessor<AttributeModifier> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.amount;
        }
        else if constexpr (I == 3) {
            return value.operation;
        }
        else if constexpr (I == 4) {
            return value.operand;
        }
        else {
            return value.serialize;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<AttributeData>{"AttributeData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<AttributeData>{{
    "min_value",
    "max_value",
    "current_value",
    "default_min_value",
    "default_max_value",
    "default_value",
    "name",
    "modifiers",
}};

template <>
struct field_accessor<AttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min_value;
        }
        else if constexpr (I == 1) {
            return value.max_value;
        }
        else if constexpr (I == 2) {
            return value.current_value;
        }
        else if constexpr (I == 3) {
            return value.default_min_value;
        }
        else if constexpr (I == 4) {
            return value.default_max_value;
        }
        else if constexpr (I == 5) {
            return value.default_value;
        }
        else if constexpr (I == 6) {
            return value.name;
        }
        else {
            return value.modifiers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<UpdateAttributesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<UpdateAttributesPacket>{"UpdateAttributesPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<UpdateAttributesPacket>{{
    "runtime_id",
    "attribute_data",
    "tick",
}};

template <>
struct field_accessor<UpdateAttributesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.attribute_data;
        }
        else {
            return value.tick;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<AttributeModifier> {
    static void serialize(BinaryWriter &stream, const AttributeModifier &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AttributeModifier, std::error_code>;
};

template <>
struct Serializer<AttributeData> {
    static void serialize(BinaryWriter &stream, const AttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AttributeData, std::error_code>;
};

template <>
struct Serializer<UpdateAttributesPacket> {
    static void serialize(BinaryWriter &stream, const UpdateAttributesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<UpdateAttributesPacket, std::error_code>;
};

}  // namespace bedrock::protocol
