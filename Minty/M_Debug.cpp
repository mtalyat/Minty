#include "pch.h"
#include "M_Debug.h"

#include "M_Stopwatch.h"

namespace minty
{
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

	void Debug::logError(unsigned int const code, std::string const& str)
	{
		if (msp_stopwatch)
		{
			// stopwatch, so print
			std::cout << "[" << msp_stopwatch->toString() << "] ERR CODE: " << code << ", ERR: " << str << END_OF_LINE;
		}
		else
		{
			// no stopwatch, just print
			std::cout << "ERR CODE: " << code << ", ERR: " << str << END_OF_LINE;
		}
	}

	void Debug::logError(unsigned int const code, std::string const& str, Object const& obj)
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

	void Debug::logErrorSDL(unsigned int const code, std::string const& str)
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
}
