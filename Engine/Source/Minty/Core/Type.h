#ifndef MINTY_CORE_TYPE_H
#define MINTY_CORE_TYPE_H

/**
 * @file Type.h
 * @brief Header file defining the Type enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Enumeration of various data types.
	 */
	enum class Type
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
		UWInt,
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

	/**
	 * @brief Gets the Type from the given TypeID.
	 * @param typeId The TypeID.
	 * @return The corresponding Type.
	 */
	Type type_typeid(TypeID const typeId);

	/**
	 * @brief Gets the TypeID from the given Type.
	 * @param type The Type.
	 * @return The corresponding TypeID.
	 */
	TypeID typeid_type(Type const type);

	/**
	 * @brief Gets the size in bytes of the given Type.
	 * @param type The Type.
	 * @return The size in bytes.
	 */
	Size sizeof_type(Type const type);

	template<>
    struct Parser<Type>
    {
        static Bool parse(StringView const str, Type &value);
        static String to_string(Type const &value);
    };
}

#endif // MINTY_CORE_TYPE_H