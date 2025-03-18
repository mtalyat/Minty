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
	Vector<String> lines;
	String line;
	while (file.read_line(line))
	{
		lines.add(std::move(line));
	}
	return lines;
}

String Minty::File::read_text(Path const& path)
{
	PhysicalFile file;
	file.open(path, Flags::Read);
	Size const size = file.get_size();
	Char* const data = new Char[size];
	memset(data, 0, size);
	file.read(data, size);
	String text(data);
	delete[] data;
	return text;
}

void Minty::File::write_lines(Path const& path, Vector<String> const& lines)
{
	PhysicalFile file;
	file.open(path, Flags::Write);
	for (String const& line : lines)
	{
		file.write(line.get_data(), line.get_size());
		file.write("\n", sizeof(Char));
	}
}

void Minty::File::write_text(Path const& path, String const& text)
{
	PhysicalFile file;
	file.open(path, Flags::Write);
	file.write(text.get_data(), text.get_size());
}
