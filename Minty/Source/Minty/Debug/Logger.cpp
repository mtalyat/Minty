#include "pch.h"
#include "Logger.h"
#include <fstream>

using namespace Minty;

Minty::Logger::Logger(Path const& path)
	: Logger(new std::ofstream(path.get_string().get_data()), true)
{
}

Minty::Logger::Logger(std::ostream& stream)
	: Logger(&stream, false)
{
}
