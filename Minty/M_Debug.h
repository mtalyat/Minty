#pragma once

#include "M_Object.h"
#include "M_Stopwatch.h"
#include <SDL.h>
#include <string>
#include <iostream>

constexpr char END_OF_LINE = '\n';

namespace minty
{
	/// <summary>
	/// Static class for debuging and testing.
	/// </summary>
	class MINTY_API Debug
	{
	private:
		static Stopwatch* msp_stopwatch;

	public:
		/// <summary>
		/// Sets the Stopwatch that is used when debugging things to the console.
		/// </summary>
		/// <param name="stopwatch"></param>
		inline static void setWatch(Stopwatch* const stopwatch) { msp_stopwatch = stopwatch; }

		/// <summary>
		/// Debugs a string to the console, with no time stamp or other characters added.
		/// </summary>
		/// <param name="str"></param>
		static void logRaw(std::string const& str);

		/// <summary>
		/// Debugs a string to the console.
		/// </summary>
		/// <param name="str"></param>
		static void log(std::string const& str);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: ".
		/// </summary>
		/// <param name="str"></param>
		static void logError(int const code, std::string const& str);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: Object( ... ) " where ... is the given obj.toString().
		/// </summary>
		/// <param name="str"></param>
		/// <param name="obj"></param>
		static void logError(int const code, std::string const& str, Object const& obj);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: ", and postpended by the SDL error message.
		/// </summary>
		/// <param name="str"></param>
		static void logErrorSDL(int const code, std::string const& str);

		/// <summary>
		/// Debugs a string to the console, letting the user know of something that has not yet been implemented yet.
		/// </summary>
		/// <param name="message"></param>
		/// <param name="function"></param>
		/// <param name="file"></param>
		static void logNotImplemented(std::string const& message, std::string const& function, std::string const& file);
	};
}