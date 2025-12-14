#ifndef MINTY_COMPONENT_SPRITECOMPONENT_H
#define MINTY_COMPONENT_SPRITECOMPONENT_H

/**
 * @file SpriteComponent.h
 * @brief Header file defining the SpriteComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Sprite.h"
#include "Minty/Render/MaterialTemplate.h"

namespace Minty
{
	/**
	 * @brief Holds a Sprite that is used by this Entity.
	 */
	struct SpriteComponent
		: public Component
	{
		/**
		 * @brief The source Asset for this SpriteComponent. Could be a Sprite or SpriteAtlas.
		 */
		Ref<Asset> source = nullptr;

		/**
		 * @brief The Sprite that this Component uses.
		 */
		Ref<Sprite> sprite = nullptr;

		/**
		 * @brief The MaterialTemplate used to render this Sprite. If null, the Sprite's default MaterialTemplate is used.
		 */
		Ref<MaterialTemplate> materialTemplate = nullptr;

		/**
		 * @brief The color of this Sprite.
		 */
		Color color = Color::white();

		/**
		 * @brief Indicates whether the X axis should be flipped.
		 */
		Bool flipX = false;

		/**
		 * @brief Indicates whether the Y axis should be flipped.
		 */
		Bool flipY = false;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_SPRITECOMPONENT_H