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
		/// <summary>
		/// The maximum FPS allowed.
		/// </summary>
		unsigned int maxFPS;

		/// <summary>
		/// The resolution of the Screen, in pixels.
		/// </summary>
		Point resolution;
		/// <summary>
		/// The window size of the Screen.
		/// </summary>
		Point windowSize;

		/// <summary>
		/// Is the window resizable?
		/// </summary>
		bool resizable;
		/// <summary>
		/// Is the window maximized?
		/// </summary>
		bool maximized;
		/// <summary>
		/// Is the window fullscreen?
		/// </summary>
		bool fullscreen;
		/// <summary>
		/// Should the engine quit when escape is pressed, no matter the Scene?
		/// </summary>
		bool quitOnEscape;

		/// <summary>
		/// Creates a default EngineConfig.
		/// </summary>
		EngineConfig()
			: maxFPS(60)
			, resolution(480, 270)
			, windowSize(480, 270)
			, resizable(true)
			, maximized(true)
			, fullscreen(true)
			, quitOnEscape(false)
		{}

		/// <summary>
		/// Gets the frames per nanosecond.
		/// </summary>
		/// <returns></returns>
		elapsed_t getFPNS() const
		{
			return static_cast<elapsed_t>(1.0f / maxFPS * ONE_SECOND);
		}
	};
}