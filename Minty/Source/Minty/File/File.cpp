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
	file.open(path, Flags::Read);
	return file.read_lines();
}

Vector<Byte> Minty::File::read_bytes(Path const& path)
{
	PhysicalFile file;
	file.open(path, Flags::Read | Flags::Binary);
	return file.read_bytes();
}

String Minty::File::read_text(Path const& path)
{
	PhysicalFile file;
	file.open(path, Flags::Read);
	return file.read_text();
}

void Minty::File::write_lines(Path const& path, Vector<String> const& lines)
{
	PhysicalFile file;
	file.open(path, Flags::Write);
	file.write_lines(lines);
}

void Minty::File::write_bytes(Path const& path, Vector<Byte> const& bytes)
{
	PhysicalFile file;
	file.open(path, Flags::Write | Flags::Binary);
	file.write_bytes(bytes);
}

void Minty::File::write_text(Path const& path, String const& text)
{
	PhysicalFile file;
	file.open(path, Flags::Write);
	file.write_text(text);
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
	// get size in bytes
	seek_read(0, Direction::End);
	Size size = tell_read();

	// make space in vector
	Vector<Byte> bytes;
	bytes.resize(size);

	// read bytes
	seek_read(0, Direction::Begin);
	read(bytes.get_data(), size);

	return bytes;
}

void Minty::File::write_text(String const& text)
{
	write(text.get_data(), text.get_size());
}

void Minty::File::write_lines(Vector<String> const& lines)
{
	for (String const& line : lines)
	{
		write(line.get_data(), line.get_size());
		write("\n", sizeof(Char));
	}
}

void Minty::File::write_bytes(Vector<Byte> const& bytes)
{
}
