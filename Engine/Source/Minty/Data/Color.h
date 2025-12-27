#ifndef MINTY_DATA_COLOR_H
#define MINTY_DATA_COLOR_H

/**
 * @file Color.h
 * @brief Defines the Color struct for representing RGBA colors.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Represents a color with red, green, blue, and alpha components.
	 */
	struct Color
	{
#pragma region Types

	public:
		/**
		 * @brief The underlying type used to store the color value.
		 */
		using Color_t = Int32;

		/**
		 * @brief The type used for individual color channels.
		 */
		using Channel_t = UInt8;

		/**
		 * @brief The number of color channels.
		 */
		constexpr static Channel_t MAX_CHANNEL = 255;

		/**
		 * @brief The minimum value for a color channel.
		 */
		constexpr static Channel_t MIN_CHANNEL = 0;

#pragma endregion

#pragma region Variables

	public:
		union
		{
			struct
			{
				/**
				 * @brief The alpha component.
				 */
				Channel_t a;
				
				/**
				 * @brief The blue component.
				 */
				Channel_t b;

				/**
				 * @brief The green component.
				 */
				Channel_t g;

				/**
				 * @brief The red component.
				 */
				Channel_t r;
			};

			/**
			 * @brief The combined color value.
			 */
			Color_t value;
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Color with the given R, G, B, and A channel values.
		 * @param r The red value.
		 * @param g The green value.
		 * @param b The blue value.
		 * @param a The alpha value.
		 */
		explicit Color(Channel_t const r, Channel_t const g, Channel_t const b, Channel_t const a = MAX_CHANNEL)
			: a(a)
			, b(b)
			, g(g)
			, r(r)
		{
		}

		/**
		 * @brief Creates a new Color with the given R, G, B, and A values as Floats between 0.0 and 1.0.
		 * @param r The red value.
		 * @param g The green value.
		 * @param b The blue value.
		 * @param a The alpha value.
		 */
		explicit Color(Int const r, Int const g, Int const b, Int const a = MAX_CHANNEL);

		/**
		 * @brief Creates a new Color with the given R, G, B, and A values as Floats between 0.0 and 1.0.
		 * @param r The red value.
		 * @param g The green value.
		 * @param b The blue value.
		 * @param a The alpha value.
		 */
		explicit Color(Float const r, Float const g, Float const b, Float const a = 1.0f);

		/**
		 * @brief Creates a new Color from a packed Color_t value.
		 * @param value The packed color value.
		 */
		explicit Color(Color_t const value)
			: value(value)
		{
		}

#pragma endregion

#pragma region Operators

	public:
		constexpr Bool operator==(Color const& other) const { return value == other.value; }
		constexpr Bool operator!=(Color const& other) const { return value != other.value; }
		constexpr Bool operator<(Color const& other) const { return value < other.value; }
		constexpr Bool operator<=(Color const& other) const { return value <= other.value; }
		constexpr Bool operator>(Color const& other) const { return value > other.value; }
		constexpr Bool operator>=(Color const& other) const { return value >= other.value; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Gets the R value as a normalized Float between 0.0 and 1.0.
		 * @returns The R value.
		 */
		constexpr Float rf() const { return static_cast<Float>(r) / static_cast<Float>(MAX_CHANNEL); }

		/**
		 * @brief Gets the G value as a normalized Float between 0.0 and 1.0.
		 * @returns The G value.
		 */
		constexpr Float gf() const { return static_cast<Float>(g) / static_cast<Float>(MAX_CHANNEL); }

		/**
		 * @brief Gets the B value as a normalized Float between 0.0 and 1.0.
		 * @returns The B value.
		 */
		constexpr Float bf() const { return static_cast<Float>(b) / static_cast<Float>(MAX_CHANNEL); }

		/**
		 * @brief Gets the A value as a normalized Float between 0.0 and 1.0.
		 * @returns The A value.
		 */
		constexpr Float af() const { return static_cast<Float>(a) / static_cast<Float>(MAX_CHANNEL); }

		/**
		 * @brief Gets the R value as a linear Float.
		 * @returns The R value.
		 */
		inline Float rlf() const { return to_linear(rf()); }

		/**
		 * @brief Gets the G value as a linear Float.
		 * @returns The G value.
		 */
		inline Float glf() const { return to_linear(gf()); }

		/**
		 * @brief Gets the B value as a linear Float.
		 * @returns The B value.
		 */
		inline Float blf() const { return to_linear(bf()); }

		/**
		 * @brief Gets the A value as a linear Float.
		 * @returns The A value.
		 */
		constexpr Float alf() const { return af(); }

		/**
		 * @brief Converts this Color to a Float4.
		 * @returns The Float4 color.
		 */
		constexpr Float4 to_float4() const
		{
			return Float4(rf(), gf(), bf(), af());
		}

		/**
		 * @brief Converts this Color to a linear Float4.
		 * @returns The linear Float4 color.
		 */
		inline Float4 to_linear_float4() const
		{
			return Float4(rlf(), glf(), blf(), alf());
		}
		
		/**
		 * @brief Creates a black color.
		 * @returns The black color.
		 */
		inline static Color black() { return Color(MIN_CHANNEL, MIN_CHANNEL, MIN_CHANNEL); }

		/**
		 * @brief Creates a red color.
		 * @returns The red color.
		 */
		inline static Color red() { return Color(MAX_CHANNEL, MIN_CHANNEL, MIN_CHANNEL); }

		/**
		 * @brief Creates a green color.
		 * @returns The green color.
		 */
		inline static Color green() { return Color(MIN_CHANNEL, MAX_CHANNEL, MIN_CHANNEL); }

		/**
		 * @brief Creates a blue color.
		 * @returns The blue color.
		 */
		inline static Color blue() { return Color(MIN_CHANNEL, MIN_CHANNEL, MAX_CHANNEL); }

		/**
		 * @brief Creates a white color.
		 * @returns The white color.
		 */
		inline static Color white() { return Color(MAX_CHANNEL, MAX_CHANNEL, MAX_CHANNEL); }

		/**
		 * @brief Creates a yellow color.
		 * @returns The yellow color.
		 */
		inline static Color yellow() { return Color(MAX_CHANNEL, MAX_CHANNEL, MIN_CHANNEL); }

		/**
		 * @brief Creates a cyan color.
		 * @returns The cyan color.
		 */
		inline static Color cyan() { return Color(MIN_CHANNEL, MAX_CHANNEL, MAX_CHANNEL); }

		/**
		 * @brief Creates a magenta color.
		 * @returns The magenta color.
		 */
		inline static Color magenta() { return Color(MAX_CHANNEL, MIN_CHANNEL, MAX_CHANNEL); }

	private:
		inline static Float to_linear(Float value)
		{
			return (value <= 0.04045f) ? (value / 12.92f) : Math::pow((value + 0.055f) / 1.055f, 2.4f);
		}

#pragma endregion
	};

	template<>
	struct Parser<Color>
	{
        static Bool parse(StringView const str, Color &value);
        static String to_string(Color const &value);
	};
}

namespace std
{
	template<>
	struct hash<Minty::Color>
	{
		std::size_t operator()(Minty::Color const& color) const noexcept
		{
			return std::hash<Minty::Color::Color_t>{}(color.value);
		}
	};
}

#endif // MINTY_DATA_COLOR_H