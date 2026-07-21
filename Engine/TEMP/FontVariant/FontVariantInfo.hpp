#pragma once

/**
 * @file FontVariantInfo.hpp
 * @brief Header file defining the FontVariantInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Resource/Font/FontFlags.h"
#include "Resource/Font/FontChar.h"
#include "Core/Data/Vector.h"
#include "Core/Data/Map.h"
#include "Core/Data/Tuple.h"
#include "Resource/Type/Handle.h"

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
		 * @brief The size of this FontVariant.
		 */
		UInt size = 0;

		/**
		 * @brief The flags applied to this FontVariant.
		 */
		FontFlags flags = FontFlagsEnum::None;

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
		Vector<FontChar> characters = {};

		/**
		 * @brief The list of kernings for this FontVariant.
		 * Kernings are the adjustments made to the spacing between specific pairs of characters.
		 */
		Vector<Tuple<Char, Char, Float>> kernings = {};
	};
}
