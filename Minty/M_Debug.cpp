#include "pch.h"
#include "M_Debug.h"

#include "M_Stopwatch.h"

namespace minty
{
	constexpr char END_OF_LINE = '\n';

	Stopwatch* Debug::msp_stopwatch = nullptr;

	void Debug::logRaw(std::string const& str)
	{
		std::cout << str;
	}

	void Debug::log(std::string const& str)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] " << str << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << str << END_OF_LINE;
		}
	}

	void Debug::logWarning(std::string const& str)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] WRN: " << str << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << "WRN: " << str << END_OF_LINE;
		}
	}

	void Debug::logError(std::string const& str)
	{
		logError(-1, str);
	}

	void Debug::logError(int const code, std::string const& str)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] ";
		}

		if (code >= 0)
		{
			// error code, so print
			std::cout << "ERR CODE: " << code << ", ";
		}

		// print error message
		std::cout << "ERR: " << str << END_OF_LINE;
	}

	void Debug::logError(int const code, std::string const& str, Object const& obj)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] ERR CODE: " << code <<  ", ERR: Object(" << obj.toString() << ") " << str << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << "ERR CODE: " << code << ", ERR: Object(" << obj.toString() << ") " << str << END_OF_LINE;
		}
	}

	void Debug::logErrorSDL(int const code, std::string const& str)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] ERR CODE: " << code << ", ERR: " << str << " Error: \"" << SDL_GetError() << "\"" << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << "ERR CODE: " << code << ", ERR: " << str << " Error: \"" << SDL_GetError() << "\"" << END_OF_LINE;
		}
	}

	void Debug::logNotImplemented(std::string const& notImplemented, std::string const& function, std::string const& file)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] WARN: " << notImplemented << " has not been implemented yet. Function: " << function << ", File: " << file << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << "WARN: " << notImplemented << " has not been implemented yet. Function: " << function << ", File: " << file << END_OF_LINE;
		}
	}
}
