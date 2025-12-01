#ifndef MINTY_RENDER_SURFACEINFO_H
#define MINTY_RENDER_SURFACEINFO_H

/**
 * @file SurfaceInfo.h
 * @brief Header file defining the Surface and SurfaceInfo.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/Format.h"

namespace Minty
{
    class Window;

    /**
	 * @brief The arguments for creating a Surface.
	 */
	struct SurfaceInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The desired format for the surface.
		 */
		Format targetFormat = Format::Default;

		/**
		 * @brief The window to create the surface for.
		 */
		Ref<Window> window = nullptr;
	};
}

#endif // MINTY_RENDER_SURFACEINFO_H