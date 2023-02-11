#pragma once

#include "M_Object.h"

// type associated with entire color
#define color_t unsigned int
// type associated with color channel
#define channel_t unsigned char

namespace minty
{
	constexpr color_t COLOR_R_MASK = 0x000000FFu;
	constexpr color_t COLOR_G_MASK = 0x0000FF00u;
	constexpr color_t COLOR_B_MASK = 0x00FF0000u;
	constexpr color_t COLOR_A_MASK = 0xFF000000u;

	/// <summary>
	/// Holds color data within a color_t, used to represent a pixel.
	/// </summary>
	struct MINTY_API Color
		: public Object
	{
		color_t value;

		/// <summary>
		/// Creates an empty Color.
		/// </summary>
		Color()
			: value(0) {}

		/// <summary>
		/// Creates a Color using the given value.
		/// </summary>
		/// <param name="color"></param>
		Color(color_t const color)
			: value(color) {}

		/// <summary>
		/// Creates a Color using the given r, g, and b values. a is defaulted to 255.
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		Color(channel_t const r, channel_t const g, channel_t const b)
			: value((r << 24) | (g << 16) | (b << 8) | 255) {}

		/// <summary>
		/// Creates a Color using the given r, g, b, and a values.
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		/// <param name="a"></param>
		Color(channel_t const r, channel_t const g, channel_t const b, channel_t const a)
			: value((r << 24) | (g << 16) | (b << 8) | a) {}

		Color(Color const& c)
			: value(c.value) {}

		Color(Color&& c) noexcept
			: value(c.value)
		{
			c.value = 0;
		}

		inline operator color_t() const { return value; }

		Color& operator=(const Color& c)
		{
			value = c.value;

			return *this;
		}

		/// <summary>
		/// Returns the red value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t r() const { return (value >> 24) & 0xff; }

		/// <summary>
		/// Returns the green value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t g() const { return (value >> 16) & 0xff; }

		/// <summary>
		/// Returns the blue value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t b() const { return (value >> 8) & 0xff; }

		/// <summary>
		/// Returns the alpha value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t a() const { return value & 0xff; }

		/// <summary>
		/// Returns a 1 if this color is visible in the slightest, or 0 if alpha is zero.
		/// </summary>
		/// <returns></returns>
		inline channel_t mask() const { return (value & 0xff) > 0; }

		/// <summary>
		/// Darkens this Color by the given percent.
		/// </summary>
		/// <param name="p"></param>
		/// <returns></returns>
		inline Color darken(float const p) const;

		/// <summary>
		/// Lightens this Color by the given percent.
		/// </summary>
		/// <param name="p"></param>
		/// <returns></returns>
		inline Color lighten(float const p) const;

		inline std::string const toString() const;

		/// <summary>
		/// Lerps two colors. t = 0.0 -> left. t = 1.0 -> right.
		/// </summary>
		/// <param name="left"></param>
		/// <param name="right"></param>
		/// <param name="t"></param>
		/// <returns></returns>
		static Color lerp_rgba(Color const left, Color const right, float const t);

		/// <summary>
		/// Lerps two colors, minus the alpha value. The alpha value is taken from the left argument. t = 0.0 -> left. t = 1.0 -> right.
		/// </summary>
		/// <param name="left"></param>
		/// <param name="right"></param>
		/// <param name="t"></param>
		/// <returns></returns>
		static Color lerp_rgb(Color const left, Color const right, float const t);

		/// <summary>
		/// Gets a Color with random rgba values.
		/// </summary>
		/// <returns></returns>
		inline static Color random();

		inline static Color white() { return Color(255, 255, 255, 255); }
		inline static Color black() { return Color(0, 0, 0, 255); }
		inline static Color red() { return Color(255, 0, 0, 255); }
		inline static Color green() { return Color(0, 255, 0, 255); }
		inline static Color blue() { return Color(0, 0, 255, 255); }
		inline static Color yellow() { return Color(255, 255, 0, 255); }
		inline static Color cyan() { return Color(0, 255, 255, 255); }
		inline static Color magenta() { return Color(255, 0, 255, 255); }

		inline static Color error() { return Color(255, 0, 255, 255); }

		inline static Color rgba(unsigned char const r, unsigned char const g, unsigned char const b, unsigned char const a) { return Color(r, g, b, a); }

		inline static Color abgr(unsigned char const a, unsigned char const b, unsigned char const g, unsigned char const r) { return Color(r, g, b, a); }
	};
}