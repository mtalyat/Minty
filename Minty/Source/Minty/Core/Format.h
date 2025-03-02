#pragma once
#include "Minty/Data/String.h"
#include "Minty/Core/ToString.h"

namespace Minty
{
#define F(format, ...) format(format, __VA_ARGS__);

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
			String formatted = format.sub(0, index) + firstString + format.sub(index + 2, format.() - index - 2);
		}
		return formatImpl(format);
	}
}