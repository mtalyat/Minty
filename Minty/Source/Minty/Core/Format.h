#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
#define F(formatString, ...) format(formatString, __VA_ARGS__)

	template<typename... Args>
	static String format(String const& format, Args&&... args)
	{
		return _format(format, std::forward<Args>(args)...);
	}

	static String _format(String const& format)
	{
		return format;
	}

	template<typename T, typename... Args>
	static String _format(String const& format, T&& first, Args&&... args)
	{
		Size index = format.find("{}");
		if (index != INVALID_INDEX)
		{
			String firstString = to_string(std::forward<T>(first));
			Size size = format.get_size() - (index + 2);
			String formatted = format.sub(0, index) + firstString;
			if (size > 0)
			{
				formatted += format.sub(index + 2, size);
			}
			return _format(formatted, std::forward<Args>(args)...);
		}
		return _format(format);
	}
}