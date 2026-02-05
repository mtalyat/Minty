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
	PhysicalFile file;
	if(!file.open(path, FileFlags::Read))
	{
		return Vector<String>();
	}
	return file.read_lines();
}

Vector<Byte> Minty::File::read_bytes(Path const& path)
{
	PhysicalFile file;
	if(!file.open(path, FileFlags::Read | FileFlags::Binary))
	{
		return Vector<Byte>();
	}
	return file.read_bytes();
}

String Minty::File::read_text(Path const& path)
{
	PhysicalFile file;
	if (!file.open(path, FileFlags::Read))
	{
		return String();
	}
	return file.read_text();
}

Bool Minty::File::write_lines(Path const& path, Vector<String> const& lines)
{
	PhysicalFile file;
	if (!file.open(path, FileFlags::Write))
	{
		return false;
	}
	file.write_lines(lines);
	return true;
}

Bool Minty::File::write_bytes(Path const& path, Vector<Byte> const& bytes)
{
	PhysicalFile file;
	if (!file.open(path, FileFlags::Write | FileFlags::Binary))
	{
		return false;
	}
	file.write_bytes(bytes);
	return true;
}

Bool Minty::File::write_text(Path const& path, String const& text)
{
	PhysicalFile file;
	if (!file.open(path, FileFlags::Write))
	{
		return false;
	}
	file.write_text(text);
	return true;
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
	set_position(0, StreamDirection::End);
	Size size = get_position();

	// make space in vector
	Vector<Byte> bytes;
	bytes.resize(size, 0);

	// read bytes
	set_position(0, StreamDirection::Begin);
	read(bytes.get_data(), size);

	return bytes;
}

void Minty::File::write_text(String const& text)
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	write(text.get_data(), text.get_size());
}

void Minty::File::write_lines(Vector<String> const& lines)
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	for (String const& line : lines)
	{
		write(line.get_data(), line.get_size());
		write("\n", sizeof(Char));
	}
}

void Minty::File::write_bytes(Vector<Byte> const& bytes)
{
	MINTY_ASSERT(is_open(), ErrorCode::File_NotOpen);

	write(bytes.get_data(), bytes.get_size());
}
