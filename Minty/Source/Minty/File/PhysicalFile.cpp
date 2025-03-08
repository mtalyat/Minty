#include "pch.h"
#include "PhysicalFile.h"

using namespace Minty;


Bool Minty::PhysicalFile::is_open() const
{
    return m_stream.is_open();
}

void Minty::PhysicalFile::open(Path const& path, Flags const flags)
{
    // close if open
    close();

    m_path = path;
    m_flags = flags;

    // open the file
    m_stream = std::fstream(path.get_string().get_data(), static_cast<std::ios_base::openmode>(flags));

    // check if open
    if (!m_stream.is_open())
    {
		MINTY_ASSERT(false, "Cannot open File at given Path.");
        return;
    }
}

void Minty::PhysicalFile::flush()
{
    m_stream.flush();
}

void Minty::PhysicalFile::close()
{
    if (is_open())
    {
        // close the stream
        m_stream.flush();
        m_stream.close();

        // reset all data
        m_flags = Flags::None;
        m_path = "";
    }
}

void Minty::PhysicalFile::seek(Position_t const offset, Direction const dir)
{
    seek_read(offset, dir);
    seek_write(offset, dir);
}

void Minty::PhysicalFile::seek_read(Position_t const offset, Direction const dir)
{
    m_stream.seekg(offset, static_cast<std::ios_base::seekdir>(dir));
}

void Minty::PhysicalFile::seek_write(Position_t const offset, Direction const dir)
{
    m_stream.seekp(offset, static_cast<std::ios_base::seekdir>(dir));
}

Bool Minty::PhysicalFile::end_of_file()
{
    return m_stream.eof();
}

File::Position_t Minty::PhysicalFile::tell()
{
    MINTY_ABORT("PhysicalFile::tell() not supported. Use tell_read() or tell_write().");
    return Position_t();
}

File::Position_t Minty::PhysicalFile::tell_read()
{
	return m_stream.tellg();
}

File::Position_t Minty::PhysicalFile::tell_write()
{
    return m_stream.tellp();
}

File::Size_t Minty::PhysicalFile::get_size() const
{
    return std::filesystem::file_size(m_path.get_string().get_data());
}

Char Minty::PhysicalFile::peek()
{
    return m_stream.peek();
}

Char Minty::PhysicalFile::get()
{
    return m_stream.get();
}

void Minty::PhysicalFile::read(void* const buffer, Size_t const size)
{
    m_stream.read(static_cast<Char*>(buffer), size);
}

Bool Minty::PhysicalFile::read_line(String& line)
{
    // get the line
	std::string temp;
    if (std::getline(m_stream, temp))
    {
        // remove the \r
        temp.erase(std::remove(temp.begin(), temp.end(), '\r'), temp.end());
        // update line
		line = String(temp.c_str());
        return true;
    }

    return false;
}

void Minty::PhysicalFile::write(void const* const buffer, Size_t const size)
{
    m_stream.write(static_cast<Char const* const>(buffer), size);
}