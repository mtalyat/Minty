#include "pch.h"
#include "Parse.h"
#include <cstdint>
#include <string> // Include the string header for std::stoi

using namespace Minty;

#define MINTY_PARSE_TO_2(type) type result{}; std::istringstream ss(string.get_data()); Char discard;\
ss >> discard; MINTY_ASSERT(discard == '(', #type " must start with '('");\
ss >> result.x;\
ss >> discard; MINTY_ASSERT(discard == ',', #type " must have a ',' after the first value");\
ss >> result.y;\
ss >> discard; MINTY_ASSERT(discard == ')', #type " must end with ')'");\
return result

#define MINTY_PARSE_TO_3(type) type result{}; std::istringstream ss(string.get_data()); Char discard;\
ss >> discard; MINTY_ASSERT(discard == '(', #type " must start with '('");\
ss >> result.x;\
ss >> discard; MINTY_ASSERT(discard == ',', #type " must have a ',' after the first value");\
ss >> result.y;\
ss >> discard; MINTY_ASSERT(discard == ',', #type " must have a ',' after the second value");\
ss >> result.z;\
ss >> discard; MINTY_ASSERT(discard == ')', #type " must end with ')'");\
return result

#define MINTY_PARSE_TO_4(type) type result{}; std::istringstream ss(string.get_data()); Char discard;\
ss >> discard; MINTY_ASSERT(discard == '(', #type " must start with '('");\
ss >> result.x;\
ss >> discard; MINTY_ASSERT(discard == ',', #type " must have a ',' after the first value");\
ss >> result.y;\
ss >> discard; MINTY_ASSERT(discard == ',', #type " must have a ',' after the second value");\
ss >> result.z;\
ss >> discard; MINTY_ASSERT(discard == ',', #type " must have a ',' after the third value");\
ss >> result.w;\
ss >> discard; MINTY_ASSERT(discard == ')', #type " must end with ')'");\
return result

#define MINTY_TRY_PARSE_TO_2(type) type result{}; std::istringstream ss(string.get_data()); Char discard;\
ss >> discard; if (discard != '(') return false;\
ss >> result.x;\
ss >> discard; if (discard != ',') return false;\
ss >> result.y;\
ss >> discard; if (discard != ')') return false;\
value = result;\
return true

#define MINTY_TRY_PARSE_TO_3(type) type result{}; std::istringstream ss(string.get_data()); Char discard;\
ss >> discard; if (discard != '(') return false;\
ss >> result.x;\
ss >> discard; if (discard != ',') return false;\
ss >> result.y;\
ss >> discard; if (discard != ',') return false;\
ss >> result.z;\
ss >> discard; if (discard != ')') return false;\
value = result;\
return true

#define MINTY_TRY_PARSE_TO_4(type) type result{}; std::istringstream ss(string.get_data()); Char discard;\
ss >> discard; if (discard != '(') return false;\
ss >> result.x;\
ss >> discard; if (discard != ',') return false;\
ss >> result.y;\
ss >> discard; if (discard != ',') return false;\
ss >> result.z;\
ss >> discard; if (discard != ',') return false;\
ss >> result.w;\
ss >> discard; if (discard != ')') return false;\
value = result;\
return true

static Bool is_unsigned_integer(String const& string)
{
	if (!string.get_size()) return false; // nothing in string

	for (Char const c : string)
	{
		if (!isdigit(c)) return false; // not a digit
	}

	// all digits
	return true;
}

static Bool is_signed_integer(String const& string)
{
	if (!string.get_size()) return false; // nothing in string

	Size i = string.at(0) == '-' ? 1 : 0;

	// check if just the '-'
	if (i == 1 && string.get_size() == 1) return false;

	Char c;
	for (; i < string.get_size(); i++)
	{
		c = string.at(i);

		if (!isdigit(c)) return false; // not a digit
	}

	// all digits or - at beginning
	return true;
}

static Bool is_float(String const& string)
{
	if (!string.get_size()) return false; // nothing in string

	Char c;
	Bool decimal = false;
	Bool digit = false;
	for (Size i = 0; i < string.get_size(); i++)
	{
		c = string.at(i);

		switch (c)
		{
		case '-':
			if (i > 0) return false; // - not at beginning
			break;
		case '.':
			if (decimal) return false; // second .
			decimal = true;
			break;
		default:
			if (!isdigit(c)) return false; // not a digit
			digit = true;
			break;
		}
	}

	// can only be a number if there was a digit
	return digit;
}

Bool Minty::to_bool(String const& string)
{
	if (string.is_empty())
	{
		return false;
	}

	// false if 'f', 'F', or '0', otherwise true
	Char c = string.at(0);

	return c != 'f' && c != 'F' && c != '0';
}

Bool Minty::try_bool(String const& string, Bool& value)
{
	if (string.is_empty())
	{
		return false;
	}

	Char c = string.at(0);

	if (c == 't' || c == 'T' || c == '1')
	{
		value = true;
		return true;
	}
	else if (c == 'f' || c == 'F' || c == '0')
	{
		value = false;
		return true;
	}

	return false;
}

Bool2 Minty::to_bool2(String const& string)
{
	Bool2 result{};
	Char c;
	std::istringstream ss(string.get_data());
	ss >> c;
	MINTY_ASSERT(c == '(', "Bool2 must start with '('");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool2 must have a valid first value");
	result.x = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ',', "Bool2 must have a ',' after the first value");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool2 must have a valid second value");
	result.y = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ')', "Bool2 must end with ')'");
	return result;
}

Bool Minty::try_bool2(String const& string, Bool2& value)
{
	Bool2 result{};
	Char c;
	std::istringstream ss(string.get_data());
	ss >> c;
	if (c != '(') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.x = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ',') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.y = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ')') return false;
	value = result;
	return true;
}

Bool3 Minty::to_bool3(String const& string)
{
	Bool3 result{};
	Char c;
	std::istringstream ss(string.get_data());
	ss >> c;
	MINTY_ASSERT(c == '(', "Bool3 must start with '('");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool3 must have a valid first value");
	result.x = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ',', "Bool3 must have a ',' after the first value");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool3 must have a valid second value");
	result.y = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ',', "Bool3 must have a ',' after the second value");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool3 must have a valid third value");
	result.z = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ')', "Bool3 must end with ')'");
	return result;
}

Bool Minty::try_bool3(String const& string, Bool3& value)
{
	Bool3 result{};
	Char c;
	std::istringstream ss(string.get_data());
	ss >> c;
	if (c != '(') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.x = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ',') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.y = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ',') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.z = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ')') return false;
	value = result;
	return true;
}

Bool4 Minty::to_bool4(String const& string)
{
	Bool4 result{};
	Char c;
	std::istringstream ss(string.get_data());
	ss >> c;
	MINTY_ASSERT(c == '(', "Bool4 must start with '('");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool4 must have a valid first value");
	result.x = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ',', "Bool4 must have a ',' after the first value");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool4 must have a valid second value");
	result.y = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ',', "Bool4 must have a ',' after the second value");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool4 must have a valid third value");
	result.z = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ',', "Bool4 must have a ',' after the third value");
	ss >> c;
	MINTY_ASSERT(c == 't' || c == 'f' || c == 'T' || c == 'F' || c == '0' || c == '1', "Bool4 must have a valid fourth value");
	result.w = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	MINTY_ASSERT(c == ')', "Bool4 must end with ')'");
	return result;
}

Bool Minty::try_bool4(String const& string, Bool4& value)
{
	Bool4 result{};
	Char c;
	std::istringstream ss(string.get_data());
	ss >> c;
	if (c != '(') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.x = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ',') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.y = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ',') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.z = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ',') return false;
	ss >> c;
	if (c != 't' && c != 'f' && c != 'T' && c != 'F' && c != '0' && c != '1') return false;
	result.w = c != 'f' && c != 'F' && c != '0';
	ss >> c;
	if (c != ')') return false;
	value = result;
	return true;
}

Byte Minty::to_byte(String const& string)
{
	return static_cast<Byte>(std::stoi(string.get_data()));
}

Bool Minty::try_byte(String const& string, Byte& value)
{
	if (is_unsigned_integer(string))
	{
		value = static_cast<Byte>(std::stoi(string.get_data()));
		return true;
	}

	return false;
}

Char Minty::to_char(String const& string)
{
	return static_cast<Char>(std::stoi(string.get_data()));
}

Bool Minty::try_char(String const& string, Char& value)
{
	if (string.is_empty())
	{
		return false;
	}

	value = string.front();
	return true;
}

Short Minty::to_short(String const& string)
{
	return static_cast<Short>(std::stoi(string.get_data()));
}

Bool Minty::try_short(String const& string, Short& value)
{
	if (is_signed_integer(string))
	{
		value = static_cast<Short>(std::stoi(string.get_data()));
		return true;
	}

	return false;
}

UShort Minty::to_ushort(String const& string)
{
	return static_cast<UShort>(std::stoi(string.get_data()));
}

Bool Minty::try_ushort(String const& string, UShort& value)
{
	if (is_signed_integer(string))
	{
		value = static_cast<UShort>(std::stoi(string.get_data()));
		return true;
	}

	return false;
}

Int Minty::to_int(String const& string)
{
	return std::stoi(string.get_data());
}

Bool Minty::try_int(String const& string, Int& value)
{
	if (is_signed_integer(string))
	{
		value = std::stoi(string.get_data());
		return true;
	}

	return false;
}

Int2 Minty::to_int2(String const& string)
{
	MINTY_PARSE_TO_2(Int2);
}

Bool Minty::try_int2(String const& string, Int2& value)
{
	MINTY_TRY_PARSE_TO_2(Int2);
}

Int3 Minty::to_int3(String const& string)
{
	MINTY_PARSE_TO_3(Int3);
}

Bool Minty::try_int3(String const& string, Int3& value)
{
	MINTY_TRY_PARSE_TO_3(Int3);
}

Int4 Minty::to_int4(String const& string)
{
	MINTY_PARSE_TO_4(Int4);
}

Bool Minty::try_int4(String const& string, Int4& value)
{
	MINTY_TRY_PARSE_TO_4(Int4);
}

UInt Minty::to_uint(String const& string)
{
	return static_cast<UInt>(std::stoul(string.get_data()));
}

Bool Minty::try_uint(String const& string, UInt& value)
{
	if (is_unsigned_integer(string))
	{
		value = static_cast<UInt>(std::stoul(string.get_data()));
		return true;
	}

	return false;
}

UInt2 Minty::to_uint2(String const& string)
{
	MINTY_PARSE_TO_2(UInt2);
}

Bool Minty::try_uint2(String const& string, UInt2& value)
{
	MINTY_TRY_PARSE_TO_2(UInt2);
}

UInt3 Minty::to_uint3(String const& string)
{
	MINTY_PARSE_TO_3(UInt3);
}

Bool Minty::try_uint3(String const& string, UInt3& value)
{
	MINTY_TRY_PARSE_TO_3(UInt3);
}

UInt4 Minty::to_uint4(String const& string)
{
	MINTY_PARSE_TO_4(UInt4);
}

Bool Minty::try_uint4(String const& string, UInt4& value)
{
	MINTY_TRY_PARSE_TO_4(UInt4);
}

Long Minty::to_long(String const& string)
{
	return std::stol(string.get_data());
}

Bool Minty::try_long(String const& string, Long& value)
{
	if (is_signed_integer(string))
	{
		value = std::stol(string.get_data());
		return true;
	}

	return false;
}

ULong Minty::to_ulong(String const& string)
{
	return std::stoul(string.get_data());
}

Bool Minty::try_ulong(String const& string, ULong& value)
{
	if (is_signed_integer(string))
	{
		value = std::stoul(string.get_data());
		return true;
	}

	return false;
}

Float Minty::to_float(String const& string)
{
	return std::stof(string.get_data());
}

Bool Minty::try_float(String const& string, Float& value)
{
	if (is_float(string))
	{
		value = std::stof(string.get_data());
		return true;
	}

	return false;
}

Float2 Minty::to_float2(String const& string)
{
	MINTY_PARSE_TO_2(Float2);
}

Bool Minty::try_float2(String const& string, Float2& value)
{
	MINTY_TRY_PARSE_TO_2(Float2);
}

Float3 Minty::to_float3(String const& string)
{
	MINTY_PARSE_TO_3(Float3);
}

Bool Minty::try_float3(String const& string, Float3& value)
{
	MINTY_TRY_PARSE_TO_3(Float3);
}

Float4 Minty::to_float4(String const& string)
{
	MINTY_PARSE_TO_4(Float4);
}

Bool Minty::try_float4(String const& string, Float4& value)
{
	MINTY_TRY_PARSE_TO_4(Float4);
}

Double Minty::to_double(String const& string)
{
	return std::stod(string.get_data());
}

Bool Minty::try_double(String const& string, Double& value)
{
	if (is_float(string))
	{
		value = std::stod(string.get_data());
		return true;
	}

	return false;
}

Size Minty::to_size(String const& string)
{
	return to_ulong(string);
}

Bool Minty::try_size(String const& string, Size& value)
{
	return try_ulong(string, value);
}

#undef MINTY_PARSE_TO_2
#undef MINTY_PARSE_TO_3
#undef MINTY_PARSE_TO_4
#undef MINTY_TRY_PARSE_TO_2
#undef MINTY_TRY_PARSE_TO_3
#undef MINTY_TRY_PARSE_TO_4