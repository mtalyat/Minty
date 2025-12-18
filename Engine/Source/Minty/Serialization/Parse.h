#ifndef MINTY_SERIALIZATION_PARSE_H
#define MINTY_SERIALIZATION_PARSE_H

/**
 * @file Parse.h
 * @brief Header file defining parsing functions.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Macro.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Serialization/IsParseable.h"

namespace Minty
{
	template<typename T>
	std::enable_if_t<is_parseable<T>::value, T> 
		parse_to(StringView const string)
	{
		T t{};
		t.parse(string);
		return t;
	}

	template<typename T>
	std::enable_if_t<is_parseable<T>::value, Bool> 
		parse_try(StringView const string, T& value)
	{
		T t{};
		if (t.parse(string))
		{
			value = t;
			return true;
		}
		return false;
	}

	template<typename T>
	std::enable_if_t<!is_parseable<T>::value, T> 
		parse_to(StringView const string)
	{
		MINTY_NOT_IMPLEMENTED();
	}

	template<typename T>
	std::enable_if_t<!is_parseable<T>::value, Bool> 
		parse_try(StringView const string, T& value)
	{
		MINTY_NOT_IMPLEMENTED();
	}

	Bool to_bool(StringView const string);
	Bool try_bool(StringView const string, Bool& value);
	template<>
	inline Bool parse_to<Bool>(StringView const string)
	{
		return to_bool(string);
	}
	template<>
	inline Bool parse_try<Bool>(StringView const string, Bool& value)
	{
		return try_bool(string, value);
	}

	Bool2 to_bool2(StringView const string);
	Bool try_bool2(StringView const string, Bool2& value);
	template<>
	inline Bool2 parse_to<Bool2>(StringView const string)
	{
		return to_bool2(string);
	}
	template<>
	inline Bool parse_try<Bool2>(StringView const string, Bool2& value)
	{
		return try_bool2(string, value);
	}

	Bool3 to_bool3(StringView const string);
	Bool try_bool3(StringView const string, Bool3& value);
	template<>
	inline Bool3 parse_to<Bool3>(StringView const string)
	{
		return to_bool3(string);
	}
	template<>
	inline Bool parse_try<Bool3>(StringView const string, Bool3& value)
	{
		return try_bool3(string, value);
	}

	Bool4 to_bool4(StringView const string);
	Bool try_bool4(StringView const string, Bool4& value);
	template<>
	inline Bool4 parse_to<Bool4>(StringView const string)
	{
		return to_bool4(string);
	}
	template<>
	inline Bool parse_try<Bool4>(StringView const string, Bool4& value)
	{
		return try_bool4(string, value);
	}

	Char to_char(StringView const string);
	Bool try_char(StringView const string, Char& value);
	template<>
	inline Char parse_to<Char>(StringView const string)
	{
		return to_char(string);
	}
	template<>
	inline Bool parse_try<Char>(StringView const string, Char& value)
	{
		return try_char(string, value);
	}

	Byte to_byte(StringView const string);
	Bool try_byte(StringView const string, Byte& value);
	template<>
	inline Byte parse_to<Byte>(StringView const string)
	{
		return to_byte(string);
	}
	template<>
	inline Bool parse_try<Byte>(StringView const string, Byte& value)
	{
		return try_byte(string, value);
	}

	Short to_short(StringView const string);
	Bool try_short(StringView const string, Short& value);
	template<>
	inline Short parse_to<Short>(StringView const string)
	{
		return to_short(string);
	}
	template<>
	inline Bool parse_try<Short>(StringView const string, Short& value)
	{
		return try_short(string, value);
	}

	UShort to_ushort(StringView const string);
	Bool try_ushort(StringView const string, UShort& value);
	template<>
	inline UShort parse_to<UShort>(StringView const string)
	{
		return to_ushort(string);
	}
	template<>
	inline Bool parse_try<UShort>(StringView const string, UShort& value)
	{
		return try_ushort(string, value);
	}

	Int to_int(StringView const string);
	Bool try_int(StringView const string, Int& value);
	template<>
	inline Int parse_to<Int>(StringView const string)
	{
		return to_int(string);
	}
	template<>
	inline Bool parse_try<Int>(StringView const string, Int& value)
	{
		return try_int(string, value);
	}

	Int2 to_int2(StringView const string);
	Bool try_int2(StringView const string, Int2& value);
	template<>
	inline Int2 parse_to<Int2>(StringView const string)
	{
		return to_int2(string);
	}
	template<>
	inline Bool parse_try<Int2>(StringView const string, Int2& value)
	{
		return try_int2(string, value);
	}

	Int3 to_int3(StringView const string);
	Bool try_int3(StringView const string, Int3& value);
	template<>
	inline Int3 parse_to<Int3>(StringView const string)
	{
		return to_int3(string);
	}
	template<>
	inline Bool parse_try<Int3>(StringView const string, Int3& value)
	{
		return try_int3(string, value);
	}

	Int4 to_int4(StringView const string);
	Bool try_int4(StringView const string, Int4& value);
	template<>
	inline Int4 parse_to<Int4>(StringView const string)
	{
		return to_int4(string);
	}
	template<>
	inline Bool parse_try<Int4>(StringView const string, Int4& value)
	{
		return try_int4(string, value);
	}

	UInt to_uint(StringView const string);
	Bool try_uint(StringView const string, UInt& value);
	template<>
	inline UInt parse_to<UInt>(StringView const string)
	{
		return to_uint(string);
	}
	template<>
	inline Bool parse_try<UInt>(StringView const string, UInt& value)
	{
		return try_uint(string, value);
	}

	UInt2 to_uint2(StringView const string);
	Bool try_uint2(StringView const string, UInt2& value);
	template<>
	inline UInt2 parse_to<UInt2>(StringView const string)
	{
		return to_uint2(string);
	}
	template<>
	inline Bool parse_try<UInt2>(StringView const string, UInt2& value)
	{
		return try_uint2(string, value);
	}

	UInt3 to_uint3(StringView const string);
	Bool try_uint3(StringView const string, UInt3& value);
	template<>
	inline UInt3 parse_to<UInt3>(StringView const string)
	{
		return to_uint3(string);
	}
	template<>
	inline Bool parse_try<UInt3>(StringView const string, UInt3& value)
	{
		return try_uint3(string, value);
	}

	UInt4 to_uint4(StringView const string);
	Bool try_uint4(StringView const string, UInt4& value);
	template<>
	inline UInt4 parse_to<UInt4>(StringView const string)
	{
		return to_uint4(string);
	}
	template<>
	inline Bool parse_try<UInt4>(StringView const string, UInt4& value)
	{
		return try_uint4(string, value);
	}

	Long to_long(StringView const string);
	Bool try_long(StringView const string, Long& value);
	template<>
	inline Long parse_to<Long>(StringView const string)
	{
		return to_long(string);
	}
	template<>
	inline Bool parse_try<Long>(StringView const string, Long& value)
	{
		return try_long(string, value);
	}

	ULong to_ulong(StringView const string);
	Bool try_ulong(StringView const string, ULong& value);
	template<>
	inline ULong parse_to<ULong>(StringView const string)
	{
		return to_ulong(string);
	}
	template<>
	inline Bool parse_try<ULong>(StringView const string, ULong& value)
	{
		return try_ulong(string, value);
	}

	Size to_size(StringView const string);
	Bool try_size(StringView const string, Size& value);

	Float to_float(StringView const string);
	Bool try_float(StringView const string, Float& value);
	template<>
	inline Float parse_to<Float>(StringView const string)
	{
		return to_float(string);
	}
	template<>
	inline Bool parse_try<Float>(StringView const string, Float& value)
	{
		return try_float(string, value);
	}

	Float2 to_float2(StringView const string);
	Bool try_float2(StringView const string, Float2& value);
	template<>
	inline Float2 parse_to<Float2>(StringView const string)
	{
		return to_float2(string);
	}
	template<>
	inline Bool parse_try<Float2>(StringView const string, Float2& value)
	{
		return try_float2(string, value);
	}

	Float3 to_float3(StringView const string);
	Bool try_float3(StringView const string, Float3& value);
	template<>
	inline Float3 parse_to<Float3>(StringView const string)
	{
		return to_float3(string);
	}
	template<>
	inline Bool parse_try<Float3>(StringView const string, Float3& value)
	{
		return try_float3(string, value);
	}

	Float4 to_float4(StringView const string);
	Bool try_float4(StringView const string, Float4& value);
	template<>
	inline Float4 parse_to<Float4>(StringView const string)
	{
		return to_float4(string);
	}
	template<>
	inline Bool parse_try<Float4>(StringView const string, Float4& value)
	{
		return try_float4(string, value);
	}

	Double to_double(StringView const string);
	Bool try_double(StringView const string, Double& value);
	template<>
	inline Double parse_to<Double>(StringView const string)
	{
		return to_double(string);
	}
	template<>
	inline Bool parse_try<Double>(StringView const string, Double& value)
	{
		return try_double(string, value);
	}

	template<>
	inline String parse_to<String>(StringView const string)
	{
		return string;
	}
	template<>
	inline Bool parse_try<String>(StringView const string, String& value)
	{
		value = string;
		return true;
	}
}

#endif // MINTY_SERIALIZATION_PARSE_H