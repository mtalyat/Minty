#ifndef MINTY_RENDER_FONTINFO_H
#define MINTY_RENDER_FONTINFO_H

/**
 * @file FontInfo.h
 * @brief Header file defining the FontInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
    class FontVariant;

    /**
     * @brief The arguments for a font.
     */
    struct FontInfo
    {
        /**
         * @brief The Asset ID.
         */
        UUID id = UUID();

        /**
         * @brief The name of this Font.
         */
        String name;

        /**
         * @brief The variants this Font will use.
         */
        Vector<Shared<FontVariant>> variants;
    };
}

#endif // MINTY_RENDER_FONTINFO_H