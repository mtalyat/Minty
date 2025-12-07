#ifndef MINTY_RENDER_TEXTUREINFO_H
#define MINTY_RENDER_TEXTUREINFO_H

/**
 * @file TextureInfo.h
 * @brief Header file defining the TextureInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/AddressMode.h"
#include "Minty/Render/Filter.h"
#include "Minty/Render/Image.h"

namespace Minty
{
    /**
	 * @brief Arguments for creating a Texture.
	 */
	struct TextureInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = {};

		/**
		 * @brief The Image this Texture uses.
		 */
		Shared<Image> image;

		/**
		 * @brief The filter to use for this Texture.
		 */
		Filter filter = Filter::Undefined;

		/**
		 * @brief The coordinate address mode to use for this Texture.
		 */
		AddressMode addressMode = AddressMode::Repeat;

		/**
		 * @brief When true, the coordinates are normalized to the range [0, 1]. Otherwise, they are from [0, width] and [0, height].
		 */
		Bool normalizeCoordinates = true;
	};
}

#endif // MINTY_RENDER_TEXTUREINFO_H