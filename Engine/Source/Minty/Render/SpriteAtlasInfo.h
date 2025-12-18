#ifndef MINTY_RENDER_SPRITEATLASINFO_H
#define MINTY_RENDER_SPRITEATLASINFO_H

/**
 * @file SpriteAtlasInfo.h
 * @brief Header file defining the SpriteAtlasInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/SpriteGroup.h"
#include "Minty/Render/Texture.h"

namespace Minty
{
    /**
	 * @brief The arguments to build a SpriteAtlas.
	 */
	struct SpriteAtlasInfo
	{
		/**
		 * @brief The ID of this Atlas.
		 */
		UUID id = {};

		/**
		 * @brief The Texture that this Atlas uses.
		 */
		Shared<Texture> texture = nullptr;

		/**
		 * @brief The Sprite groups within this Atlas.
		 */
		Vector<SpriteGroup> groups = {};
	};
}

#endif // MINTY_RENDER_SPRITEATLASINFO_H