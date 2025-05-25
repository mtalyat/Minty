#include "pch.h"
#include "EntityPath.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Bool Minty::EntityPath::parse(String const& text)
{
	// split the string into parts
	Vector<String> parts = String::split(text, '/');

	// parse to the path
	m_path.reserve(parts.get_size());
	for (Size i = 0; i < m_path.get_size(); i++)
	{
		// parse the byte
		Byte b;
		if (!try_byte(parts.at(i), b))
		{
			// failed to parse
			return false;
		}
		
		// add to the path
		m_path.add(b);
	}

	return true;
}

String Minty::EntityPath::to_string() const
{
	// write empty string if nothing
	if (m_path.is_empty())
	{
		return "";
	}

	// compile the path into a string separated by /
	String result = Minty::to_string(m_path.front());
	for (Size i = 1; i < m_path.get_size(); i++)
	{
		result.append('/');
		result.append(Minty::to_string(m_path.at(i)));
	}

	// write that
	return result;
}
