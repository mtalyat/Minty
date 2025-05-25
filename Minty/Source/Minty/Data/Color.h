#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Holds a color value.
	/// </summary>
	struct Color
	{
#pragma region Types

	public:
		/// <summary>
		/// The color value type.
		/// </summary>
		using Color_t = Int;

		/// <summary>
		/// The color channel type.
		/// </summary>
		using Channel_t = Byte;

		/// <summary>
		/// The maximum value for a color channel.
		/// </summary>
		constexpr static Channel_t MAX_CHANNEL = 255;

		/// <summary>
		/// The minimum value for a color channel.
		/// </summary>
		constexpr static Channel_t MIN_CHANNEL = 0;

#pragma endregion

#pragma region Variables

	public:
		union
		{
			struct
			{
				/// <summary>
				/// The red component.
				/// </summary>
				Channel_t r;
				/// <summary>
				/// The green component.
				/// </summary>
				Channel_t g;
				/// <summary>
				/// The blue component.
				/// </summary>
				Channel_t b;
				/// <summary>
				/// The alpha component.
				/// </summary>
				Channel_t a;
			};

			/// <summary>
			/// The color value, within one integer.
			/// </summary>
			Color_t value;
		};

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Color with the given R, G, B, and A values.
		/// </summary>
		/// <param name="r">The red value.</param>
		/// <param name="g">The green value.</param>
		/// <param name="b">The blue value.</param>
		/// <param name="a">The alpha value.</param>
		constexpr Color(Channel_t const r, Channel_t const g, Channel_t const b, Channel_t const a = MAX_CHANNEL)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{
		}

		/// <summary>
		/// Creates a new Color with the given R, G, B, and A values.
		/// </summary>
		/// <param name="r">The red value.</param>
		/// <param name="g">The green value.</param>
		/// <param name="b">The blue value.</param>
		/// <param name="a">The alpha value.</param>
		constexpr Color(Int const r, Int const g, Int const b, Int const a = MAX_CHANNEL)
			: r(static_cast<Channel_t>(r))
			, g(static_cast<Channel_t>(g))
			, b(static_cast<Channel_t>(b))
			, a(static_cast<Channel_t>(a))
		{
			MINTY_ASSERT(r >= 0, "Red value cannot be below zero.");
			MINTY_ASSERT(g >= 0, "Green value cannot be below zero.");
			MINTY_ASSERT(b >= 0, "Blue value cannot be below zero.");
			MINTY_ASSERT(a >= 0, "Alpha value cannot be below zero.");
			MINTY_ASSERT(r <= MAX_CHANNEL, "Red value cannot be above MAX_CHANNEL.");
			MINTY_ASSERT(g <= MAX_CHANNEL, "Green value cannot be above MAX_CHANNEL.");
			MINTY_ASSERT(b <= MAX_CHANNEL, "Blue value cannot be above MAX_CHANNEL.");
			MINTY_ASSERT(a <= MAX_CHANNEL, "Alpha value cannot be above MAX_CHANNEL.");
		}

		/// <summary>
		/// Creates a new Color with the given R, G, B, and A values.
		/// </summary>
		/// <param name="r">The red value.</param>
		/// <param name="g">The green value.</param>
		/// <param name="b">The blue value.</param>
		/// <param name="a">The alpha value.</param>
		constexpr Color(Float const r, Float const g, Float const b, Float const a = 1.0f)
			: r(static_cast<Channel_t>(r* MAX_CHANNEL))
			, g(static_cast<Channel_t>(g* MAX_CHANNEL))
			, b(static_cast<Channel_t>(b* MAX_CHANNEL))
			, a(static_cast<Channel_t>(a* MAX_CHANNEL))
		{
			MINTY_ASSERT(r >= 0.0f, "Red value cannot be below zero.");
			MINTY_ASSERT(g >= 0.0f, "Green value cannot be below zero.");
			MINTY_ASSERT(b >= 0.0f, "Blue value cannot be below zero.");
			MINTY_ASSERT(a >= 0.0f, "Alpha value cannot be below zero.");
			MINTY_ASSERT(r <= 1.0f, "Red value cannot be above one.");
			MINTY_ASSERT(g <= 1.0f, "Green value cannot be above one.");
			MINTY_ASSERT(b <= 1.0f, "Blue value cannot be above one.");
			MINTY_ASSERT(a <= 1.0f, "Alpha value cannot be above one.");
		}

		/// <summary>
		/// Creates a new Color with the given color value.
		/// </summary>
		/// <param name="value">The color value.</param>
		constexpr Color(Color_t const value)
			: value(value)
		{
		}

#pragma endregion

#pragma region Operators

	public:
		constexpr Bool operator==(Color const& other) const
		{
			return value == other.value;
		}

		constexpr Bool operator!=(Color const& other) const
		{
			return value != other.value;
		}

		constexpr Bool operator<(Color const& other) const
		{
			return value < other.value;
		}

		constexpr Bool operator<=(Color const& other) const
		{
			return value <= other.value;
		}

		constexpr Bool operator>(Color const& other) const
		{
			return value > other.value;
		}

		constexpr Bool operator>=(Color const& other) const
		{
			return value >= other.value;
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Gets the R value as a normalized Float between 0.0 and 1.0.
		/// </summary>
		/// <returns>The R value.</returns>
		constexpr Float rf() const { return static_cast<Float>(r) / static_cast<Float>(MAX_CHANNEL); }

		/// <summary>
		/// Gets the G value as a normalized Float between 0.0 and 1.0.
		/// </summary>
		/// <returns>The G value.</returns>
		constexpr Float gf() const { return static_cast<Float>(g) / static_cast<Float>(MAX_CHANNEL); }

		/// <summary>
		/// Gets the B value as a normalized Float between 0.0 and 1.0.
		/// </summary>
		/// <returns>The B value.</returns>
		constexpr Float bf() const { return static_cast<Float>(b) / static_cast<Float>(MAX_CHANNEL); }

		/// <summary>
		/// Gets the A value as a normalized Float between 0.0 and 1.0.
		/// </summary>
		/// <returns>The A value.</returns>
		constexpr Float af() const { return static_cast<Float>(a) / static_cast<Float>(MAX_CHANNEL); }

		/// <summary>
		/// Converts this Color to a Float4. Each value is normalzed.
		/// </summary>
		/// <returns>The Float4 color.</returns>
		constexpr Float4 to_float4() const
		{
			return Float4(rf(), gf(), bf(), af());
		}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a black color.
		/// </summary>
		/// <returns></returns>
		inline static Color black() { return Color(MIN_CHANNEL, MIN_CHANNEL, MIN_CHANNEL); }

		/// <summary>
		/// Creates a red color.
		/// </summary>
		/// <returns></returns>
		inline static Color red() { return Color(MAX_CHANNEL, MIN_CHANNEL, MIN_CHANNEL); }

		/// <summary>
		/// Creates a green color.
		/// </summary>
		/// <returns></returns>
		inline static Color green() { return Color(MIN_CHANNEL, MAX_CHANNEL, MIN_CHANNEL); }

		/// <summary>
		/// Creates a blue color.
		/// </summary>
		/// <returns></returns>
		inline static Color blue() { return Color(MIN_CHANNEL, MIN_CHANNEL, MAX_CHANNEL); }

		/// <summary>
		/// Creates a white color.
		/// </summary>
		/// <returns></returns>
		inline static Color white() { return Color(MAX_CHANNEL, MAX_CHANNEL, MAX_CHANNEL); }

		/// <summary>
		/// Creates a yellow color.
		/// </summary>
		/// <returns></returns>
		inline static Color yellow() { return Color(MAX_CHANNEL, MAX_CHANNEL, MIN_CHANNEL); }

		/// <summary>
		/// Creates a cyan color.
		/// </summary>
		/// <returns></returns>
		inline static Color cyan() { return Color(MIN_CHANNEL, MAX_CHANNEL, MAX_CHANNEL); }

		/// <summary>
		/// Creates a magenta color.
		/// </summary>
		/// <returns></returns>
		inline static Color magenta() { return Color(MAX_CHANNEL, MIN_CHANNEL, MAX_CHANNEL); }

#pragma endregion
	};

	String to_string(Color const obj);
	Color parse_to_color(String const& string);
	Bool parse_try_color(String const& string, Color& value);
	template<>
	inline Color parse_to<Color>(String const& string) { return parse_to_color(string); }
	template<>
	inline Bool parse_try<Color>(String const& string, Color& value) { return parse_try_color(string, value); }
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