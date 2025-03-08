#include "pch.h"
#include "VirtualFile.h"

using namespace Minty;

PhysicalFile::Size_t Minty::VirtualFile::get_size() const
{
    return m_virtualSize;
}

void Minty::VirtualFile::open(Path const& path, Flags const flags, Position_t const offset, Size const size)
{
    MINTY_ASSERT((flags & Flags::Truncate) == Flags::None, "VirtualFiles are not allowed to be opened with the Truncate flag.");
	MINTY_ASSERT((flags & Flags::Append) == Flags::None, "VirtualFiles are not allowed to be opened with the Append flag.");
	MINTY_ASSERT((flags & Flags::Write) == Flags::None || (flags & Flags::Read) != Flags::None, "VirtualFiles are not allowed to be opened with the Write flag without an accompanying Read flag.");

    PhysicalFile::open(path, flags);
    m_virtualOffset = offset;
    m_virtualSize = size;

    // seek to beginning of the virtual file
    seek_write(0);
    seek_read(0);
}

void Minty::VirtualFile::seek_read(Position_t const offset, Direction seekDir)
{
    switch (seekDir)
    {
    case Direction::Begin:
        PhysicalFile::seek_read(m_virtualOffset + offset);
        break;
    case Direction::Current:
        PhysicalFile::seek_read(offset);
        break;
    case Direction::End:
        PhysicalFile::seek_read(offset + (m_virtualOffset + m_virtualSize));
        break;
    }
}

void Minty::VirtualFile::seek_write(Position_t const offset, Direction const seekDir)
{
    switch (seekDir)
    {
    case Direction::Begin:
        PhysicalFile::seek_write(m_virtualOffset + offset);
        break;
    case Direction::Current:
        PhysicalFile::seek_write(offset);
        break;
    case Direction::End:
        PhysicalFile::seek_write(offset + (m_virtualOffset + m_virtualSize));
        break;
    }
}

Bool Minty::VirtualFile::end_of_file()
{
	Position_t tellRead = tell_read();
    return PhysicalFile::end_of_file() || (tellRead >= m_virtualSize) || tellRead == -1;
}

PhysicalFile::Position_t Minty::VirtualFile::tell_read()
{
	Position_t value = PhysicalFile::tell_read();
    if (value == -1)
    {
        return -1;
    }
    return value - m_virtualOffset;
}

PhysicalFile::Position_t Minty::VirtualFile::tell_write()
{
    Position_t value = PhysicalFile::tell_write();
    if (value == -1)
    {
        return -1;
    }
    return value - m_virtualOffset;
}

Char Minty::VirtualFile::peek()
{
    if (end_of_file())
    {
		return '\0';
    }

	return PhysicalFile::peek();
}

Char Minty::VirtualFile::read()
{
    // if at the end of the file, stop
    if (end_of_file())
    {
        MINTY_ERROR("Cannot read_file from file to buffer. End Of File.");
        return '\0';
    }

    // read as per normal
	return PhysicalFile::read();
}

void Minty::VirtualFile::read(void* const buffer, Size_t const size)
{
    // if at the end of the file, stop
    if (end_of_file())
    {
        MINTY_ERROR("Cannot read_file from file to buffer. End Of File.");
        return;
    }

    // read as per normal
    PhysicalFile::read(buffer, size);
}

Bool Minty::VirtualFile::read_line(String& line)
{
    Position_t before = tell_read();

    // get the line
    std::string temp;
    if (std::getline(m_stream, temp))
    {
        // check if went past the end of the file
		Position_t after = tell_read();
        // if end of file, set to virtual size
        if (after == -1)
        {
			after = m_virtualSize;
        }
		if (after >= m_virtualSize)
		{
            // go to end of file
			seek_read(0, Direction::End);

            // cut off end of string
			Size_t keep = m_virtualSize - before;
			temp = temp.substr(0, keep);
		}

        // remove the \r
        temp.erase(std::remove(temp.begin(), temp.end(), '\r'), temp.end());
        
        // update line
        line = String(temp.c_str());
        return true;
    }

    return false;
}

void Minty::VirtualFile::write(void const* const buffer, Size_t const size)
{
    // cap the size to not go out of bounds
	Size_t cappedSize = size;
    Position_t position = tell_write();
	if (position + size > m_virtualSize)
	{
		cappedSize = m_virtualSize - position;
	}

    // write as per normal
    PhysicalFile::write(buffer, cappedSize);
}
