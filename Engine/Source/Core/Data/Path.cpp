#include "pch.h"
#include "Path.h"
#include "Core/Data/Queue.h"
#include "Core/Data/String.h"

using namespace Minty;

Minty::Path::Path()
			: m_path()
		{
		}

Minty::Path::Path(String const &string)
    : m_path(string.get_data())
{}

Minty::Path::Path(Char const* data)
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

Path Minty::Path::get_absolute() const
{
	return Path(std::filesystem::absolute(m_path).string().data());
}

Path Minty::Path::get_extension() const
{
	return Path(m_path.extension().string().data());
}

Path Minty::Path::get_extension_full() const
{
	// get the full path
	String fullPath = get_string();
	
	// find the last /
	Size lastSlash = fullPath.find_last('/');

	Size start;

	// if none, search whole string
	if (lastSlash == INVALID_SIZE)
	{
		start = 0;
	}
	else
	{
		// search after the last slash
		start = lastSlash + 1;
	}

	// find the first .
	Size firstDot = fullPath.find_first('.', start);

	// if none, return empty
	if (firstDot == INVALID_SIZE)
	{
		return Path();
	}

	// return from the first . to the end
	return Path(fullPath.sub(firstDot).get_data());
}

Path Minty::Path::get_relative_to(Path const& other) const
{
	return Path(m_path.lexically_relative(other.m_path).string().data());
}

Path Minty::Path::get_parent() const
{
	return Path(m_path.parent_path().string().data());
}

void Minty::Path::reserve(Size const capacity)
{
	MINTY_NOT_IMPLEMENTED();
}

Path& Minty::Path::append(Path const& other)
{
	String str = other.get_string();
	m_path.append(str.get_data());
	return *this;
}

Bool Minty::Path::exists(Path const& path)
{
	return std::filesystem::exists(path.m_path);
}

Bool Minty::Path::is_file(Path const& path)
{
	return std::filesystem::is_regular_file(path.m_path);
}

Bool Minty::Path::is_directory(Path const& path)
{
	return std::filesystem::is_directory(path.m_path);
}

Size Minty::Path::get_file_size(Path const& path)
{
	if (!exists(path))
	{
		return 0;
	}

	return std::filesystem::file_size(path.m_path);
}

Bool Minty::Path::create(Path const& path)
{
	return std::filesystem::create_directories(path.m_path);
}

void Minty::Path::destroy(Path const &path)
{
	std::filesystem::remove_all(path.m_path);
}

std::ostream& Minty::operator<<(std::ostream& stream, Path const& path)
{
	String str = path.get_string();
	stream << str.get_data();
	return stream;
}

Bool Minty::Parser<Path>::parse(StringView const str, Path &value)
{
	value.m_path = str.get_data();
	return true;
}

String Minty::Parser<Path>::to_string(Path const &value)
{
	return value.get_string();
}