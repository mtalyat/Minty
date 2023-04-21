#pragma once

#include "M_Object.h"
#include <SDL.h>

// type associated with entire color
#define color_t unsigned int
// type associated with color channel
#define channel_t unsigned char

namespace minty
{
	/// <summary>
	/// Max value in a color channel.
	/// </summary>
	constexpr channel_t CHANNEL_MAX = static_cast<channel_t>(0xff);
	/// <summary>
	/// Min value in a color channel.
	/// </summary>
	constexpr channel_t CHANNEL_MIN = static_cast<channel_t>(0x00);

	/// <summary>
	/// The bit shift amount to get the alpha value in a color.
	/// </summary>
	constexpr int COLOR_SHAMT_A = 24;
	/// <summary>
	/// The bit shift amount to get the red value in a color.
	/// </summary>
	constexpr int COLOR_SHAMT_R = 0;
	/// <summary>
	/// The bit shift amount to get the green value in a color.
	/// </summary>
	constexpr int COLOR_SHAMT_G = 8;
	/// <summary>
	/// The bit shift amount to get the blue value in a color.
	/// </summary>
	constexpr int COLOR_SHAMT_B = 16;

	/// <summary>
	/// The SDL color mask for red.
	/// </summary>
	constexpr color_t SDL_R_MASK = CHANNEL_MAX << COLOR_SHAMT_R;
	/// <summary>
	/// The SDL color mask for green.
	/// </summary>
	constexpr color_t SDL_G_MASK = CHANNEL_MAX << COLOR_SHAMT_G;
	/// <summary>
	/// The SDL color mask for blue.
	/// </summary>
	constexpr color_t SDL_B_MASK = CHANNEL_MAX << COLOR_SHAMT_B;
	/// <summary>
	/// The SDL color mask for alpha.
	/// </summary>
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
			: value((r << COLOR_SHAMT_R) | (g << COLOR_SHAMT_G) | (b << COLOR_SHAMT_B) | (255 << COLOR_SHAMT_A)) {}

		/// <summary>
		/// Creates a Color using the given r, g, b, and a values.
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		/// <param name="a"></param>
		Color(channel_t const r, channel_t const g, channel_t const b, channel_t const a)
			: value((r << COLOR_SHAMT_R) | (g << COLOR_SHAMT_G) | (b << COLOR_SHAMT_B) | (a << COLOR_SHAMT_A)) {}

		// copy constructor
		Color(Color const& c)
			: value(c.value) {}

		// move constructor
		Color(Color&& c) noexcept
			: value(c.value)
		{
			c.value = 0;
		}

		// implicit conversion operator to color_t
		inline operator color_t() const { return value; }

		// assignment operator
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

		/// <summary>
		/// Converts this Color to an SDL_Color.
		/// </summary>
		/// <returns>The SDL_Color equivalent.</returns>
		inline SDL_Color toSDL() const;

		/// <summary>
		/// Gets the string form of this Color.
		/// </summary>
		/// <returns>The Color as a readable string.</returns>
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

		/// <summary>
		/// Creates a Color that represents the color white.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color white() { return Color(255, 255, 255, 255); }
		/// <summary>
		/// Creates a Color that represents the color black.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color black() { return Color(0, 0, 0, 255); }
		/// <summary>
		/// Creates a Color that represents the color red.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color red() { return Color(255, 0, 0, 255); }
		/// <summary>
		/// Creates a Color that represents the color green.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color green() { return Color(0, 255, 0, 255); }
		/// <summary>
		/// Creates a Color that represents the color blue.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color blue() { return Color(0, 0, 255, 255); }
		/// <summary>
		/// Creates a Color that represents the color yellow.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color yellow() { return Color(255, 255, 0, 255); }
		/// <summary>
		/// Creates a Color that represents the color cyan.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color cyan() { return Color(0, 255, 255, 255); }
		/// <summary>
		/// Creates a Color that represents the color magenta.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color magenta() { return Color(255, 0, 255, 255); }

		/// <summary>
		/// Creates a Color that represents an error.
		/// </summary>
		/// <returns>The Color.</returns>
		inline static Color error() { return Color(255, 0, 255, 255); }

		/// <summary>
		/// Creates a new Color from the RGBA format.
		/// </summary>
		/// <param name="r">The red value.</param>
		/// <param name="g">The green value.</param>
		/// <param name="b">The blue value.</param>
		/// <param name="a">The alpha value.</param>
		/// <returns>The new Color.</returns>
		inline static Color rgba(unsigned char const r, unsigned char const g, unsigned char const b, unsigned char const a) { return Color(r, g, b, a); }

		/// <summary>
		/// Creates a new Color from the ABGR format.
		/// </summary>
		/// <param name="a">The alpha value.</param>
		/// <param name="b">The blue value.</param>
		/// <param name="g">The green value.</param>
		/// <param name="r">The red value.</param>
		/// <returns>The new Color.</returns>
		inline static Color abgr(unsigned char const a, unsigned char const b, unsigned char const g, unsigned char const r) { return Color(r, g, b, a); }

		/// <summary>
		/// Gets the alpha channel from the given color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns>The alpha channel value.</returns>
		inline static channel_t getA(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_A) & CHANNEL_MAX); }
		/// <summary>
		/// Gets the red channel from the given color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns>The red channel value.</returns>
		inline static channel_t getR(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_R) & CHANNEL_MAX); }
		/// <summary>
		/// Gets the green channel from the given color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns>The green channel value.</returns>
		inline static channel_t getG(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_G) & CHANNEL_MAX); }
		/// <summary>
		/// Gets the blue channel from the given color.
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns>The blue channel value.</returns>
		inline static channel_t getB(color_t const color) { return static_cast<channel_t>((color >> COLOR_SHAMT_B) & CHANNEL_MAX); }
	};
}