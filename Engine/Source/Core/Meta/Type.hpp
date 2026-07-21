#pragma once

/**
 * @file Type.hpp
 * @brief Header file defining the Type enumeration.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	constexpr Size TYPE_MAX_SIZE = sizeof(Float) * 16; // max size of any type

	/**
	 * @brief Enumeration of various data types.
	 */
	enum class TypeEnum
	{
		Undefined,
		Bool,
		Bool2,
		Bool3,
		Bool4,
		Char,
		Byte,
		Int,
		Int2,
		Int3,
		Int4,
		UInt,
		UInt2,
		UInt3,
		UInt4,
		WInt,
		WUInt,
		Size,
		Float,
		Float2,
		Float3,
		Float4,
		WFloat,
		Matrix2,
		Matrix3,
		Matrix4,
		Quaternion,
		Color,
		Object,
		String,
		MultilineString,

		Count,
	};

	MINTY_ENABLE_ENUM_OPERATORS(TypeEnum)

	struct Type
	{
		TypeEnum value;

		constexpr Type() : value(TypeEnum::Undefined) {}
		constexpr Type(TypeEnum const value) : value(value) {}
		Type(TypeID const typeId);

		TypeID get_typeid() const;
		Size get_size() const;

		operator TypeEnum() const { return value; }
		Bool operator==(TypeEnum const other) const { return value == other; }
		Bool operator!=(TypeEnum const other) const { return value != other; }
	};

	template<>
    struct Parser<TypeEnum>
    {
        static Bool parse(StringView const str, TypeEnum &value);
        static String to_string(TypeEnum const &value);
    };

	template<>
	struct Parser<Type>
	{
		inline static Bool parse(StringView const str, Type &value) { return Parser<TypeEnum>::parse(str, value.value); }
		inline static String to_string(Type const &value) { return Parser<TypeEnum>::to_string(value.value); }
	};
}
