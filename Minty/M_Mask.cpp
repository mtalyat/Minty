#include "pch.h"
#include "M_Mask.h"
#include "M_Sprite.h"
#include "M_Color.h"

namespace minty
{
	Mask::Mask()
		: m_width(0)
		, m_height(0)
		, mp_bytes(nullptr)
	{}

	Mask::Mask(int const width, int const height)
		: m_width(width)
		, m_height(height)
		, mp_bytes(new mask_t[width * height])
	{}

	Mask::Mask(int const width, int const height, mask_t* const bytes)
		: m_width(width)
		, m_height(height)
		, mp_bytes(bytes)
	{}

	Mask::~Mask()
	{
		if (mp_bytes)
		{
			delete[] mp_bytes;
			mp_bytes = nullptr;
		}
	}

	void Mask::emplace(int const index, mask_t const value)
	{
		mp_bytes[index] = value;
	}

	bool Mask::collidesWith(Mask const& other) const
	{
		return !isEmpty() && sameSize(other) && checkForCollision(other);
	}

	bool Mask::sameSize(Mask const& other) const
	{
		return m_width == other.m_width && m_height == other.m_height;
	}

	Mask* Mask::slice(int const x, int const y, int const width, int const height) const
	{
		if (width * height == 0)
		{
			return new Mask();
		}

		// make a new array
		mask_t* output = new mask_t[width * height];

		// copy rows
		for (int i = 0; i < height; i++)
		{
			std::memcpy(&output[i * width], &mp_bytes[(y + i) * m_width + x], width);
		}

		return new Mask(width, height, output);
	}

	Mask* Mask::slice(Rect const& rect) const
	{
		return slice(rect.x, rect.y, rect.width, rect.height);
	}

	Mask* Mask::fromSprite(Sprite const* const sprite, Rect const* const rect)
	{
		// no sprite
		if (!sprite)
		{
			return nullptr;
		}

		Rect bounds = Rect(0, 0, sprite->width, sprite->height);

		if (rect)
		{
			bounds = *rect;
		}

		int size = bounds.area();
		mask_t* bytes = new mask_t[size];

		// if no surface, we cannot read pixel data, so just assume every pixel is empty
		if (!sprite->surface())
		{
			std::memset(bytes, 0, size);

			return new Mask(bounds.width, bounds.height, bytes);
		}

		// has a surface, so use those pixels
		color_t* pixels = static_cast<color_t*>(sprite->surface()->pixels);
		int pitch = sprite->surface()->pitch;

		for (int y = 0; y < bounds.height; y++)
		{
			for (int x = 0; x < bounds.width; x++)
			{
				bytes[y * bounds.width + x] = static_cast<mask_t>(Color(pixels[(bounds.y + y) * sprite->width + (bounds.x + x)]).mask());
			}
		}

		return new Mask(bounds.width, bounds.height, bytes);
	}

	std::string const Mask::toString() const
	{
		std::string output;

		// debug print the masks
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				output += std::to_string(mp_bytes[y * m_width + x] != 0);
			}
			output += "\n";
		}

		return output;
	}

	inline bool Mask::compare(Mask const& other) const
	{
		return std::memcmp(mp_bytes, other.mp_bytes, size());
	}

	bool Mask::checkForCollision(Mask const& other) const
	{
		int length = size();
		for (int i = 0; i < length; i++)
		{
			if ((mp_bytes[i] & other.mp_bytes[i]) != 0)
			{
				// if the byte of this mask is on, and the other one is, there is a collision
				return true;
			}
		}

		// no collisions
		return false;
	}
}
