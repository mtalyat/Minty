#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// Sets the seed for the random number generator.
	/// </summary>
	/// <param name="seed"></param>
	MINTY_API inline void random_seed(unsigned int const seed);

	/// <summary>
	/// Sets the seed for the random number generator, based on the current time.
	/// </summary>
	MINTY_API inline void random_seed_time();

	/// <summary>
	/// Generates a random integer.
	/// </summary>
	/// <returns></returns>
	MINTY_API inline int random_int();

	/// <summary>
	/// Generates a random float from 0.0f (inclusive) to 1.0f (inclusive).
	/// </summary>
	/// <returns></returns>
	MINTY_API inline float random_float();

	/// <summary>
	/// Generates a random integer between min (inclusive) and max (exclusive).
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	MINTY_API inline int random_range(int const min, int const max);

	/// <summary>
	/// Generates a random integer between 0 (inclusive) and max (exclusive).
	/// </summary>
	/// <param name="max"></param>
	/// <returns></returns>
	MINTY_API inline int random_range(int const max);

	/// <summary>
	/// Generates a random float between min (inclusive) and max (inclusive).
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	MINTY_API inline float random_range(float const min, float const max);

	/// <summary>
	/// Generates a random float between 0 (inclusive) and max (inclusive).
	/// </summary>
	/// <param name="max"></param>
	/// <returns></returns>
	MINTY_API inline float random_range(float const max);

	/// <summary>
	/// Generates a random integer that is either -1 or 1.
	/// </summary>
	/// <returns></returns>
	MINTY_API inline int random_direction();

	/// <summary>
	/// Returns true if the random integer generated is less than the given value, with the given range.
	/// </summary>
	/// <param name="value"></param>
	/// <param name="range"></param>
	/// <returns></returns>
	MINTY_API inline bool random_chance(int const value, int const range);
}