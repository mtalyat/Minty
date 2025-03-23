#pragma once
#include <type_traits>

namespace Minty
{
	class Parseable;
	template<typename T, typename = void>
	struct is_parseable : std::false_type {};
	template<typename T>
	struct is_parseable<T, std::enable_if_t<std::is_base_of_v<Parseable, T>>> : std::true_type {};
}