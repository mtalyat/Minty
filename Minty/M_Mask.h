#pragma once

#include "M_Object.h"
#include "M_Point.h"
#include "M_Rect.h"

#define mask_t unsigned char

namespace minty
{
	class Sprite;

	/// <summary>
	/// Holds data for a psuedo bitmask, made of bytes.
	/// </summary>
	class MINTY_API Mask
		: public Object
	{
	private:
		// the width of the mask
		int m_width;
		// the height of the mask
		int m_height;
		// the mask data in bytes
		mask_t* mp_bytes;

	public:
		/// <summary>
		/// Creates an empty Mask.
		/// </summary>
		Mask();

		/// <summary>
		/// Creates a blank Mask using the given width and height.
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		Mask(int const width, int const height);

		/// <summary>
		/// Creates a new Mask using the given width, height and array of bytes.
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="bytes"></param>
		Mask(int const width, int const height, mask_t* const bytes);

		~Mask();

		// index operator
		mask_t operator [](int const index) const
		{
			return mp_bytes[index];
		}

		// equals operator
		bool operator ==(Mask const& other) const
		{
			return sameSize(other) && compare(other);
		}

		// not equals operator
		bool operator !=(Mask const& other) const
		{
			return m_width != other.m_width || m_height != other.m_height || !compare(other);
		}

		/// <summary>
		/// The Width of this Mask.
		/// </summary>
		/// <returns></returns>
		constexpr int width() const { return m_width; }

		/// <summary>
		/// The Height of this Mask.
		/// </summary>
		/// <returns></returns>
		constexpr int height() const { return m_height; }

		/// <summary>
		/// The total area of this Mask.
		/// </summary>
		/// <returns></returns>
		constexpr int size() const { return m_width * m_height; }

		/// <summary>
		/// Is this Mask empty?
		/// </summary>
		/// <returns></returns>
		constexpr bool isEmpty() const { return m_width == 0 || m_height == 0; }

		/// <summary>
		/// Returns the mask_t at the given index.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		mask_t at(int const index) const { return mp_bytes[index]; }

		/// <summary>
		/// Sets the mask_t at the given index.
		/// </summary>
		/// <param name="index"></param>
		/// <param name="value"></param>
		void emplace(int const index, mask_t const value);

		/// <summary>
		/// Checks if this Mask collides with the given Mask.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool collidesWith(Mask const& other) const;

		/// <summary>
		/// Checks if this Mask is the same size as the given Mask.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool sameSize(Mask const& other) const;

		/// <summary>
		/// Takes a slice of this Mask, then returns it as a new Mask.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <returns></returns>
		Mask* slice(int const x, int const y, int const width, int const height) const;

		/// <summary>
		/// Takes a slice of this Mask, then returns it as a new Mask.
		/// </summary>
		/// <param name="rect"></param>
		/// <returns></returns>
		Mask* slice(Rect const& rect) const;

		/// <summary>
		/// Generates a mask from the given sprite data.
		/// </summary>
		/// <param name="sprite"></param>
		/// <returns></returns>
		static Mask* fromSprite(Sprite const* const sprite, Rect const* const rect = nullptr);

		std::string const toString() const override;
	private:
		/// <summary>
		/// Compares this mask and the given mask.
		/// </summary>
		/// <param name="other"></param>
		/// <returns>True if the Masks have the same bytes.</returns>
		inline bool compare(Mask const& other) const;

		/// <summary>
		/// Checks if this Mask has any overlapping 1's with the given Mask.
		/// </summary>
		/// <param name="other"></param>
		/// <returns>True if this Mask has a 1 where the given Mask also has a 1, otherwise false.</returns>
		bool checkForCollision(Mask const& other) const;
	};
}