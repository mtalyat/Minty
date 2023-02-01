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

	MINTY_API Point direction_toPoint(int const dir);

	MINTY_API std::string direction_toString(int const dir);

	MINTY_API Direction direction_getCardinalDirection(float const x, float const y);
}