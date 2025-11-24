#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/Color.h"
#include "Minty/Render/Font.h"
#include "Minty/Render/FontVariant.h"

namespace Minty
{
	/// <summary>
	/// Holds Text data for an Entity.
	/// </summary>
	struct TextComponent
		: public Component
	{
		/// <summary>
		/// The text to render.
		/// </summary>
		String text = "";

		/// <summary>
		/// The color of the text.
		/// </summary>
		Color color = Color::white();

		/// <summary>
		/// The font to render the text in.
		/// </summary>
		Ref<Font> font = nullptr;

		/// <summary>
		/// The specific variant of the font to render the text in.
		/// </summary>
		Ref<FontVariant> fontVariant = nullptr;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
	
	/// <summary>
	/// Marks an Entity as having a dirty TextComponent.
	/// </summary>
	struct DirtyTextComponent
		: public Component
	{
	};
}