#include "pch.h"
#include "VirtualFile.h"
#include "Core/Debug/DebugF.h"

using namespace Minty;

StreamSize Minty::VirtualFile::get_size() const
{
    return m_virtualSize;
}

Bool Minty::VirtualFile::open(Path const& path, FileFlags const flags, StreamPosition const offset, Size const size)
{
    MINTY_ASSERT_B(!flags.has_flag(FileFlagsEnum::Truncate), ErrorCodeEnum::File_FlagNotSupported, flags);
	MINTY_ASSERT_B(!flags.has_flag(FileFlagsEnum::Append), ErrorCodeEnum::File_FlagNotSupported, flags);
	MINTY_ASSERT_B(!flags.has_flag(FileFlagsEnum::Write) || flags.has_flag(FileFlagsEnum::Read), ErrorCodeEnum::File_FlagNotSupported, flags);
    MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedAboveZero);

    Bool const opened = PhysicalFile::open(path, flags);
    if (!opened)
    {
        return false;
    }
    m_virtualOffset = offset;
    m_virtualSize = size;

    // seek to beginning of the virtual file
    set_position(0);

    return true;
}

StreamPosition Minty::VirtualFile::get_position()
{
    StreamPosition value = PhysicalFile::get_position();
    if (value == INVALID_FILE_POSITION)
    {
        return INVALID_FILE_POSITION;
    }
    return value - m_virtualOffset;
}

void Minty::VirtualFile::set_position(StreamPosition const offset, StreamDirectionEnum const dir)
{
    switch (dir)
    {
    case StreamDirectionEnum::Begin:
        PhysicalFile::set_position(m_virtualOffset + offset);
        break;
    case StreamDirectionEnum::Current:
        PhysicalFile::set_position(offset);
        break;
    case StreamDirectionEnum::End:
        PhysicalFile::set_position(offset + (m_virtualOffset + m_virtualSize));
        break;
    }
}

Bool Minty::VirtualFile::end_of_file()
{
	StreamPosition tellRead = get_position();
    return PhysicalFile::end_of_file() || (tellRead >= m_virtualSize) || tellRead == -1;
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
    MINTY_ASSERT(!end_of_file(), ErrorCodeEnum::File_EndOfFileReached);

    // read as per normal
	return PhysicalFile::read();
}

Bool Minty::VirtualFile::read(Pointer const buffer, StreamSize const size)
{
    // if not enough to read, stop
    StreamPosition const position = get_position();
    if(position + size > m_virtualSize)
    {
        MINTY_ERROR(ErrorCodeEnum::File_ReadFailed);
        return false;
    }
    
    // read as per normal
    return PhysicalFile::read(buffer, size);
}

Bool Minty::VirtualFile::read_line(String& line)
{
    StreamPosition before = get_position();

    // get the line
    std::string temp;
    if (std::getline(m_stream, temp))
    {
        // check if went past the end of the file
		StreamPosition after = get_position();
        // if end of file, set to virtual size
        if (after == INVALID_FILE_POSITION)
        {
			after = m_virtualSize;
        }
		if (after >= m_virtualSize)
		{
            // go to end of file
			set_position(0, StreamDirectionEnum::End);

            // cut off end of string
			StreamSize keep = m_virtualSize - before;
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

void Minty::VirtualFile::write(PointerConst const buffer, StreamSize const size)
{
    // check if going out of bounds
    // it is the responsibility of the caller to ensure they do not write past the virtual size
    MINTY_ASSERT(get_position() + size <= m_virtualSize, ErrorCodeEnum::File_WriteFailed);

    PhysicalFile::write(buffer, size);
}
