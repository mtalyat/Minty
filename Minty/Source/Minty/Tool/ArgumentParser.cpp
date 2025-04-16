#include "pch.h"
#include "ArgumentParser.h"

using namespace Minty;

void ArgumentParser::add_parameter(Parameter const& param)
{
	switch (param.type)
	{
	case Parameter::Type::POSITIONAL:
		m_positionalParams.add(param.index, param);
		break;
	case Parameter::Type::FLAG:
		m_flagParams.add(param.flag, param);
		break;
	}
}

void ArgumentParser::parse(Int const argc, Char const* argv[])
{
	Parameter const* param = nullptr;

	// iterate through all arguments
	for (Int i = 0; i < argc; i++)
	{
		// find positional argument or flag argument, flag takes priority
		char const* argument = argv[i];
		auto flagFound = m_flagParams.find(argument);
		auto posFound = m_positionalParams.find(i);

		Argument arg;

		if (flagFound != m_flagParams.end())
		{
			param = &flagFound->second;

			// grab values, store in argument
			for (Int j = 1; j <= param->argc && j + i <= argc; j++)
			{
				arg.args.add(argv[i + j]);
			}
		}
		else if (posFound != m_positionalParams.end())
		{
			param = &posFound->second;

			// grab values, store in argument
			for (Int j = 0; j < param->argc && j + i < argc; j++)
			{
				arg.args.add(argv[i + j]);
			}
		}
		else
		{
			// no arg found at this position
			continue;
		}

		// add/override to total arguments
		m_args[param->name] = arg;
	}
}

Bool ArgumentParser::get_argument(String const& name, Argument& arg)
{
	// try to find the arg
	auto argFound = m_args.find(name);
	if (argFound != m_args.end())
	{
		// found arg
		arg = argFound->second;

		return true;
	}

	// did not find arg
	return false;
}

Bool ArgumentParser::get_argument(String const& name)
{
	return m_args.find(name) != m_args.end();
}
