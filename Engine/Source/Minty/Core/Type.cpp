#include "pch.h"
#include "Type.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/String.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Map.h"

using namespace Minty;

Type Minty::type_typeid(TypeID const typeId)
{
	if (typeId == typeid(Bool))
	{
		return Type::Bool;
	}
	else if (typeId == typeid(Bool2))
	{
		return Type::Bool2;
	}
	else if (typeId == typeid(Bool3))
	{
		return Type::Bool3;
	}
	else if (typeId == typeid(Bool4))
	{
		return Type::Bool4;
	}
	else if (typeId == typeid(Char))
	{
		return Type::Char;
	}
	else if (typeId == typeid(Byte))
	{
		return Type::Byte;
	}
	else if (typeId == typeid(Short))
	{
		return Type::Short;
	}
	else if (typeId == typeid(UShort))
	{
		return Type::UShort;
	}
	else if (typeId == typeid(Int))
	{
		return Type::Int;
	}
	else if (typeId == typeid(Int2))
	{
		return Type::Int2;
	}
	else if (typeId == typeid(Int3))
	{
		return Type::Int3;
	}
	else if (typeId == typeid(Int4))
	{
		return Type::Int4;
	}
	else if (typeId == typeid(UInt))
	{
		return Type::UInt;
	}
	else if (typeId == typeid(UInt2))
	{
		return Type::UInt2;
	}
	else if (typeId == typeid(UInt3))
	{
		return Type::UInt3;
	}
	else if (typeId == typeid(UInt4))
	{
		return Type::UInt4;
	}
	else if (typeId == typeid(Long))
	{
		return Type::Long;
	}
	else if (typeId == typeid(ULong))
	{
		return Type::ULong;
	}
	else if (typeId == typeid(Size))
	{
		return Type::Size;
	}
	else if (typeId == typeid(Float))
	{
		return Type::Float;
	}
	else if (typeId == typeid(Float2))
	{
		return Type::Float2;
	}
	else if (typeId == typeid(Float3))
	{
		return Type::Float3;
	}
	else if (typeId == typeid(Float4))
	{
		return Type::Float4;
	}
	else if (typeId == typeid(Double))
	{
		return Type::Double;
	}
	else if (typeId == typeid(Matrix2))
	{
		return Type::Matrix2;
	}
	else if (typeId == typeid(Matrix3))
	{
		return Type::Matrix3;
	}
	else if (typeId == typeid(Matrix4))
	{
		return Type::Matrix4;
	}
	else if (typeId == typeid(Quaternion))
	{
		return Type::Quaternion;
	}
	else if (typeId == typeid(Color))
	{
		return Type::Color;
	}
	else if (typeId == typeid(UUID))
	{
		return Type::Object;
	}
	else if (typeId == typeid(String))
	{
		return Type::String;
	}
	else
	{
		return Type::Undefined;
	}
}

TypeID Minty::typeid_type(Type const type)
{
	switch (type)
	{
	case Type::Undefined:
		return typeid(nullptr);
	case Type::Bool:
		return typeid(Bool);
	case Type::Bool2:
		return typeid(Bool2);
	case Type::Bool3:
		return typeid(Bool3);
	case Type::Bool4:
		return typeid(Bool4);
	case Type::Char:
		return typeid(Char);
	case Type::Byte:
		return typeid(Byte);
	case Type::Short:
		return typeid(Short);
	case Type::UShort:
		return typeid(UShort);
	case Type::Int:
		return typeid(Int);
	case Type::Int2:
		return typeid(Int2);
	case Type::Int3:
		return typeid(Int3);
	case Type::Int4:
		return typeid(Int4);
	case Type::UInt:
		return typeid(UInt);
	case Type::UInt2:
		return typeid(UInt2);
	case Type::UInt3:
		return typeid(UInt3);
	case Type::UInt4:
		return typeid(UInt4);
	case Type::Long:
		return typeid(Long);
	case Type::ULong:
		return typeid(ULong);
	case Type::Size:
		return typeid(Size);
	case Type::Float:
		return typeid(Float);
	case Type::Float2:
		return typeid(Float2);
	case Type::Float3:
		return typeid(Float3);
	case Type::Float4:
		return typeid(Float4);
	case Type::Double:
		return typeid(Double);
	case Type::Matrix2:
		return typeid(Matrix2);
	case Type::Matrix3:
		return typeid(Matrix3);
	case Type::Matrix4:
		return typeid(Matrix4);
	case Type::Quaternion:
		return typeid(Quaternion);
	case Type::Color:
		return typeid(Color);
	case Type::Object:
		return typeid(UUID);
	case Type::String:
	case Type::MultilineString:
		return typeid(String);
	default:
		MINTY_ABORT("typeid_type not implemented for given type.");
	}
}

Size Minty::sizeof_type(Type const type)
{
	switch (type)
	{
	case Type::Undefined:
		return 0;
	case Type::Bool:
		return sizeof(Bool);
	case Type::Bool2:
		return sizeof(Bool2);
	case Type::Bool3:
		return sizeof(Bool3);
	case Type::Bool4:
		return sizeof(Bool4);
	case Type::Char:
		return sizeof(Char);
	case Type::Byte:
		return sizeof(Byte);
	case Type::Short:
		return sizeof(Short);
	case Type::UShort:
		return sizeof(UShort);
	case Type::Int:
		return sizeof(Int);
	case Type::Int2:
		return sizeof(Int2);
	case Type::Int3:
		return sizeof(Int3);
	case Type::Int4:
		return sizeof(Int4);
	case Type::UInt:
		return sizeof(UInt);
	case Type::UInt2:
		return sizeof(UInt2);
	case Type::UInt3:
		return sizeof(UInt3);
	case Type::UInt4:
		return sizeof(UInt4);
	case Type::Long:
		return sizeof(Long);
	case Type::ULong:
		return sizeof(ULong);
	case Type::Size:
		return sizeof(Size);
	case Type::Float:
		return sizeof(Float);
	case Type::Float2:
		return sizeof(Float2);
	case Type::Float3:
		return sizeof(Float3);
	case Type::Float4:
		return sizeof(Float4);
	case Type::Double:
		return sizeof(Double);
	case Type::Matrix2:
		return sizeof(Matrix2);
	case Type::Matrix3:
		return sizeof(Matrix3);
	case Type::Matrix4:
		return sizeof(Matrix4);
	case Type::Quaternion:
		return sizeof(Quaternion);
	case Type::Color:
		return sizeof(Color);
	case Type::Object:
		return sizeof(UUID);
	case Type::String:
	case Type::MultilineString:
		return sizeof(String);
	default:
		MINTY_ABORT("sizeof_type not implemented for given type.");
	}
}

String Minty::to_string(Type const obj)
{
	switch (obj)
	{
	case Type::Bool: return "Bool";
	case Type::Bool2: return "Bool2";
	case Type::Bool3: return "Bool3";
	case Type::Bool4: return "Bool4";
	case Type::Char: return "Char";
	case Type::Byte: return "Byte";
	case Type::Short: return "Short";
	case Type::UShort: return "UShort";
	case Type::Int: return "Int";
	case Type::Int2: return "Int2";
	case Type::Int3: return "Int3";
	case Type::Int4: return "Int4";
	case Type::UInt: return "UInt";
	case Type::UInt2: return "UInt2";
	case Type::UInt3: return "UInt3";
	case Type::UInt4: return "UInt4";
	case Type::Long: return "Long";
	case Type::ULong: return "ULong";
	case Type::Size: return "Size";
	case Type::Float: return "Float";
	case Type::Float2: return "Float2";
	case Type::Float3: return "Float3";
	case Type::Float4: return "Float4";
	case Type::Double: return "Double";
	case Type::Matrix2: return "Matrix2";
	case Type::Matrix3: return "Matrix3";
	case Type::Matrix4: return "Matrix4";
	case Type::Quaternion: return "Quaternion";
	case Type::Color: return "Color";
	case Type::Object: return "Object";
	case Type::String: return "String";
	case Type::MultilineString: return "MultilineString";
	case Type::Count: return "Count";

	default: return "";
	}
}

Type Minty::parse_to_type(String const& string)
{
	if (string == "Bool") return Type::Bool;
	if (string == "Bool2") return Type::Bool2;
	if (string == "Bool3") return Type::Bool3;
	if (string == "Bool4") return Type::Bool4;
	if (string == "Char") return Type::Char;
	if (string == "Byte") return Type::Byte;
	if (string == "Short") return Type::Short;
	if (string == "UShort") return Type::UShort;
	if (string == "Int") return Type::Int;
	if (string == "Int2") return Type::Int2;
	if (string == "Int3") return Type::Int3;
	if (string == "Int4") return Type::Int4;
	if (string == "UInt") return Type::UInt;
	if (string == "UInt2") return Type::UInt2;
	if (string == "UInt3") return Type::UInt3;
	if (string == "UInt4") return Type::UInt4;
	if (string == "Long") return Type::Long;
	if (string == "ULong") return Type::ULong;
	if (string == "Size") return Type::Size;
	if (string == "Float") return Type::Float;
	if (string == "Float2") return Type::Float2;
	if (string == "Float3") return Type::Float3;
	if (string == "Float4") return Type::Float4;
	if (string == "Double") return Type::Double;
	if (string == "Matrix2") return Type::Matrix2;
	if (string == "Matrix3") return Type::Matrix3;
	if (string == "Matrix4") return Type::Matrix4;
	if (string == "Quaternion") return Type::Quaternion;
	if (string == "Color") return Type::Color;
	if (string == "Object") return Type::Object;
	if (string == "String") return Type::String;
	if (string == "MultilineString") return Type::MultilineString;
	if (string == "Count") return Type::Count;

	return Type();
}

Bool Minty::parse_try_type(String const& string, Type& value)
{
	value = parse_to_type(string);
	return value != Type();
}
