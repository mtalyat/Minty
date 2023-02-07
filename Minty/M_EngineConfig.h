#pragma once

#include "M_Main.h"
#include "M_Object.h"
#include "M_Point.h"
#include "M_Stopwatch.h"

namespace minty
{
	/// <summary>
	/// Holds data that will change how the Engine functions.
	/// </summary>
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
		bool quitOnEscape;

		EngineConfig()
			: maxFPS(60)
			, resolution(480, 270)
			, windowSize(480, 270)
			, resizable(true)
			, maximized(true)
			, fullscreen(true)
			, quitOnEscape(false)
		{}

		elapsed_t getFPNS() const
		{
			return static_cast<elapsed_t>(1.0f / maxFPS * ONE_SECOND);
		}
	};
}