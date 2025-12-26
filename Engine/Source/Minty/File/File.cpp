#include "pch.h"
#include "File.h"
#include "Minty/File/PhysicalFile.h"

using namespace Minty;

void Minty::File::copy(Path const& from, Path const& to)
{
	std::filesystem::copy_file(from.get_string().get_data(), to.get_string().get_data(), std::filesystem::copy_options::overwrite_existing);
}

void Minty::File::move(Path const& from, Path const& to)
{
	std::filesystem::rename(from.get_string().get_data(), to.get_string().get_data());
}

void Minty::File::create(Path const& path)
{
	std::ofstream file(path.get_string().get_data());
	file.close();
}

void Minty::File::destroy(Path const& path)
{
	std::filesystem::remove(path.get_string().get_data());
}

Vector<String> Minty::File::read_lines(Path const& path)
{
	PhysicalFile file(path, FileFlags::Read);
	if(!file.is_open())
	{
		return Vector<String>();
	}
	return file.read_lines();
}

Vector<Byte> Minty::File::read_bytes(Path const& path)
{
	PhysicalFile file(path, FileFlags::Read | FileFlags::Binary);
	if (!file.is_open())
	{
		return Vector<Byte>();
	}
	return file.read_bytes();
}

String Minty::File::read_text(Path const& path)
{
	PhysicalFile file(path, FileFlags::Read);
	if (!file.is_open())
	{
		return String();
	}
	return file.read_text();
}

Bool Minty::File::write_lines(Path const& path, Vector<String> const& lines)
{
	PhysicalFile file(path, FileFlags::Write);
	if (!file.is_open())
	{
		return false;
	}
	return file.write_lines(lines);
}

Bool Minty::File::write_bytes(Path const& path, Vector<Byte> const& bytes)
{
	PhysicalFile file(path, FileFlags::Write | FileFlags::Binary);
	if (!file.is_open())
	{
		return false;
	}
	return file.write_bytes(bytes);
}

Bool Minty::File::write_text(Path const& path, String const& text)
{
	PhysicalFile file(path, FileFlags::Write);
	if (!file.is_open())
	{
		return false;
	}
	return file.write_text(text);
}

String Minty::File::read_text()
{
	Size const size = get_size();
	Char* const data = new Char[size];
	memset(data, 0, size);
	read(data, size);
	String text(data);
	delete[] data;
	return text;
}

Vector<String> Minty::File::read_lines()
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	Vector<String> lines;
	String line;
	while (read_line(line))
	{
		lines.add(std::move(line));
	}
	return lines;
}

Vector<Byte> Minty::File::read_bytes()
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	// get size in bytes
	set_position(0, FileDirection::End);
	Size size = get_position();

	// make space in vector
	Vector<Byte> bytes;
	bytes.resize(size, 0);

	// read bytes
	set_position(0, FileDirection::Begin);
	read(bytes.get_data(), size);

	return bytes;
}

Bool Minty::File::write_text(String const& text)
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	return write(text.get_data(), text.get_size());
}

Bool Minty::File::write_lines(Vector<String> const& lines)
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	for (String const& line : lines)
	{
		if(!write(line.get_data(), line.get_size()))
		{
			return false;
		}
		if(!write("\n", sizeof(Char)))
		{
			return false;
		}
	}
	return true;
}

Bool Minty::File::write_bytes(Vector<Byte> const& bytes)
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	return write(bytes.get_data(), bytes.get_size());
}
