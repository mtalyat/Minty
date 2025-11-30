#ifndef MINTY_RENDER_RENDERMANAGERINFO_H
#define MINTY_RENDER_RENDERMANAGERINFO_H

/**
 * @file RenderManagerInfo.h
 * @brief Header file for the RenderManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Format.h"

namespace Minty
{
    class Window;

    /**
     * @brief Configuration information for creating a RenderManager.
     */
	struct RenderManagerInfo
	{
        /**
         * @brief The Window to render to.
         */
		Ref<Window> window = nullptr;

        /**
         * @brief The format to use for the target Surface.
         */
		Format targetSurfaceFormat = Format::Default;
	};

}

#endif // MINTY_RENDER_RENDERMANAGERINFO_H