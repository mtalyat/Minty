#pragma once

namespace Minty
{
	/// <summary>
	/// Returns the minimum of the two given values.
	/// </summary>
	/// <typeparam name="T">The type of value.</typeparam>
	/// <param name="a">The first value.</param>
	/// <param name="b">The second value.</param>
	/// <returns>The lower of the two values.</returns>
	template<typename T>
	constexpr T min(T const& a, T const& b)
	{
		return a < b ? a : b;
	}

	/// <summary>
	/// Returns the minimum of the given values.
	/// </summary>
	/// <typeparam name="T">The type of value.</typeparam>
	/// <typeparam name="...Args">The type of value.</typeparam>
	/// <param name="a">The first value.</param>
	/// <param name="...args">The other values.</param>
	/// <returns>The lowest of the values.</returns>
	template<typename T, typename... Args>
	constexpr T min(T const& a, Args const&... args)
	{
		return min(a, min(args...));
	}

	/// <summary>
	/// Returns the maximum of the two given values.
	/// </summary>
	/// <typeparam name="T">The type of value.</typeparam>
	/// <param name="a">The first value.</param>
	/// <param name="b">The second value.</param>
	/// <returns>The higher of the two values.</returns>
	template<typename T>
	constexpr T max(T const& a, T const& b)
	{
		return a > b ? a : b;
	}

	/// <summary>
	/// Returns the maximum of the given values.
	/// </summary>
	/// <typeparam name="T">The type of value.</typeparam>
	/// <typeparam name="...Args">The type of value.</typeparam>
	/// <param name="a">The first value.</param>
	/// <param name="...args">The other values.</param>
	/// <returns>The highest of the values.</returns>
	template<typename T, typename... Args>
	constexpr T max(T const& a, Args const&... args)
	{
		return max(a, max(args...));
	}

	/// <summary>
	/// Clamps the given value between the given minimum and maximum values.
	/// </summary>
	/// <typeparam name="T">The type of value.</typeparam>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimum value.</param>
	/// <param name="max">The maximum value.</param>
	/// <returns>The value, clamped between min and max.</returns>
	template<typename T>
	constexpr T clamp(T const& value, T const& min, T const& max)
	{
		return value < min ? min : (value > max ? max : value);
	}
}