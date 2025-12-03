#ifndef MINTY_RENDER_RENDERTARGETINFO_H
#define MINTY_RENDER_RENDERTARGETINFO_H

/**
 * @file RenderTargetInfo.h
 * @brief Header file defining the RenderTargetInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    class RenderPass;
    class Image;

    /**
     * @brief The arguments for a RenderTarget.
     */
    struct RenderTargetInfo
    {
        /**
         * @brief The ID.
         */
        UUID id = UUID();

        /**
         * @brief The RenderPass this RenderTarget belongs to.
         */
        Ref<RenderPass> renderPass = nullptr;

        /**
         * @brief The images this RenderTarget uses.
         */
        Vector<Ref<Image>> images;

        /**
         * @brief If true, the RenderTarget is bound to the screen surface.
         */
        Bool surfaceBound = false;
    };
}

#endif // MINTY_RENDER_RENDERTARGETINFO_H