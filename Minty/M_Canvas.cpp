#include "pch.h"
#include "M_Canvas.h"
#include "M_Line.h"
#include "M_Math.h"
#include "M_Debug.h"
#include "M_Brush_Sprite.h"

namespace minty
{
	Canvas::Canvas(int const width, int const height, Renderer* const renderer)
		: width(width)
		, height(height)
		, mp_pixels(nullptr)
		, mp_sprite(new Sprite(SDL_CreateRGBSurface(0, width, height, 32, SDL_R_MASK, SDL_G_MASK, SDL_B_MASK, SDL_A_MASK), renderer))// SDL_CreateTexture(renderer, SDL_PixelFormatEnum::SDL_PIXELFORMAT_ABGR8888, SDL_TextureAccess::SDL_TEXTUREACCESS_STREAMING, width, height), width, height)
		, m_dirty(false)
	{
		if (!mp_sprite->texture())
		{
			Debug::logErrorSDL(31, "Failed to create Canvas texture.");
		}

		// allow texture to blend for transparency
		SDL_SetTextureBlendMode(mp_sprite->texture(), SDL_BLENDMODE_BLEND);
	}

	Canvas::~Canvas()
	{
		delete mp_sprite;
	}

	void Canvas::lock()
	{
		if (SDL_LockSurface(mp_sprite->surface()))
		{
			Debug::logErrorSDL(32, "Failed to lock Canvas.");
			mp_pixels = nullptr;
		}
		else
		{
			mp_pixels = static_cast<color_t*>(mp_sprite->surface()->pixels);
		}
	}

	void Canvas::unlock()
	{
		SDL_UnlockSurface(mp_sprite->surface());

		// if changes made, update texture
		if (m_dirty)
		{
			SDL_UpdateTexture(mp_sprite->texture(), nullptr, mp_pixels, width * 4);
		}

		mp_pixels = nullptr;
	}

	void Canvas::set(int const x, int const y, color_t const color)
	{
		mp_pixels[y * width + x] = color;
	}

	void Canvas::set_s(int const x, int const y, color_t const color)
	{
		if (contains(x, y))
		{
			set(x, y, color);
		}
	}

	constexpr color_t Canvas::get(int const x, int const y) const
	{
		return mp_pixels[y * width + x];
	}

	constexpr color_t Canvas::get_s(int const x, int const y) const
	{
		if (contains(x, y))
		{
			return get(x, y);
		}

		return 0;
	}

	constexpr bool Canvas::contains(int const x, int const y) const
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	void Canvas::draw(int const x, int const y, Brush const& brush)
	{
		set_s(x, y, brush.getColor(x, y));

		m_dirty = true;
	}

	void Canvas::drawLine(int const x1, int const y1, int const x2, int const y2, Brush const& brush)
	{
		int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
		int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
		int err = dx + dy, e2;

		int x = x1;
		int y = y1;

		for (;;) {
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				set(x, y, brush.getColor(x1, y1, x, y));
			}

			if (x == x2 && y == y2)
			{
				break;
			}

			e2 = 2 * err;

			if (e2 >= dy)
			{
				err += dy; x += sx;
			}

			if (e2 <= dx)
			{
				err += dx; y += sy;
			}
		}

		m_dirty = true;
	}

	void Canvas::drawRect(int const x, int const y, int const width, int const height, Brush const& brush)
	{
		int i, j, k;

		// use for loops, straight lines

		// horizontal lines
		k = y + height - 1;
		for (i = 0; i < width; i++)
		{
			j = x + i;

			set_s(j, y, brush.getColor(x, y, j, y));
			set_s(j, k, brush.getColor(x, y, j, k));
		}

		// vertical lines
		k = x + width - 1;
		for (i = 1; i < height - 1; i++)
		{
			j = y + i;

			set_s(x, j, brush.getColor(x, y, x, j));
			set_s(k, j, brush.getColor(x, y, k, j));
		}

		m_dirty = true;
	}

	void Canvas::drawCircle(int const xm, int const ym, int const radius, Brush const& brush)
	{
		int r = radius;

		int x = -radius, y = 0, err = 2 - 2 * radius; /* II. Quadrant */
		do {
			// quadrant 1, 2, 3, 4, in this order:
			set_s(xm - x, ym + y, brush.getColor(xm - radius, ym - radius, xm - x, ym + y));
			set_s(xm - y, ym - x, brush.getColor(xm - radius, ym - radius, xm - y, ym - x));
			set_s(xm + x, ym - y, brush.getColor(xm - radius, ym - radius, xm + x, ym - y));
			set_s(xm + y, ym + x, brush.getColor(xm - radius, ym - radius, xm + y, ym + x));

			r = err;
			if (r <= y) err += ++y * 2 + 1;           /* e_xy+e_y < 0 */
			if (r > x || err > y) err += ++x * 2 + 1; /* e_xy+e_x > 0 or no 2nd y-step */
		} while (x < 0);

		m_dirty = true;
	}

	void Canvas::drawSprite(int const x, int const y, Sprite const* const sprite)
	{
		// cannot draw if null
		if (!sprite)
		{
			return;
		}

		int i, j;

		int x1, y1;

		// fill in entire rectangle
		for (i = 0; i < height; i++)
		{
			y1 = y + i;

			// skip if out of bounds
			if (y1 < 0 || y1 >= this->height)
			{
				continue;
			}

			for (j = 0; j < width; j++)
			{
				x1 = x + j;

				// skip if out of bounds
				if (x1 < 0 || x1 >= this->width)
				{
					continue;
				}

				set(x1, y1, sprite->getColor(x1, y1));
			}
		}

		m_dirty = true;
	}

	void Canvas::fillRect(int const x, int const y, int const width, int const height, Brush const& brush)
	{
		int i, j;

		int x1, y1;

		// fill in entire rectangle
		for (i = 0; i < height; i++)
		{
			y1 = y + i;

			// skip if out of bounds
			if (y1 < 0 || y1 >= this->height)
			{
				continue;
			}

			for (j = 0; j < width; j++)
			{
				x1 = x + j;

				// skip if out of bounds
				if (x1 < 0 || x1 >= this->width)
				{
					continue;
				}

				set(x1, y1, brush.getColor(x, y, x1, y1));
			}
		}

		m_dirty = true;
	}
	
	void Canvas::fillCircle(int const xm, int const ym, int const radius, Brush const& brush)
	{
		int const diameter = radius * 2;
		int const rs = radius * radius + radius; // + radius to round it out more like the drawCircle circle

		int x1, y1, ys;

		for (int y = 0; y <= diameter; y++)
		{
			y1 = ym - radius + y;

			// skip if out of bounds
			if (y1 < 0 || y1 >= height)
			{
				continue;
			}

			ys = (y - radius) * (y - radius);

			for (int x = 0; x <= diameter; x++)
			{
				x1 = xm - radius + x;

				// skip if out of bounds
				if (x1 < 0 || x1 >= width)
				{
					continue;
				}

				// skip if not in circle
				if ((x - radius) * (x - radius) + ys > rs)
				{
					continue;
				}

				// in circle, set color
				set(x1, y1, brush.getColor(xm - radius, ym - radius, x1, y1));
			}
		}

		m_dirty = true;
	}

	void Canvas::fillSlices(int const xm, int const ym, int const radius, std::vector<Sprite*> const& sprites, float offset)
	{
		// get slice data
		int sliceCount = static_cast<int>(sprites.size());
		float sliceSize = MATH_PI * 2.0f / static_cast<float>(sliceCount);

		// create brushes
		std::vector<Brush*> brushes;
		brushes.reserve(sliceCount);
		for (auto* sprite : sprites)
		{
			if (sprite)
			{
				brushes.push_back(new SpriteBrush(sprite, true));
			}
			else
			{
				brushes.push_back(nullptr);
			}
		}

		// get circle data
		int const diameter = radius * 2;
		int const rs = radius * radius + radius; // + radius to round it out more like the drawCircle circle

		int x1, y1, ys;

		for (int y = 0; y <= diameter; y++)
		{
			y1 = ym - radius + y;

			// skip if out of bounds
			if (y1 < 0 || y1 >= height)
			{
				continue;
			}

			ys = (y - radius) * (y - radius);

			for (int x = 0; x <= diameter; x++)
			{
				x1 = xm - radius + x;

				// skip if out of bounds
				if (x1 < 0 || x1 >= width)
				{
					continue;
				}

				// skip if not in circle
				if ((x - radius) * (x - radius) + ys > rs)
				{
					continue;
				}

				// determine slice index by using angle to this pixel from center
				float angle = math_mod_positive(math_angle(static_cast<float>(x - radius), static_cast<float>(y - radius)), MATH_PI * 2.0f);

				// divide by slice size to get slice index
				int slice = math_floorToInt(math_mod(angle + offset, MATH_PI * 2.0f) / sliceSize);

				// get brush
				Brush* brush = brushes.at(slice);

				// in circle, set color, if there is a brush
				if (brush)
				{
					set(x1, y1, brush->getColor(xm - radius, ym - radius, x1, y1));
				}
			}
		}

		// delete brushes
		for (auto* brush : brushes)
		{
			if (brush)
			{
				delete brush;
			}
		}

		m_dirty = true;
	}
	
	void Canvas::clear(color_t const color)
	{
		for (int i = 0; i < width * height; i++)
		{
			mp_pixels[i] = color;
		}

		m_dirty = true;
	}
}
