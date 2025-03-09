#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
	/// <summary>
	/// A static class for writing to the terminal.
	/// </summary>
	class Console
	{
#pragma region Classes

	public:
		/// <summary>
		/// A color that can be used to write in the terminal.
		/// </summary>
		enum class Color
		{
			Black = 30,
			Red = 31,
			Green = 32,
			Yellow = 33,
			Blue = 34,
			Magenta = 35,
			Cyan = 36,
			White = 37,
			BrightBlack = 90,
			Gray = BrightBlack,
			BrightRed = 91,
			BrightGreen = 92,
			BrightYellow = 93,
			BrightBlue = 94,
			BrightMagenta = 95,
			BrightCyan = 96,
			BrightWhite = 97
		};

#pragma endregion

#pragma region Constructors

	private:
		Console() = delete;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Sets the foreground color attribute of the terminal.
		/// </summary>
		/// <param name="color">The color to use for text.</param>
		static void set_foreground_color(Color const color);

		/// <summary>
		/// Sets the background color attribute of the terminal.
		/// </summary>
		/// <param name="color">The color to use for the background.</param>
		static void set_background_color(Color const color);

		/// <summary>
		/// Resets all attributes in the terminal.
		/// </summary>
		static void reset();

		/// <summary>
		/// Writes nothing.
		/// </summary>
		constexpr static void write()
		{
			// base case, do nothing
		}

		/// <summary>
		/// Writes a newline to the terminal.
		/// </summary>
		inline static void write_line()
		{
			std::cout << "\n";
		}

		/// <summary>
		/// Writes the given value(s) to the terminal.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		inline static void write(T const& first, Args const&... args)
		{
			std::cout << first;
			write(args...);
		}

		/// <summary>
		/// Writes the given value(s) to the terminal and adds a newline.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		inline static void write_line(T const& first, Args const&... args)
		{
			std::cout << first;
			write(args...);
			std::cout << "\n";
		}

		/// <summary>
		/// Flushes the output buffer.
		/// </summary>
		inline static void flush()
		{
			std::cout << std::flush;
		}

#pragma endregion


	};
}