#include "pch.h"
#include "VirtualFile.h"

using namespace Minty;

FileSize Minty::VirtualFile::get_size() const
{
    return m_virtualSize;
}

Bool Minty::VirtualFile::open(Path const& path, FileFlags const flags, FilePosition const offset, Size const size)
{
    MINTY_ASSERT_F((flags & FileFlags::Truncate) == FileFlags::None, ErrorCode::File_FlagNotSupported, flags);
	MINTY_ASSERT_F((flags & FileFlags::Append) == FileFlags::None, ErrorCode::File_FlagNotSupported, flags);
	MINTY_ASSERT_F((flags & FileFlags::Write) == FileFlags::None || (flags & FileFlags::Read) != FileFlags::None, ErrorCode::File_FlagNotSupported, flags);
    MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedAboveZero);

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

FilePosition Minty::VirtualFile::get_position()
{
    FilePosition value = PhysicalFile::get_position();
    if (value == INVALID_FILE_POSITION)
    {
        return INVALID_FILE_POSITION;
    }
    return value - m_virtualOffset;
}

void Minty::VirtualFile::set_position(FilePosition const offset, FileDirection const dir)
{
    switch (dir)
    {
    case FileDirection::Begin:
        PhysicalFile::set_position(m_virtualOffset + offset);
        break;
    case FileDirection::Current:
        PhysicalFile::set_position(offset);
        break;
    case FileDirection::End:
        PhysicalFile::set_position(offset + (m_virtualOffset + m_virtualSize));
        break;
    }
}

Bool Minty::VirtualFile::end_of_file()
{
	FilePosition tellRead = get_position();
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
    MINTY_ASSERT(!end_of_file(), ErrorCode::File_EndOfFileReached);

    // read as per normal
	return PhysicalFile::read();
}

Bool Minty::VirtualFile::read(Any const buffer, FileSize const size)
{
    // if not enough to read, stop
    FilePosition const position = get_position();
    if(position + size > m_virtualSize)
    {
        MINTY_ERROR(ErrorCode::File_ReadFailed);
        return false;
    }
    
    // read as per normal
    return PhysicalFile::read(buffer, size);
}

Bool Minty::VirtualFile::read_line(String& line)
{
    FilePosition before = get_position();

    // get the line
    std::string temp;
    if (std::getline(m_stream, temp))
    {
        // check if went past the end of the file
		FilePosition after = get_position();
        // if end of file, set to virtual size
        if (after == INVALID_FILE_POSITION)
        {
			after = m_virtualSize;
        }
		if (after >= m_virtualSize)
		{
            // go to end of file
			set_position(0, FileDirection::End);

            // cut off end of string
			FileSize keep = m_virtualSize - before;
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

Bool Minty::VirtualFile::write(AnyConst const buffer, FileSize const size)
{
    // if going out of bounds, do not write
    FilePosition const position = get_position();
    if(position + size > m_virtualSize)
    {
        MINTY_ERROR(ErrorCode::File_WriteFailed);
        return false;
    }

    return PhysicalFile::write(buffer, size);
}
