#include "FileStream.h"
#include "Minty/Debug/Debug.h"
#include "Minty/File/File.h"

using namespace Minty;

Minty::FileStream::FileStream(Shared<File> const &file)
    : m_file(file)
{
}

Bool Minty::FileStream::write(AnyConst const data, Size const size)
{
    MINTY_ASSERT(m_file != nullptr, ErrorCode::Object_InvalidState);

    return m_file->write(data, static_cast<FileSize>(size));
}

Bool Minty::FileStream::read(Any data, Size const size)
{
    MINTY_ASSERT(m_file != nullptr, ErrorCode::Object_InvalidState);
    MINTY_ASSERT(!end_of_stream(), ErrorCode::Object_InvalidState);

    FilePosition const start = m_file->get_position();

    FileSize const bytesRead = m_file->read(data, static_cast<FileSize>(size));

    // If no bytes were read, return false
    if (bytesRead == 0)
    {
        return false;
    }

    // If fewer bytes were read than requested, reset the position and return false
    if (bytesRead < static_cast<FileSize>(size))
    {
        m_file->set_position(start, FileDirection::Begin);
        return false;
    }

    // Read successfully
    return true;
}

Char Minty::FileStream::peek()
{
    MINTY_ASSERT(m_file != nullptr, ErrorCode::Object_InvalidState);
    
    if(end_of_stream())
    {
        return '\0';
    }

    return m_file->peek();
}

Bool Minty::FileStream::end_of_stream()
{
    MINTY_ASSERT(m_file != nullptr, ErrorCode::Object_InvalidState);

    return m_file->end_of_file();
}
