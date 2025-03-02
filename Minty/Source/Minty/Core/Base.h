#pragma once

namespace Minty
{
	template<typename From, typename To>
	constexpr To Cast(From const from)
	{
		return static_cast<To>(from);
	}
}