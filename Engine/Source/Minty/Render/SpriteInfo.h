#ifndef MINTY_RENDER_SPRITEINFO_H
#define MINTY_RENDER_SPRITEINFO_H

/**
 * @file SpriteInfo.h
 * @brief Header file defining the SpriteInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/SpriteSlice.h"
#include "Minty/Render/Texture.h"

namespace Minty
{
    /**
	 * @brief The arguments for a Sprite.
	 */
	struct SpriteInfo
	{
		/**
		 * @brief The Asset ID.
		 */
		UUID id = {};

		/**
		 * @brief The Texture that this Sprite uses.
		 */
		Shared<Texture> texture = nullptr;

		/**
		 * @brief The slice of the Texture this Sprite uses.
		 */
		SpriteSlice slice = {};
	};
}

#endif // MINTY_RENDER_SPRITEINFO_H