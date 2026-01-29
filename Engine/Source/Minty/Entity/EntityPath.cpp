#include "pch.h"
#include "EntityPath.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Tool/String.h"

using namespace Minty;

Bool Minty::Parser<EntityPath>::parse(StringView const str, EntityPath &value)
{
	value.clear();
	
    // split the string into parts
	Vector<String> parts = Tool::split(str, '/');

	// parse to the path
	value.m_path.reserve(parts.get_size());
	for (Size i = 0; i < parts.get_size(); i++)
	{
		// parse the byte
		Byte b;
		if (!Parser<Byte>::parse(parts.at(i), b))
		{
			// failed to parse
			return false;
		}
		
		// add to the path
		value.m_path.add(b);
	}

	return true;
}

String Minty::Parser<EntityPath>::to_string(EntityPath const &value)
{
	// write empty string if nothing
	if (value.is_empty())
	{
		return "";
	}

	// compile the path into a string separated by /
	StringBuilder builder(value.m_path.get_size() * 4);
	builder.append(Parser<Byte>::to_string(value.m_path.front()));
	for (Size i = 1; i < value.m_path.get_size(); i++)
	{
		builder.append('/');
		builder.append(Parser<Byte>::to_string(value.m_path.at(i)));
	}

	// write that
	return builder.get_string();
}

Minty::EntityPath::EntityPath()
			: m_path()
		{
		}

        Minty::EntityPath::EntityPath(Vector<Byte> const &path)
			: m_path(path)
		{
		}