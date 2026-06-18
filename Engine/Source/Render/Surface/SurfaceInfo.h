#pragma once

/**
 * @file SurfaceInfo.h
 * @brief Header file defining the SurfaceInfo.
 * @author Mitchell Talyat
 */

#include "Resource/Image/ImageFormat.h"
#include "Window/Type/Handle.h"

namespace Minty
{
    /**
	 * @brief The arguments for creating a Surface.
	 */
	struct SurfaceInfo
	{
		/**
		 * @brief The size of the surface.
		 */
		WindowHandle window = INVALID_HANDLE;

		/**
		 * @brief The format of the surface.
		 */
		ImageFormat format = ImageFormatEnum::Default;
	};
}
