#pragma once

#include "M_Object.h"
#include <SDL.h>

// type associated with entire color
#define color_t unsigned int
// type associated with color channel
#define channel_t unsigned char

namespace minty
{
	constexpr channel_t CHANNEL_MAX = static_cast<channel_t>(0xff);
	constexpr channel_t CHANNEL_MIN = static_cast<channel_t>(0x00);

	constexpr int COLOR_SHAMT_A = 24;
	constexpr int COLOR_SHAMT_R = 0;
	constexpr int COLOR_SHAMT_G = 8;
	constexpr int COLOR_SHAMT_B = 16;

	constexpr color_t SDL_R_MASK = CHANNEL_MAX << COLOR_SHAMT_R;
	constexpr color_t SDL_G_MASK = CHANNEL_MAX << COLOR_SHAMT_G;
	constexpr color_t SDL_B_MASK = CHANNEL_MAX << COLOR_SHAMT_B;
	constexpr color_t SDL_A_MASK = CHANNEL_MAX << COLOR_SHAMT_A;

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
			: value((r << COLOR_SHAMT_R) | (b << COLOR_SHAMT_G) | (g << COLOR_SHAMT_B) | (255 << COLOR_SHAMT_A)) {}

		/// <summary>
		/// Creates a Color using the given r, g, b, and a values.
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		/// <param name="a"></param>
		Color(channel_t const r, channel_t const g, channel_t const b, channel_t const a)
			: value((r << COLOR_SHAMT_R) | (b << COLOR_SHAMT_G) | (g << COLOR_SHAMT_B) | (a << COLOR_SHAMT_A)) {}

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
		inline channel_t r() const { return getR(value); }

		/// <summary>
		/// Returns the green value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t g() const { return getG(value); }

		/// <summary>
		/// Returns the blue value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t b() const { return getB(value); }

		/// <summary>
		/// Returns the alpha value of this Color.
		/// </summary>
		/// <returns></returns>
		inline channel_t a() const { return getA(value); }

		/// <summary>
		/// Returns a 1 if this color is visible in the slightest, or 0 if alpha is zero.
		/// </summary>
		/// <returns></returns>
		inline channel_t mask() const { return getA(value) > CHANNEL_MIN; }

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

		inline SDL_Color toSDL() const;

		inline std::string const toString() const;

		/// <summary>
		/// Lerps two colors. t = 0.0 -> left. t = 1.0 -> right.
		/// </summary>
		/// <param name="left"></param>
		/// <param name="right"></param>
		/// <param name="t"></param>
		/// <returns></returns>
		static Color lerp_rgba(color_t const left, color_t const right, float const t);

		/// <summary>
		/// Lerps two colors, minus the alpha value. The alpha value is taken from the left argument. t = 0.0 -> left. t = 1.0 -> right.
		/// </summary>
		/// <param name="left"></param>
		/// <param name="right"></param>
		/// <param name="t"></param>
		/// <returns></returns>
		static Color lerp_rgb(color_t const left, color_t const right, float const t);

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

		inline static channel_t getA(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_A) & CHANNEL_MAX); }
		inline static channel_t getR(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_R) & CHANNEL_MAX); }
		inline static channel_t getG(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_G) & CHANNEL_MAX); }
		inline static channel_t getB(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_B) & CHANNEL_MAX); }
	};
}