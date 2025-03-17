#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Represents a type of data.
	/// </summary>
	enum class Type
	{
		Undefined,
		Bool,
		Bool2,
		Bool3,
		Bool4,
		Char,
		Byte,
		Short,
		UShort,
		Int,
		Int2,
		Int3,
		Int4,
		UInt,
		UInt2,
		UInt3,
		UInt4,
		Long,
		ULong,
		Size,
		Float,
		Float2,
		Float3,
		Float4,
		Double,
		String,
		MultilineString,
		Matrix2,
		Matrix3,
		Matrix4,
		Quaternion,
		Object,
		UUID,
	};

	/// <summary>
	/// Gets the Type from the given TypeID.
	/// </summary>
	/// <param name="typeId">The TypeID.</param>
	/// <returns>The Type.</returns>
	Type type_typeid(TypeID const typeId);

	/// <summary>
	/// Gets the TypeID from the given Type.
	/// </summary>
	/// <param name="type">The Type.</param>
	/// <returns>The TypeID.</returns>
	TypeID typeid_type(Type const type);

	/// <summary>
	/// Gets the size of the given Type in bytes.
	/// </summary>
	/// <param name="type">The Type.</param>
	/// <returns>The size of the type that the Type represents, in bytes.</returns>
	Size sizeof_type(Type const type);
}