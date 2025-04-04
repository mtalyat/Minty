#pragma once
#include "Minty/Core/Types.h"
#include <iostream>

#pragma region Macros

#ifdef NDEBUG
#define MINTY_RELEASE
#else
#define MINTY_DEBUG
#endif // NDEBUG

#ifdef MINTY_DEBUG

// if debugging and using Visual Studio, insert debug break
#ifdef _MSC_VER
#define MINTY_BREAK() __debugbreak()
#else
#define MINTY_BREAK()
#endif // _MSC_VER

#else
#define MINTY_BREAK()
#endif // MINTY_DEBUG

#define MINTY_DEBUG_INFO(message) "[", std::filesystem::path(__FILE__).filename().string(), "][", __func__, "()][line ", __LINE__, "] -> ", message

#ifdef MINTY_DEBUG
#define MINTY_LOG(message) Debug::write_message(message)
#else
#define MINTY_LOG(message)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
#define MINTY_INFO(message) Debug::write_info(message)
#else
#define MINTY_INFO(message)
#endif // MINTY_DEBUG

#define MINTY_ERROR(message) Debug::write_error(message)

#ifdef MINTY_DEBUG
#define MINTY_WARNING(message) Debug::write_warning(message)
#else
#define MINTY_WARNING(message)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
#define MINTY_ABORT(message) do { Debug::write_abort(message); throw std::runtime_error(message); } while(false)
#else
#define MINTY_ABORT(message) MINTY_ERROR(message)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
#define MINTY_ASSERT(expression, message) do { if(!(expression)) { MINTY_ABORT("(" #expression ") failed: " #message); } } while(false)
#else
#define MINTY_ASSERT(expression, message)
#endif // MINTY_DEBUG

#pragma endregion

namespace Minty
{
	/// <summary>
	/// A static class for writing output.
	/// </summary>
	class Debug
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
		Debug() = delete;

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
			// base case
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
		/// Writes a newline to the terminal.
		/// </summary>
		inline static void write_line()
		{
			std::cout << std::endl;
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
			std::cout << std::endl;
		}

		/// <summary>
		/// Flushes the output buffer.
		/// </summary>
		inline static void flush()
		{
			std::cout << std::flush;
		}

		/// <summary>
		/// Writes an abort message to the terminal.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		static void write_abort(T const& first, Args const&... args)
		{
			set_foreground_color(Color::Black);
			set_background_color(Color::BrightRed);
			write("[ABO] ", first, args...);
			reset();
			std::cout << std::endl;
		}

		/// <summary>
		/// Writes an error message to the terminal.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		static void write_error(T const& first, Args const&... args)
		{
			set_foreground_color(Color::BrightRed);
			write("[ERR] ", first, args...);
			reset();
			std::cout << std::endl;
		}

		/// <summary>
		/// Writes a warning message to the terminal.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		static void write_warning(T const& first, Args const&... args)
		{
			set_foreground_color(Color::BrightYellow);
			write("[WRN] ", first, args...);
			reset();
			std::cout << std::endl;
		}

		/// <summary>
		/// Writes a message to the terminal.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		static void write_message(T const& first, Args const&... args)
		{
			set_foreground_color(Color::White);
			write("[MSG] ", first, args...);
			reset();
			std::cout << std::endl;
		}

		/// <summary>
		/// Writes an info message to the terminal.
		/// </summary>
		/// <typeparam name="T">The first argument type to use.</typeparam>
		/// <typeparam name="...Args">The argument types to use.</typeparam>
		/// <param name="first">The first argument to write.</param>
		/// <param name="...args">The rest of the arguments to write.</param>
		template<typename T, typename... Args>
		static void write_info(T const& first, Args const&... args)
		{
			set_foreground_color(Color::BrightBlack);
			write("[INF] ", first, args...);
			reset();
			std::cout << std::endl;
		}

#pragma endregion
	};
}