#pragma once

/**
 * @file FontInfo.h
 * @brief Header file defining the FontInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Data/String.h"
#include "Core/Data/Vector.h"
#include "Resource/Type/Handle.h"

namespace Minty
{
    /**
     * @brief The arguments for a font.
     */
    struct FontInfo
    {
        /**
         * @brief The name of this Font.
         */
        String name;

        /**
         * @brief The variants this Font will use.
         */
        Vector<FontVariantResourceHandle> variants;
    };
}
