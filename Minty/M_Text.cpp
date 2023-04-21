#include "pch.h"
#include "M_Text.h"

namespace minty
{
	void Text::setPivot(PointF const& pivot)
	{
		m_pivot = pivot;

		if (mp_sprite)
		{
			mp_sprite->setPivot(pivot);
		}
	}
	
	void Text::apply(SDL_Renderer* const renderer)
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
}
