#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/Color.h"
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
		/// The color of this Sprite.
		/// </summary>
		Color color = Color::white();

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}