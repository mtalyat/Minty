#pragma once

#include "M_Object.h"
#include "M_Font.h"
#include "M_Color.h"
#include "M_Sprite.h"
#include "M_PointF.h"
#include "M_Debug.h"

namespace minty
{
	/// <summary>
	/// A renderable string object.
	/// </summary>
	class MINTY_API Text
		: public Object
	{
	private:
		// the text to be rendered
		std::string m_text;
		// the width and height
		int m_width, m_height;
		// the font to render the text with
		Font* mp_font;
		// the color to render the text as
		Color m_color;
		// the pivot to apply to the text Sprite
		PointF m_pivot;
		// the Sprite itself
		Sprite* mp_sprite;
		// has the text changed since the Sprite was last updated?
		bool m_dirty;

	public:
		/// <summary>
		/// Creates a new Text from the given string, size bounds, font, and color.
		/// </summary>
		/// <param name="text">The initial text to be rendered.</param>
		/// <param name="width">The width of the bounding box of the Text.</param>
		/// <param name="height">The height of the bounding box of the Text.</param>
		/// <param name="font">The font to render the Text with.</param>
		/// <param name="color">The color to render the Text as.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		/// <param name="pivot">The pivot to apply to the Text Sprite.</param>
		Text(std::string text, int const width, int const height, Font* const font, Color const color, SDL_Renderer* const renderer, PointF const& pivot = PointF())
			: m_text(text)
			, m_width(width)
			, m_height(height)
			, mp_font(font)
			, m_color(color)
			, m_pivot(pivot)
			, mp_sprite(nullptr)
			, m_dirty(false)
		{
			apply(renderer);
		}

		/// <summary>
		/// Get the text that is within this Text.
		/// </summary>
		/// <returns>The text.</returns>
		inline std::string const& text() const { return m_text; }

		/// <summary>
		/// Gets the Font for this Text.
		/// </summary>
		/// <returns>The Font.</returns>
		inline Font* const font() const { return mp_font; }

		/// <summary>
		/// Gets the Color for this Text.
		/// </summary>
		/// <returns>The Color.</returns>
		inline Color color() const { return m_color; }

		/// <summary>
		/// Gets the Sprite for this Text.
		/// </summary>
		/// <returns>The Sprite.</returns>
		inline Sprite* const sprite() const { return mp_sprite; }

		/// <summary>
		/// Gets the pivot for this Text.
		/// </summary>
		/// <returns>The pivot.</returns>
		inline PointF const& pivot() const { return m_pivot; }

		/// <summary>
		/// Has the Text been edited but not applied?
		/// </summary>
		/// <returns>True if the text has been edited, but not applied.</returns>
		constexpr bool isDirty() const { return m_dirty; }

		/// <summary>
		/// Sets the text of this Text.
		/// </summary>
		/// <param name="text">The new text to render.</param>
		void setText(std::string text) { m_text = text; m_dirty = true; }

		/// <summary>
		/// Sets the Font to render this Text with.
		/// </summary>
		/// <param name="font">The Font.</param>
		void setFont(Font* const font) { mp_font = font; m_dirty = true; }

		/// <summary>
		/// Sets the Color to render this Text as.
		/// </summary>
		/// <param name="color">The Color.</param>
		void setColor(Color const color) { m_color = color; m_dirty = true; }

		/// <summary>
		/// Sets the pivot.
		/// </summary>
		/// <param name="pivot">The pivot.</param>
		void setPivot(PointF const& pivot);

		// update the sprite
		void apply(SDL_Renderer* const renderer);
	};
}