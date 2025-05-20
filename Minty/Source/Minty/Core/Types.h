#pragma once
#include <cstdint>
#include <typeindex>
#include <chrono>
#include <functional>

namespace Minty
{
	using Bool = bool;
	using Char = char;
	using Byte = uint8_t;
	using Short = int16_t;
	using UShort = uint16_t;
	using Int = int32_t;
	using UInt = uint32_t;
	using Long = int64_t;
	using ULong = uint64_t;
	using Float = float;
	using Double = double;
	using Size = size_t;
	using ID = uint64_t;
	using Handle = uint32_t;
	using Layer = uint32_t;

	/// <summary>
	/// A point in time.
	/// </summary>
	using TimePoint = std::chrono::steady_clock::time_point;
	/// <summary>
	/// Time elapsed in nanoseconds.
	/// </summary>
	using TimeElapsed = long long;

	using TypeID = std::type_index;
	using TypeInfo = std::type_info;
	using TypeIndex = Size;

	template<typename T>
	using Function = std::function<T>;

	using Job = Function<void()>;
	using ParallelJob = Function<void(Size)>;
}