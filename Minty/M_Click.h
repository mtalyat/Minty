#pragma once

#include "M_Main.h"
#include "M_Point.h"

namespace minty
{
	struct MINTY_API Click
	{
		unsigned char button;
		unsigned char clicks;

		int x, y;

		inline Point pos() const { return Point(x, y); }
	};
}