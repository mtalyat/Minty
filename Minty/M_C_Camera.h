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

		/// <summary>
		/// Sets the center of the Camera on the Screen.
		/// </summary>
		/// <param name="x">The X percentage of the Screen width.</param>
		/// <param name="y">The Y percentage of the Screen height.</param>
		/// <param name="screen"></param>
		void setCenter(float const x, float const y, Screen* const screen);

		/// <summary>
		/// Directly sets the offset to render the Camera by.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void setOffset(float const x, float const y);
	};
}