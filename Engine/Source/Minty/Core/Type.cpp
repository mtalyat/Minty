#include "pch.h"
#include "Type.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/String.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Map.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size TYPE_COUNT = 33;
static constexpr Char const* TYPE_STRINGS[TYPE_COUNT] =
{
	"Undefined",
	"Bool",
	"Bool2",
	"Bool3",
	"Bool4",
	"Char",
	"Byte",
	"Short",
	"UShort",
	"Int",
	"Int2",
	"Int3",
	"Int4",
	"UInt",
	"UInt2",
	"UInt3",
	"UInt4",
	"Long",
	"ULong",
	"Size",
	"Float",
	"Float2",
	"Float3",
	"Float4",
	"Double",
	"Matrix2",
	"Matrix3",
	"Matrix4",
	"Quaternion",
	"Color",
	"Object",
	"String",
	"MultilineString",
};
static constexpr TypeID TYPE_TYPEIDS[TYPE_COUNT] =
{
	typeid(std::nullptr_t),
	typeid(Bool),
	typeid(Bool2),
	typeid(Bool3),
	typeid(Bool4),
	typeid(Char),
	typeid(Byte),
	typeid(Short),
	typeid(UShort),
	typeid(Int),
	typeid(Int2),
	typeid(Int3),
	typeid(Int4),
	typeid(UInt),
	typeid(UInt2),
	typeid(UInt3),
	typeid(UInt4),
	typeid(Long),
	typeid(ULong),
	typeid(Size),
	typeid(Float),
	typeid(Float2),
	typeid(Float3),
	typeid(Float4),
	typeid(Double),
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
	sizeof(Short),
	sizeof(UShort),
	sizeof(Int),
	sizeof(Int2),
	sizeof(Int3),
	sizeof(Int4),
	sizeof(UInt),
	sizeof(UInt2),
	sizeof(UInt3),
	sizeof(UInt4),
	sizeof(Long),
	sizeof(ULong),
	sizeof(Size),
	sizeof(Float),
	sizeof(Float2),
	sizeof(Float3),
	sizeof(Float4),
	sizeof(Double),
	sizeof(Matrix2),
	sizeof(Matrix3),
	sizeof(Matrix4),
	sizeof(Quaternion),
	sizeof(Color),
	sizeof(UUID),
	sizeof(String),
	sizeof(String),
};

Type Minty::type_typeid(TypeID const typeId)
{
	for (Size i = 0; i < TYPE_COUNT; i++)
	{
		if (typeId == TYPE_TYPEIDS[i])
		{
			return reinterpret_cast<Type>(i);
		}
	}
	return Type::Undefined;
}

TypeID Minty::typeid_type(Type const type)
{
	Size const index = reinterpret_cast<Size>(type);

	if(index >= TYPE_COUNT)
	{
		return TYPE_TYPEIDS[0];
	}
	return TYPE_TYPEIDS[index];
}

Size Minty::sizeof_type(Type const type)
{
	Size const index = reinterpret_cast<Size>(type);

	if(index >= TYPE_COUNT)
	{
		return TYPE_SIZES[0];
	}
	return TYPE_SIZES[index];
}

Bool Minty::Parser<Type>::parse(StringView const str, Type &value)
{
    return Tool::try_parse_enum(str, TYPE_STRINGS, TYPE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<Type>::to_string(Type const &value)
{
    return Tool::to_string_enum(reinterpret_cast<Size>(value), TYPE_STRINGS, TYPE_COUNT);
}
