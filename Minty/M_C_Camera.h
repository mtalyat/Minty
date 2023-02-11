#pragma once

#include "M_Main.h"

namespace minty
{
	class Screen;

	/// <summary>
	/// A component that holds data relating a camera within the Scene.
	/// </summary>
	struct MINTY_API Camera
	{
		/// <summary>
		/// The offset of the Camera when rendering.
		/// </summary>
		float offsetX, offsetY;

		void setCenter(float const x, float const y, Screen* const screen);

		void setOffset(float const x, float const y);
	};
}