#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty::Parse
{
	/// <summary>
	/// Parses the given string into the given value.
	/// </summary>
	/// <typeparam name="T">The type to parse to.</typeparam>
	/// <param name="string">The String to parse from.</param>
	/// <param name="value">The value to parse into.</param>
	template<typename T>
	void parse_to(String const& string, T& value)
	{
		MINTY_ABORT("The given type is not parseable.");
	}

	/// <summary>
	/// Attempts to parse the given string into the given value.
	/// </summary>
	/// <typeparam name="T">The type to parse to.</typeparam>
	/// <param name="string">The String to parse from.</param>
	/// <param name="value">The value to parse into.</param>
	/// <returns>True on success.</returns>
	template<typename T>
	Bool parse_try(String const& string, T& value)
	{
		MINTY_ABORT("The given type is not parseable.");
	}

	Bool to_bool(String const& string);
	Bool try_bool(String const& string, Bool& value);
	template<>
	inline void parse_to(String const& string, Bool& value)
	{
		value = to_bool(string);
	}
	template<>
	inline Bool parse_try(String const& string, Bool& value)
	{
		return try_bool(string, value);
	}

	Bool2 to_bool2(String const& string);
	Bool try_bool2(String const& string, Bool2& value);
	template<>
	inline void parse_to(String const& string, Bool2& value)
	{
		value = to_bool2(string);
	}
	template<>
	inline Bool parse_try(String const& string, Bool2& value)
	{
		return try_bool2(string, value);
	}

	Bool3 to_bool3(String const& string);
	Bool try_bool3(String const& string, Bool3& value);
	template<>
	inline void parse_to(String const& string, Bool3& value)
	{
		value = to_bool3(string);
	}
	template<>
	inline Bool parse_try(String const& string, Bool3& value)
	{
		return try_bool3(string, value);
	}

	Bool4 to_bool4(String const& string);
	Bool try_bool4(String const& string, Bool4& value);
	template<>
	inline void parse_to(String const& string, Bool4& value)
	{
		value = to_bool4(string);
	}
	template<>
	inline Bool parse_try(String const& string, Bool4& value)
	{
		return try_bool4(string, value);
	}

	Char to_char(String const& string);
	Bool try_char(String const& string, Char& value);
	template<>
	inline void parse_to(String const& string, Char& value)
	{
		value = to_char(string);
	}
	template<>
	inline Bool parse_try(String const& string, Char& value)
	{
		return try_char(string, value);
	}

	Byte to_byte(String const& string);
	Bool try_byte(String const& string, Byte& value);
	template<>
	inline void parse_to(String const& string, Byte& value)
	{
		value = to_byte(string);
	}
	template<>
	inline Bool parse_try(String const& string, Byte& value)
	{
		return try_byte(string, value);
	}

	Short to_short(String const& string);
	Bool try_short(String const& string, Short& value);
	template<>
	inline void parse_to(String const& string, Short& value)
	{
		value = to_short(string);
	}
	template<>
	inline Bool parse_try(String const& string, Short& value)
	{
		return try_short(string, value);
	}

	UShort to_ushort(String const& string);
	Bool try_ushort(String const& string, UShort& value);
	template<>
	inline void parse_to(String const& string, UShort& value)
	{
		value = to_ushort(string);
	}
	template<>
	inline Bool parse_try(String const& string, UShort& value)
	{
		return try_ushort(string, value);
	}

	Int to_int(String const& string);
	Bool try_int(String const& string, Int& value);
	template<>
	inline void parse_to(String const& string, Int& value)
	{
		value = to_int(string);
	}
	template<>
	inline Bool parse_try(String const& string, Int& value)
	{
		return try_int(string, value);
	}

	Int2 to_int2(String const& string);
	Bool try_int2(String const& string, Int2& value);
	template<>
	inline void parse_to(String const& string, Int2& value)
	{
		value = to_int2(string);
	}
	template<>
	inline Bool parse_try(String const& string, Int2& value)
	{
		return try_int2(string, value);
	}

	Int3 to_int3(String const& string);
	Bool try_int3(String const& string, Int3& value);
	template<>
	inline void parse_to(String const& string, Int3& value)
	{
		value = to_int3(string);
	}
	template<>
	inline Bool parse_try(String const& string, Int3& value)
	{
		return try_int3(string, value);
	}

	Int4 to_int4(String const& string);
	Bool try_int4(String const& string, Int4& value);
	template<>
	inline void parse_to(String const& string, Int4& value)
	{
		value = to_int4(string);
	}
	template<>
	inline Bool parse_try(String const& string, Int4& value)
	{
		return try_int4(string, value);
	}

	UInt to_uint(String const& string);
	Bool try_uint(String const& string, UInt& value);
	template<>
	inline void parse_to(String const& string, UInt& value)
	{
		value = to_uint(string);
	}
	template<>
	inline Bool parse_try(String const& string, UInt& value)
	{
		return try_uint(string, value);
	}

	UInt2 to_uint2(String const& string);
	Bool try_uint2(String const& string, UInt2& value);
	template<>
	inline void parse_to(String const& string, UInt2& value)
	{
		value = to_uint2(string);
	}
	template<>
	inline Bool parse_try(String const& string, UInt2& value)
	{
		return try_uint2(string, value);
	}

	UInt3 to_uint3(String const& string);
	Bool try_uint3(String const& string, UInt3& value);
	template<>
	inline void parse_to(String const& string, UInt3& value)
	{
		value = to_uint3(string);
	}
	template<>
	inline Bool parse_try(String const& string, UInt3& value)
	{
		return try_uint3(string, value);
	}

	UInt4 to_uint4(String const& string);
	Bool try_uint4(String const& string, UInt4& value);
	template<>
	inline void parse_to(String const& string, UInt4& value)
	{
		value = to_uint4(string);
	}
	template<>
	inline Bool parse_try(String const& string, UInt4& value)
	{
		return try_uint4(string, value);
	}

	Long to_long(String const& string);
	Bool try_long(String const& string, Long& value);
	template<>
	inline void parse_to(String const& string, Long& value)
	{
		value = to_long(string);
	}
	template<>
	inline Bool parse_try(String const& string, Long& value)
	{
		return try_long(string, value);
	}

	ULong to_ulong(String const& string);
	Bool try_ulong(String const& string, ULong& value);
	template<>
	inline void parse_to(String const& string, ULong& value)
	{
		value = to_ulong(string);
	}
	template<>
	inline Bool parse_try(String const& string, ULong& value)
	{
		return try_ulong(string, value);
	}

	Size to_size(String const& string);
	Bool try_size(String const& string, Size& value);

	Float to_float(String const& string);
	Bool try_float(String const& string, Float& value);
	template<>
	inline void parse_to(String const& string, Float& value)
	{
		value = to_float(string);
	}
	template<>
	inline Bool parse_try(String const& string, Float& value)
	{
		return try_float(string, value);
	}

	Float2 to_float2(String const& string);
	Bool try_float2(String const& string, Float2& value);
	template<>
	inline void parse_to(String const& string, Float2& value)
	{
		value = to_float2(string);
	}
	template<>
	inline Bool parse_try(String const& string, Float2& value)
	{
		return try_float2(string, value);
	}

	Float3 to_float3(String const& string);
	Bool try_float3(String const& string, Float3& value);
	template<>
	inline void parse_to(String const& string, Float3& value)
	{
		value = to_float3(string);
	}
	template<>
	inline Bool parse_try(String const& string, Float3& value)
	{
		return try_float3(string, value);
	}

	Float4 to_float4(String const& string);
	Bool try_float4(String const& string, Float4& value);
	template<>
	inline void parse_to(String const& string, Float4& value)
	{
		value = to_float4(string);
	}
	template<>
	inline Bool parse_try(String const& string, Float4& value)
	{
		return try_float4(string, value);
	}

	Double to_double(String const& string);
	Bool try_double(String const& string, Double& value);
	template<>
	inline void parse_to(String const& string, Double& value)
	{
		value = to_double(string);
	}
	template<>
	inline Bool parse_try(String const& string, Double& value)
	{
		return try_double(string, value);
	}

	template<>
	inline void parse_to(String const& string, String& value)
	{
		value = string;
	}
	template<>
	inline Bool parse_try(String const& string, String& value)
	{
		value = string;
		return true;
	}

	Type to_type(String const& string);
	Bool try_type(String const& string, Type& value);
	template<>
	inline void parse_to(String const& string, Type& value)
	{
		value = to_type(string);
	}
	template<>
	inline Bool parse_try(String const& string, Type& value)
	{
		return try_type(string, value);
	}
}