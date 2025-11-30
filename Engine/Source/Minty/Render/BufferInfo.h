#ifndef MINTY_RENDER_BUFFERINFO_H
#define MINTY_RENDER_BUFFERINFO_H

/**
 * @file BufferInfo.h
 * @brief Header file defining the BufferInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Render/BufferUsage.h"

namespace Minty
{
    /**
     * @brief The arguments for a Buffer.
     */
    struct BufferInfo
    {
        /**
         * @brief The usage of the Buffer.
         */
        BufferUsage usage = BufferUsage::Undefined;

        /**
         * @brief The size of the Buffer in bytes.
         */
        Size size = 0;

        /**
         * @brief The data of the Buffer.
         */
        AnyConst data = nullptr;

        /**
         * @brief When true, optimize for frequent per-frame usage. When false, optimize for infrequent usage.
         */
        Bool frequent = false;
    };
}

#endif // MINTY_RENDER_BUFFERINFO_H