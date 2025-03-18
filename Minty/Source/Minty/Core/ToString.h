#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include "Minty/Data/String.h"

namespace Minty
{
	template<typename T>
	String to_string(T const value)
	{
		MINTY_ABORT("Cannot convert type to string.");
		return "";
	}

	String to_string(Bool const value);
	String to_string(Bool2 const& value);
	String to_string(Bool3 const& value);
	String to_string(Bool4 const& value);
	String to_string(Char const value);
	String to_string(Char const* const value);
	String to_string(Byte const value);
	String to_string(Short const value);
	String to_string(UShort const value);
	String to_string(Int const value);
	String to_string(Int2 const& value);
	String to_string(Int3 const& value);
	String to_string(Int4 const& value);
	String to_string(UInt const value);
	String to_string(UInt2 const& value);
	String to_string(UInt3 const& value);
	String to_string(UInt4 const& value);
	String to_string(Long const value);
	String to_string(ULong const value);
	String to_string(Float const value);
	String to_string(Float2 const& value);
	String to_string(Float3 const& value);
	String to_string(Float4 const& value);
	String to_string(Double const value);
	String to_string(String const& value);
}