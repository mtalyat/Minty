#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/Color.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Sprite.h"

namespace Minty
{
	/// <summary>
	/// Holds a Sprite that is used by this Entity.
	/// </summary>
	struct SpriteComponent
		: public Component
	{
		/// <summary>
		/// The Sprite that this Component uses.
		/// </summary>
		Ref<Sprite> sprite = nullptr;

		/// <summary>
		/// The MaterialTemplate used to render this Sprite. If null, the Sprite's default MaterialTemplate is used.
		/// </summary>
		Ref<MaterialTemplate> materialTemplate = nullptr;

		/// <summary>
		/// The color of this Sprite.
		/// </summary>
		Color color = Color::white();

		/// <summary>
		/// Indicates whether the X axis should be flipped.
		/// </summary>
		Bool flipX = false;

		/// <summary>
		/// Indicates whether the Y axis should be flipped.
		/// </summary>
		Bool flipY = false;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}