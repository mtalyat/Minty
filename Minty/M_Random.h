#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// Sets the seed for the random number generator.
	/// </summary>
	/// <param name="seed">The seed to set.</param>
	MINTY_API inline void random_seed(unsigned int const seed);

	/// <summary>
	/// Sets the seed for the random number generator, based on the current time.
	/// </summary>
	MINTY_API inline void random_seed_time();

	/// <summary>
	/// Generates a random integer.
	/// </summary>
	/// <returns>The random value generated.</returns>
	MINTY_API inline int random_int();

	/// <summary>
	/// Generates a random float from 0.0f (inclusive) to 1.0f (inclusive).
	/// </summary>
	/// <returns>The random value generated.</returns>
	MINTY_API inline float random_float();

	/// <summary>
	/// Generates a random integer in the range of [min, max).
	/// </summary>
	/// <param name="min">The minimum value (inclusive).</param>
	/// <param name="max">The maximum value (exclusive).</param>
	/// <returns>The random value generated.</returns>
	MINTY_API inline int random_range(int const min, int const max);

	/// <summary>
	/// Generates a random integer in the range of [0, max).
	/// </summary>
	/// <param name="max">The maximum value (exclusive).</param>
	/// <returns>The random value generated.</returns>
	MINTY_API inline int random_range(int const max);

	/// <summary>
	/// Generates a random float in the range of [min, max].
	/// </summary>
	/// <param name="min">The minimum value (inclusive).</param>
	/// <param name="max">The maximum value (inclusive).</param>
	/// <returns>The random value generated.</returns>
	MINTY_API inline float random_range(float const min, float const max);

	/// <summary>
	/// Generates a random float in the range of [min, max].
	/// </summary>
	/// <param name="max">The maximum value (inclusive).</param>
	/// <returns>The random value generated.</returns>
	MINTY_API inline float random_range(float const max);

	/// <summary>
	/// Generates a random integer that is either -1 or 1.
	/// </summary>
	/// <returns>The random value generated.</returns>
	MINTY_API inline int random_direction();

	/// <summary>
	/// Returns true if the random integer generated is less than the given value, with the given range.
	/// </summary>
	/// <param name="value">The value to check against.</param>
	/// <param name="range">The maximum value (exclusive).</param>
	/// <returns>True on success, otherwise false.</returns>
	MINTY_API inline bool random_chance(int const value, int const range);

	/// <summary>
	/// Returns true if the random byte generated is less than the given value.
	/// </summary>
	/// <param name="value"></param>
	/// <returns>True on success, otherwise false.</returns>
	MINTY_API inline bool random_chance_b(int const value);
}