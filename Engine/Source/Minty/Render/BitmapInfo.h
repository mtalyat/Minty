#ifndef MINTY_RENDER_BITMAPINFO_H
#define MINTY_RENDER_BITMAPINFO_H

/**
 * @file BitmapInfo.h
 * @brief Defines the BitmapInfo struct for bitmap creation parameters.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    /**
     * @brief Represents information required to create a Bitmap.
     */
    struct BitmapInfo
    {
        /**
         * @brief The unique identifier for the Bitmap.
         */
        UUID id = {};

        /**
         * @brief The width of the Bitmap.
         */
        UInt width = 0;

        /**
         * @brief The height of the Bitmap.
         */
        UInt height = 0;

        /**
         * @brief The number of channels in the Bitmap.
         */
        UInt channels = 0;

        /**
         * @brief A pointer to the pixel data. The size should be width * height * channels bytes.
         */
        AnyConst data = nullptr;
    };
}

#endif // MINTY_RENDER_BITMAPINFO_H