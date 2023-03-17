#pragma once

#include "M_Object.h"
#include "M_Font.h"
#include "M_Color.h"
#include "M_Sprite.h"
#include "M_PointF.h"
#include "M_Debug.h"

namespace minty
{
	class MINTY_API Text
		: public Object
	{
	private:
		std::string m_text;
		int m_width, m_height;
		Font* mp_font;
		Color m_color;
		PointF m_pivot;
		Sprite* mp_sprite;
		bool m_dirty;

	public:
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

		inline std::string const& getText() const { return m_text; }

		inline Font* const getFont() const { return mp_font; }

		inline Color getColor() const { return m_color; }

		inline Sprite* const getSprite() const { return mp_sprite; }

		inline PointF const& getPivot() const { return m_pivot; }

		/// <summary>
		/// Has the Text been edited but not applied?
		/// </summary>
		/// <returns></returns>
		constexpr bool isDirty() const { return m_dirty; }

		void setText(std::string text) { m_text = text; m_dirty = true; }

		void setFont(Font* const font) { mp_font = font; m_dirty = true; }

		void setColor(Color const color) { m_color = color; m_dirty = true; }

		void setPivot(PointF const& pivot)
		{
			m_pivot = pivot;

			if (mp_sprite)
			{
				mp_sprite->setPivot(pivot);
			}
		}

		// update the sprite
		void apply(SDL_Renderer* const renderer)
		{
			// delete old sprite if there is one
			if (mp_sprite)
			{
				if (mp_sprite->surface())
				{
					SDL_FreeSurface(mp_sprite->surface());
				}

				delete mp_sprite;
				mp_sprite = nullptr;
			}

			// generate new sprite, if there is text
			if (m_text.empty())
			{
				return;
			}
			
			if (!mp_font)
			{
				Debug::logError(31, "Could not generate text sprite. Font was NULL.");
				return;
			}
			SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(mp_font, m_text.c_str(), m_color.toSDL(), static_cast<Uint32>(m_width));
			if (!surface)
			{
				Debug::logErrorSDL(30, "Could not generate text sprite.");
				return;
			}
			mp_sprite = new Sprite(surface, renderer);
			mp_sprite->setPivot(m_pivot);
		}
	};
}