#include "pch.h"
#include "PhysicalFile.h"
#include "Core/Debug/Debug.h"

using namespace Minty;

static std::ios_base::openmode minty_to_ios_base(FileFlags const flags)
{
    std::ios_base::openmode mode = std::ios_base::openmode(0);

    if (flags.has_flag(FileFlagsEnum::Read))
    {
        mode |= std::ios_base::in;
    }
    if (flags.has_flag(FileFlagsEnum::Write))
    {
        mode |= std::ios_base::out;
    }
    if (flags.has_flag(FileFlagsEnum::AtEnd))
    {
        mode |= std::ios_base::ate;
    }
    if (flags.has_flag(FileFlagsEnum::Append))
    {
        mode |= std::ios_base::app;
    }
    if (flags.has_flag(FileFlagsEnum::Binary))
    {
        mode |= std::ios_base::binary;
    }
    if (flags.has_flag(FileFlagsEnum::Truncate))
    {
        mode |= std::ios_base::trunc;
    }

    return mode;
}

Bool Minty::PhysicalFile::is_open() const
{
    return m_stream.is_open();
}

Bool Minty::PhysicalFile::open(Path const& path, FileFlags const flags)
{
    // close if open
    close();

    // open the file
    m_stream = std::fstream(path.get_string().get_data(), minty_to_ios_base(flags));

    // check if open
    if(!m_stream.is_open())
    {
        return false;
    }

    m_path = path;
    m_flags = flags;

    return true;
}

void Minty::PhysicalFile::flush()
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

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
        m_flags = FileFlagsEnum::None;
        m_path = "";
    }
}

StreamPosition Minty::PhysicalFile::get_position()
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

    return static_cast<StreamPosition>(m_stream.tellg());
}

void Minty::PhysicalFile::set_position(StreamPosition const offset, StreamDirectionEnum const dir)
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

    std::ios_base::seekdir const seekDir = static_cast<std::ios_base::seekdir>(dir);
    std::streamoff const streamOffset = static_cast<std::streamoff>(offset);

    m_stream.seekg(streamOffset, seekDir);
    m_stream.seekp(streamOffset, seekDir);
}

Bool Minty::PhysicalFile::end_of_file()
{    
    return !m_stream.is_open() || m_stream.eof();
}

StreamSize Minty::PhysicalFile::get_size() const
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

    return std::filesystem::file_size(m_path.get_string().get_data());
}

Char Minty::PhysicalFile::peek()
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

	int const result = m_stream.peek();
    if (result == -1)
    {
		return '\0';
    }
    else
    {
		return static_cast<Char>(result);
    }
}

Char Minty::PhysicalFile::read()
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

    int const result = m_stream.get();
    if (result == -1)
    {
        return '\0';
    }
    else
    {
        return static_cast<Char>(result);
    }
}

Bool Minty::PhysicalFile::read(Pointer const buffer, StreamSize const size)
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

    m_stream.read(static_cast<Char*>(buffer), size);
    return true;
}

Bool Minty::PhysicalFile::read_line(String& line)
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

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

void Minty::PhysicalFile::write(PointerConst const buffer, StreamSize const size)
{
    MINTY_ASSERT(is_open(), ErrorCodeEnum::File_NotOpen);

    m_stream.write(static_cast<Char const* const>(buffer), size);
}