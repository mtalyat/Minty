#pragma once

/**
 * @file SpriteComponent.h
 * @brief Header file defining the SpriteComponent structure.
 * @author Mitchell Talyat
 */

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
		 * @brief The group this Sprite belongs to for rendering purposes. 0 is the default group.
		 */
		Int group = 0;

		/**
		 * @brief Indicates whether the X axis should be flipped.
		 */
		Bool flipX = false;

		/**
		 * @brief Indicates whether the Y axis should be flipped.
		 */
		Bool flipY = false;
	};

	template<>
	struct Serializer<SpriteComponent>
	{
		static Bool serialize(Writer& writer, SpriteComponent const& value);
		static Bool deserialize(Reader& reader, SpriteComponent& value);
	};
}
