#ifndef MINTY_RENDER_SPRITESLICE_H
#define MINTY_RENDER_SPRITESLICE_H

/**
 * @file SpriteSlice.h
 * @brief Header file defining the SpriteSlice struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Render/CoordinateMode.h"

namespace Minty
{
	/**
	 * @brief Represents a slice of a Texture that can be used to create a Sprite.
	 */
	struct SpriteSlice
	{
		/**
		 * @brief How the coordinates are interpreted.
		 */
		CoordinateMode coordinateMode = CoordinateMode::Normalized;

		/**
		 * @brief The offset of this Sprite within the Texture.
		 */
		Float2 offset = { 0.0f, 0.0f };

		/**
		 * @brief The size of this Sprite within the Texture.
		 */
		Float2 size = { 1.0f, 1.0f };

		/**
		 * @brief The pivot of this Sprite within world space.
		 */
		Float2 pivot = { 0.5f, 0.5f };

		/**
		 * @brief The number of pixels that fit within 1 unit of world space.
		 */
		Float pixelsPerUnit = 16.0f;
	};
}

#endif // MINTY_RENDER_SPRITESLICE_H