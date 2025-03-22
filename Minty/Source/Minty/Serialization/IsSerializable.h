#pragma once
#include <type_traits>

namespace Minty
{
	class Serializable;
	template<typename T, typename = void>
	struct is_serializable : std::false_type {};
	template<typename T>
	struct is_serializable<T, std::enable_if_t<std::is_base_of_v<Serializable, T>>> : std::true_type {};

	class SerializableObject;
	template<typename T, typename = void>
	struct is_serializable_object : std::false_type {};
	template<typename T>
	struct is_serializable_object<T, std::enable_if_t<std::is_base_of_v<SerializableObject, T>>> : std::true_type {};
}