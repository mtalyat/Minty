#pragma once

#include "M_Object.h"
#include "M_Stopwatch.h"
#include <SDL.h>
#include <string>
#include <iostream>

#define MINTY_DEBUG_MODE_NONE 0b000
#define MINTY_DEBUG_MODE_LOG 0b001
#define MINTY_DEBUG_MODE_WARN 0b010
#define MINTY_DEBUG_MODE_ERROR 0b100
// error
#define MINTY_DEBUG_MODE_LOW 0b100
// error, warn
#define MINTY_DEBUG_MODE_MEDIUM 0b110
// error, warn, log
#define MINTY_DEBUG_MODE_HIGH 0b111
#define MINTY_DEBUG_MODE_ALL 0b111
#define MINTY_DEBUG_MODE_ON 0b111
#define MINTY_DEBUG_MODE_OFF 0b000

// assign this in main project
//#define MINTY_DEBUG_MODE MINTY_DEBUG_MODE_ALL


namespace minty
{
	/// <summary>
	/// Static class for debuging and testing.
	/// </summary>
	class MINTY_API Debug
	{
	private:
		// the game time stopwatch
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
		/// Debugs a string to the console, prepended by "WRN: ".
		/// </summary>
		/// <param name="str"></param>
		static void logWarning(std::string const& str);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: ".
		/// </summary>
		/// <param name="str"></param>
		static void logError(std::string const& str);

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