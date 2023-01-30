#pragma once

#include "M_Main.h"
#include "M_Object.h"
#include "M_Point.h"
#include "M_Stopwatch.h"

namespace minty
{
	struct MINTY_API EngineConfig
		: public Object
	{
	public:
		unsigned int maxFPS;

		Point resolution;
		Point windowSize;

		bool resizable;
		bool maximized;
		bool fullscreen;

		EngineConfig()
			: maxFPS(60)
			, resolution(480, 270)
			, windowSize(480, 270)
			, resizable(true)
			, maximized(true)
			, fullscreen(true)
		{}

		elapsed_t getFPNS() const
		{
			return static_cast<elapsed_t>(1.0f / maxFPS * ONE_SECOND);
		}
	};
}