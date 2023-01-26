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
	class Debug
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
		/// Debugs a string to the console, followed by the given T.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="str"></param>
		/// <param name="value"></param>
		template<typename T>
		static void log(std::string const& str, T const value);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: ".
		/// </summary>
		/// <param name="str"></param>
		static void logError(std::string const& str);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: Object( ... ) " where ... is the given obj.toString().
		/// </summary>
		/// <param name="str"></param>
		/// <param name="obj"></param>
		static void logError(std::string const& str, Object const& obj);

		/// <summary>
		/// Debugs a string to the console, prepended by "ERR: ", and postpended by the SDL error message.
		/// </summary>
		/// <param name="str"></param>
		static void logErrorSDL(std::string const& str);
	};

	template<typename T>
	void Debug::log(std::string const& str, T const value)
	{
		std::cout << str << value << END_OF_LINE;

		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] " << str << value << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << str << value << END_OF_LINE;
		}
	}
}