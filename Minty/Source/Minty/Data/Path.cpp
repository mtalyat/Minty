#include "pch.h"
#include "Path.h"
#include "Minty/Data/Queue.h"
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
	if (lastSlash == INVALID_INDEX)
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
	if (firstDot == INVALID_INDEX)
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
	MINTY_ASSERT(false, "Not implemented.");
}

Path& Minty::Path::append(Path const& other)
{
	String str = other.get_string();
	m_path.append(str.get_data());
	return *this;
}

Bool Minty::Path::parse(String const& text)
{
	m_path = text.get_data();
	return true;
}

String Minty::Path::to_string() const
{
	return get_string();
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

Vector<Path> Minty::Path::get_files(Path const& path, Bool const recursive)
{
	MINTY_ASSERT(exists(path), "No directory exists at the given Path.");
	MINTY_ASSERT(is_directory(path), "The given path does not point to a directory.");

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : std::filesystem::directory_iterator(current.m_path))
		{
			if (entry.is_regular_file())
			{
				paths.add(Path(entry.path().string().data()));
			}
			else if (recursive && entry.is_directory())
			{
				directoriesToCheck.push(Path(entry.path().string().data()));
			}
		}
	}
	
	return paths;
}

Vector<Path> Minty::Path::get_directories(Path const& path, Bool const recursive)
{
	MINTY_ASSERT(exists(path), "No directory exists at the given Path.");
	MINTY_ASSERT(is_directory(path), "The given path does not point to a directory.");

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : std::filesystem::directory_iterator(current.m_path))
		{
			if (entry.is_directory())
			{
				Path entryPath = Path(entry.path().string().data());
				paths.add(entryPath);

				if (recursive)
				{
					directoriesToCheck.push(entryPath);
				}
			}
		}
	}

	return paths;
}

Vector<Path> Minty::Path::get_contents(Path const& path, Bool const recursive)
{
	MINTY_ASSERT(exists(path), "No directory exists at the given Path.");
	MINTY_ASSERT(is_directory(path), "The given path does not point to a directory.");

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : std::filesystem::directory_iterator(current.m_path))
		{
			if (entry.is_regular_file())
			{
				paths.add(Path(entry.path().string().data()));
			}
			else if (entry.is_directory())
			{
				Path entryPath = Path(entry.path().string().data());
				paths.add(entryPath);

				if (recursive)
				{
					directoriesToCheck.push(entryPath);
				}
			}
		}
	}

	return paths;
}

Bool Minty::Path::create(Path const& path)
{
	return std::filesystem::create_directories(path.m_path);
}

std::ostream& Minty::operator<<(std::ostream& stream, Path const& path)
{
	String str = path.get_string();
	stream << str.get_data();
	return stream;
}
