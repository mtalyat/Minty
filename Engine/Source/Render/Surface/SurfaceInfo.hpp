#pragma once

/**
 * @file SurfaceInfo.hpp
 * @brief Header file defining the SurfaceInfo.
 * @author Mitchell Talyat
 */

#include "Resource/Image/ImageFormat.hpp"

namespace Minty
{
	class Window;

    /**
	 * @brief The arguments for creating a Surface.
	 */
	struct SurfaceInfo
	{
		/**
		 * @brief The window associated with the surface.
		 */
		Window* window = nullptr;

		/**
		 * @brief The format of the surface.
		 */
		ImageFormat format = ImageFormatEnum::Default;
	};
}
