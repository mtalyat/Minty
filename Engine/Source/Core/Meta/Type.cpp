#include "pch.hpp"
#include "Type.hpp"
#include "Core/Type/Bool2.hpp"
#include "Core/Type/Bool3.hpp"
#include "Core/Type/Bool4.hpp"
#include "Core/Type/Int2.hpp"
#include "Core/Type/Int3.hpp"
#include "Core/Type/Int4.hpp"
#include "Core/Type/UInt2.hpp"
#include "Core/Type/UInt3.hpp"
#include "Core/Type/UInt4.hpp"
#include "Core/Type/Float2.hpp"
#include "Core/Type/Float3.hpp"
#include "Core/Type/Float4.hpp"
#include "Core/Type/WInt2.hpp"
#include "Core/Type/WInt3.hpp"
#include "Core/Type/WInt4.hpp"
#include "Core/Type/WUInt2.hpp"
#include "Core/Type/WUInt3.hpp"
#include "Core/Type/WUInt4.hpp"
#include "Core/Type/WFloat2.hpp"
#include "Core/Type/WFloat3.hpp"
#include "Core/Type/WFloat4.hpp"
#include "Core/Math/Matrix2x2.hpp"
#include "Core/Math/Matrix3x3.hpp"
#include "Core/Math/Matrix4x4.hpp"
#include "Core/Math/Quaternion.hpp"
#include "Core/Type/Color.hpp"
#include "Core/Data/UUID.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Size TYPE_COUNT = static_cast<Size>(TypeEnum::Count);
static constexpr Char const *TYPE_STRINGS[TYPE_COUNT] =
	{
		"Undefined",
		"Bool",
		"Bool2",
		"Bool3",
		"Bool4",
		"Char",
		"Byte",
		"Int",
		"Int2",
		"Int3",
		"Int4",
		"UInt",
		"UInt2",
		"UInt3",
		"UInt4",
		"WInt",
		"WUInt",
		"Size",
		"Float",
		"Float2",
		"Float3",
		"Float4",
		"WFloat",
		"Matrix2",
		"Matrix3",
		"Matrix4",
		"Quaternion",
		"Color",
		"Object",
		"String",
		"MultilineString",
};
static TypeID TYPE_TYPEIDS[TYPE_COUNT] =
	{
		typeid(Pointer),
		typeid(Bool),
		typeid(Bool2),
		typeid(Bool3),
		typeid(Bool4),
		typeid(Char),
		typeid(Byte),
		typeid(Int),
		typeid(Int2),
		typeid(Int3),
		typeid(Int4),
		typeid(UInt),
		typeid(UInt2),
		typeid(UInt3),
		typeid(UInt4),
		typeid(WInt),
		typeid(WUInt),
		typeid(Size),
		typeid(Float),
		typeid(Float2),
		typeid(Float3),
		typeid(Float4),
		typeid(WFloat),
		typeid(Matrix2),
		typeid(Matrix3),
		typeid(Matrix4),
		typeid(Quaternion),
		typeid(Color),
		typeid(UUID),
		typeid(String),
		typeid(String),
};
static constexpr Size TYPE_SIZES[TYPE_COUNT] =
	{
		sizeof(std::nullptr_t),
		sizeof(Bool),
		sizeof(Bool2),
		sizeof(Bool3),
		sizeof(Bool4),
		sizeof(Char),
		sizeof(Byte),
		sizeof(Int),
		sizeof(Int2),
		sizeof(Int3),
		sizeof(Int4),
		sizeof(UInt),
		sizeof(UInt2),
		sizeof(UInt3),
		sizeof(UInt4),
		sizeof(WInt),
		sizeof(WUInt),
		sizeof(Size),
		sizeof(Float),
		sizeof(Float2),
		sizeof(Float3),
		sizeof(Float4),
		sizeof(WFloat),
		sizeof(Matrix2),
		sizeof(Matrix3),
		sizeof(Matrix4),
		sizeof(Quaternion),
		sizeof(Color),
		sizeof(UUID),
		sizeof(String),
		sizeof(String),
};

Minty::Type::Type(TypeID const typeId)
{
	for (Size i = 0; i < TYPE_COUNT; i++)
	{
		if (typeId == TYPE_TYPEIDS[i])
		{
			value = static_cast<TypeEnum>(i);
			return;
		}
	}
	value = TypeEnum::Undefined;
}

TypeID Minty::Type::get_typeid() const
{
	Size const index = static_cast<Size>(value);

	if (index >= TYPE_COUNT)
	{
		return TYPE_TYPEIDS[0];
	}
	return TYPE_TYPEIDS[index];
}

Size Minty::Type::get_size() const
{
	Size const index = static_cast<Size>(value);

	if (index >= TYPE_COUNT)
	{
		return TYPE_SIZES[0];
	}
	return TYPE_SIZES[index];
}

Bool Minty::Parser<TypeEnum>::parse(StringView const str, TypeEnum &value)
{
	return Tool::try_parse_enum(str, TYPE_STRINGS, TYPE_COUNT, value);
}

String Minty::Parser<TypeEnum>::to_string(TypeEnum const &value)
{
	return Tool::to_string_enum(reinterpret_cast<Size const &>(value), TYPE_STRINGS, TYPE_COUNT);
}
