#pragma once

#include "M_Main.h"
#include "M_Point.h"

namespace minty
{
	constexpr int DIRECTION_COUNT = 8;

	enum MINTY_API Direction
	{
		None,
		Right,
		UpRight,
		Up,
		UpLeft,
		Left,
		DownLeft,
		Down,
		DownRight
	};

	/// <summary>
	/// Converts the given direction to a Point.
	/// </summary>
	/// <param name="dir"></param>
	/// <returns></returns>
	MINTY_API Point direction_toPoint(int const dir);

	/// <summary>
	/// Converts the given direction to the string representation.
	/// </summary>
	/// <param name="dir"></param>
	/// <returns></returns>
	MINTY_API std::string direction_toString(int const dir);

	/// <summary>
	/// Gets the closest cardinal direction, given the x y position.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	MINTY_API Direction direction_getCardinalDirection(float const x, float const y);
}