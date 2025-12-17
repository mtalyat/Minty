#ifndef MINTY_CORE_TYPES_H
#define MINTY_CORE_TYPES_H

/**
 * @file Types.h
 * @brief Header file defining core type aliases.
 * @author Mitchell Talyat
 */

#include <cstdint>
#include <typeindex>
#include <chrono>
#include <functional>
#include <concepts>

namespace Minty
{
	using Int8 = signed char;
    using UInt8 = unsigned char;
    using Int16 = signed short;
    using UInt16 = unsigned short;
    using Int32 = signed int;
    using UInt32 = unsigned int;
    using Int64 = signed long long;
    using UInt64 = unsigned long long;
    using Float32 = float;
    using Float64 = double;

	using Bool = bool;
	using Char = char;
	using Byte = UInt8;
	using Short = Int16;
	using UShort = UInt16;
	using Int = Int32;
	using UInt = UInt32;
	using Long = Int64;
	using ULong = UInt64;
	using Float = Float32;
	using Double = Float64;
	using Any = void*;
	using AnyConst = void const*;
	using Null = std::nullptr_t;
	
	using Size = size_t;
	using Handle = uint32_t;
	using Layer = Int;
	using TimePoint = int64_t;

	using TypeID = std::type_index;
	using TypeInfo = std::type_info;
	using TypeIndex = Size;

	template<typename T>
	using Function = std::function<T>;

	using Job = Function<void()>;
	using ParallelJob = Function<void(Size)>;

	// Concept to require all comparison operators for T
	template<typename T>
	concept Comparable = requires(T a, T b) {
		{ a == b } -> std::convertible_to<bool>;
		{ a != b } -> std::convertible_to<bool>;
		{ a < b } -> std::convertible_to<bool>;
		{ a > b } -> std::convertible_to<bool>;
		{ a <= b } -> std::convertible_to<bool>;
		{ a >= b } -> std::convertible_to<bool>;
	};

	class Event;
	using EventCallback = Function<void(Event&)>;

	struct CollisionData;
	using CollisionCallback = Function<void(CollisionData const&)>;
}

#endif // MINTY_CORE_TYPES_H