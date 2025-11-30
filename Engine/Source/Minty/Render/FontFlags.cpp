#include "pch.h"
#include "FontFlags.h"
#include "Minty/Data/StringBuilder.h"

using namespace Minty;

String Minty::to_string(FontFlags const obj)
{
	if (obj == FontFlags::None)
	{
		return "None";
	}

	StringBuilder builder;
	if (static_cast<Bool>(obj & FontFlags::Bold))
	{
		builder.append("Bold");
	}
	if (static_cast<Bool>(obj & FontFlags::Italic))
	{
		builder.append("Italic");
	}
	return builder.to_string();
}

FontFlags Minty::parse_to_font_flags(String const& string)
{
	if (string == "None") return FontFlags::None;

	FontFlags result = FontFlags::None;
	if (string.contains("Bold")) { result |= FontFlags::Bold; }
	if (string.contains("Italic")) { result |= FontFlags::Italic; }
	return result;
}

Bool Minty::parse_try_font_flags(String const& string, FontFlags& value)
{
	value = parse_to_font_flags(string);
	return string == "None" || value != FontFlags::None;
}