#include "pch.h"
#include "Path.h"
#include "Minty/Data/String.h"

using namespace Minty;

Minty::Path::Path(String const& string, Allocator const allocator)
	: m_path(string.get_data())
{}

Minty::Path::Path(Char const* data, Allocator const allocator)
	: m_path(data)
{}

Path Minty::Path::operator+(Path const& other) const
{
	return Path(*this).append(other);
}

Path Minty::Path::operator/(Path const& other) const
{
	return Path(*this).append(other);
}

void Minty::Path::reserve(Size const capacity)
{
	MINTY_ASSERT(false, "Not implemented.");
}

Path& Minty::Path::append(Path const& other)
{
	String str = other.get_string();
	m_path.append(str.get_data());
	return *this;
}

std::ostream& Minty::operator<<(std::ostream& stream, Path const& path)
{
	String str = path.get_string();
	stream << str.get_data();
	return stream;
}
