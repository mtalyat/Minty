#include "pch.h"
#include "ArgumentParser.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Math.h"

using namespace Minty;

void Minty::ArgumentParser::add_parameter(String const& name, Int const argc)
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(argc != 0, ErrorCode::Argument_ExpectedNonZero);

	m_positionalParams.add({ name, argc });
}

void Minty::ArgumentParser::add_parameter(String const& name, String const& flag, Int const argc)
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);

	Int index = static_cast<Int>(m_flagParams.get_size());
	m_flagParams.add({ name, argc });
	m_flagIndices.add(name, index);
	if (!flag.is_empty())
	{
		m_flagIndices.add(flag, index);
	}
}

void ArgumentParser::parse(Int const argc, Char const* argv[])
{
    MINTY_ASSERT(argc > 0, ErrorCode::Argument_ExpectedAboveZero);
    MINTY_ASSERT(argv != nullptr, ErrorCode::Argument_ExpectedNonNull);

    // Clear any previously parsed arguments
    m_args.clear();

    // Positional arguments
	Int i = 0;
	for (Parameter const& param : m_positionalParams)
	{
		// add args, if any
		Int count = param.argc;
		Int countAdj = Math::abs(count);
		for (Int j = 0; j < countAdj; ++j)
		{
			// if no more args...
			if (i >= argc || argv[i][0] == '-') // no more args OR next flag
			{
				if (count > 0)
				{
					// show error if required
					MINTY_LOG_ERROR(F("Not enough arguments for parameter: {}", i));
				}
				break;
			}
			m_args[param.name].args.add(argv[i]);
			++i;
		}
	}

	// flag arguments
	for (; i < argc; ++i)
	{
		Char const* arg = argv[i];
		Size argSize = strlen(arg);

		// if not flag, ignore
		if (!argSize || arg[0] != '-')
		{
			Debug::log(LogLevel::Warning, F("Ignoring argument: {}", arg));
			continue;
		}

		// search for flag
		String flag = &arg[1]; // ignore -
		auto it = m_flagIndices.find(flag);
		if (it == m_flagIndices.end())
		{
			Debug::log(LogLevel::Warning, F("Ignoring unknown flag: {}", arg));
			continue;
		}

		// get argument
		Int index = it->get_second();
		Parameter const& param = m_flagParams[index];
		Argument& argument = m_args[param.name];

		// add args, if any
		++i; // skip -name/-flag
		Int count = param.argc;
		Int countAdj = Math::abs(count);
		for (Int j = 0; j < countAdj; ++j)
		{
			// if no more args...
			if (i >= argc || argv[i][0] == '-') // no more args OR next flag
			{
				// negative count is optional
				if (count > 0)
				{
					// show error if required
					Debug::log(LogLevel::Error, F("Not enough arguments for parameter: {}", param.name));
				}
				break;
			}
			m_args[param.name].args.add(argv[i]);
			++i;
		}
		--i;
	}
}

Vector<String> const& Minty::ArgumentParser::get_argument(String const& name) const
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(m_args.contains(name), ErrorCode::Argument_KeyNotFound, name);
	return m_args[name].args;
}
