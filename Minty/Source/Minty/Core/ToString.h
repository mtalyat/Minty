#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	template<typename T>
	String to_string(T const value)
	{
		return "";
	}

	String to_string(Bool const value);
	String to_string(Char const value);
	String to_string(Byte const value);
	String to_string(Short const value);
	String to_string(UShort const value);
	String to_string(Int const value);
	String to_string(UInt const value);
	String to_string(Long const value);
	String to_string(ULong const value);
	String to_string(Float const value);
	String to_string(Double const value);
	String to_string(UUID const value);
}