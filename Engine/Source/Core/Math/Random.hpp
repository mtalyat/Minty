#pragma once

/**
 * @file Random.hpp
 * @brief Header file for random number generation utilities.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    namespace Math
    {
        /// <summary>
		/// Returns a random Float in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random Float in the given range.</returns>
		Float random_float(Float const min, Float const max);

		/// <summary>
		/// Returns a random Float in the range [0.0, 1.0).
		/// </summary>
		/// <returns>A random Float.</returns>
		Float random_float();

		/// <summary>
		/// Returns a random Int in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random Int in the given range.</returns>
		Int random_int(Int const min, Int const max);

		/// <summary>
		/// Returns a random Int in the range [INT_MIN, INT_MAX].
		/// </summary>
		/// <returns>A random Int.</returns>
		Int random_int();

		/// <summary>
		/// Returns a random UInt in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random UInt in the given range.</returns>
		UInt random_uint(UInt const min, UInt const max);

		/// <summary>
		/// Returns a random UInt in the range [UINT_MIN, UINT_MAX].
		/// </summary>
		/// <returns>A random UInt.</returns>
		UInt random_uint();

		/// <summary>
		/// Returns a random WFloat in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random WFloat in the given range.</returns>
		WFloat random_double(WFloat const min, WFloat const max);

		/// <summary>
		/// Returns a random WFloat in the range [0.0, 1.0).
		/// </summary>
		/// <returns>A random WFloat.</returns>
		WFloat random_double();

		/// <summary>
		/// Returns a random WInt in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random WInt in the given range.</returns>
		WInt random_long(WInt const min, WInt const max);

		/// <summary>
		/// Returns a random WInt in the range [LONG_MIN, LONG_MAX].
		/// </summary>
		/// <returns>A random WInt.</returns>
		WInt random_long();

		/// <summary>
		/// Returns a random WUInt in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random WUInt in the given range.</returns>
		WUInt random_ulong(WUInt const min, WUInt const max);

		/// <summary>
		/// Returns a random WUInt in the range [ULONG_MIN, ULONG_MAX].
		/// </summary>
		/// <returns>A random WUInt.</returns>
		WUInt random_ulong();

		/// <summary>
		/// Returns a random value of the specified type.
		/// </summary>
		/// <typeparam name="T">The type of value to return. Supported types: Float, Int, UInt, WFloat, WInt, WUInt.</typeparam>
		/// <returns>A random value of the specified type.</returns>
		template<typename T>
		inline T random() requires (
			std::is_same_v<T, Float> ||
			std::is_same_v<T, Int> ||
			std::is_same_v<T, UInt> ||
			std::is_same_v<T, WFloat> ||
			std::is_same_v<T, WInt> ||
			std::is_same_v<T, WUInt>)
		{
			return T();
		}

		/// <summary>
		/// Returns a random Float in the range [0.0, 1.0).
		/// </summary>
		/// <returns>A random Float.</returns>
		template<>
		inline Float random<Float>()
		{
			return random_float();
		}

		/// <summary>
		/// Returns a random Int in the range [INT_MIN, INT_MAX].
		/// </summary>
		/// <returns>A random Int.</returns>
		template<>
		inline Int random<Int>()
		{
			return random_int();
		}

		/// <summary>
		/// Returns a random UInt in the range [UINT_MIN, UINT_MAX].
		/// </summary>
		/// <returns>A random UInt.</returns>
		template<>
		inline UInt random<UInt>()
		{
			return random_uint();
		}

		/// <summary>
		/// Returns a random WFloat in the range [0.0, 1.0).
		/// </summary>
		/// <returns>A random WFloat.</returns>
		template<>
		inline WFloat random<WFloat>()
		{
			return random_double();
		}

		/// <summary>
		/// Returns a random WInt in the range [LONG_MIN, LONG_MAX].
		/// </summary>
		/// <returns>A random WInt.</returns>
		template<>
		inline WInt random<WInt>()
		{
			return random_long();
		}

		/// <summary>
		/// Returns a random WUInt in the range [ULONG_MIN, ULONG_MAX].
		/// </summary>
		/// <returns>A random WUInt.</returns>
		template<>
		inline WUInt random<WUInt>()
		{
			return random_ulong();
		}

		/// <summary>
		/// Returns a random value of the specified type in the range [min, max).
		/// </summary>
		/// <typeparam name="T">The type of value to return. Supported types: Float, Int, UInt, WFloat, WInt, WUInt.</typeparam>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random value of the specified type in the given range.</returns>
		template<typename T>
		inline T random(T const min, T const max) requires (
			std::is_same_v<T, Float> ||
			std::is_same_v<T, Int> ||
			std::is_same_v<T, UInt> ||
			std::is_same_v<T, WFloat> ||
			std::is_same_v<T, WInt> ||
			std::is_same_v<T, WUInt>)
		{
			return random(min, max);
		}

		/// <summary>
		/// Returns a random Float in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random Float in the given range.</returns>
		template<>
		inline Float random<Float>(Float const min, Float const max)
		{
			return random_float(min, max);
		}

		/// <summary>
		/// Returns a random Int in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random Int in the given range.</returns>
		template<>
		inline Int random<Int>(Int const min, Int const max)
		{
			return random_int(min, max);
		}

		/// <summary>
		/// Returns a random UInt in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random UInt in the given range.</returns>
		template<>
		inline UInt random<UInt>(UInt const min, UInt const max)
		{
			return random_uint(min, max);
		}

		/// <summary>
		/// Returns a random WFloat in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random WFloat in the given range.</returns>
		template<>
		inline WFloat random<WFloat>(WFloat const min, WFloat const max)
		{
			return random_double(min, max);
		}

		/// <summary>
		/// Returns a random WInt in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random WInt in the given range.</returns>
		template<>
		inline WInt random<WInt>(WInt const min, WInt const max)
		{
			return random_long(min, max);
		}

		/// <summary>
		/// Returns a random WUInt in the range [min, max].
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (inclusive).</param>
		/// <returns>A random WUInt in the given range.</returns>
		template<>
		inline WUInt random<WUInt>(WUInt const min, WUInt const max)
		{
			return random_ulong(min, max);
		}
    }
}