#ifndef MINTY_RENDER_FONTVARIANTINFO_H
#define MINTY_RENDER_FONTVARIANTINFO_H

/**
 * @file FontVariantInfo.h
 * @brief Header file defining the FontVariantInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/FontFlags.h"

namespace Minty
{
    struct FontChar;
    class Texture;

    /**
	 * @brief The arguments for a FontVariant.
	 */
	struct FontVariantInfo
	{
		/**
		 * @brief The Asset ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The size of this FontVariant.
		 */
		UInt size;

		/**
		 * @brief The flags applied to this FontVariant.
		 */
		FontFlags flags = FontFlags::None;

		/**
		 * @brief The height of each line
		 */
		Float lineHeight = 0.0f;

		/**
		 * @brief The texture this FontVariant uses to render characters.
		 */
		Ref<Texture> texture = nullptr;

		/**
		 * @brief The data for each character that this FontVariant uses.
		 */
		Vector<FontChar> characters;

		/**
		 * @brief The list of kernings for this FontVariant.
		 * Kernings are the adjustments made to the spacing between specific pairs of characters.
		 */
		Vector<Tuple<Char, Char, Float>> kernings;
	};
}

#endif // MINTY_RENDER_FONTVARIANTINFO_H