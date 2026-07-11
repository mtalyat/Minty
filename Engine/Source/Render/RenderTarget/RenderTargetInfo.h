#pragma once

/**
 * @file RenderTargetInfo.h
 * @brief Header file defining the RenderTargetInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/Type/Handle.h"
#include "Core/Data/Vector.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    /**
     * @brief The arguments for a RenderTarget.
     */
    struct RenderTargetInfo
    {
        /**
		 * @brief Optional RenderPass to bind this target to at creation time.
		 * If INVALID_HANDLE, this target can be attached by a RenderPass later.
         */
        RenderPassHandle renderPass = INVALID_HANDLE;

        /**
         * @brief The surface this RenderTarget renders to. If INVALID_HANDLE, a new target will be created using the images.
         */
        SurfaceHandle surface = INVALID_HANDLE;

        /**
         * @brief The images this RenderTarget uses. Only used if surface is INVALID_HANDLE, otherwise the surface's images will be used.
         */
        Vector<TextureHandle> images = {};
    };
}
