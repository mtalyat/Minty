#include "FileStream.h"
#include "Minty/Debug/Debug.h"
#include "Minty/File/File.h"

using namespace Minty;

Minty::FileStream::FileStream(Shared<File> const &file)
    : m_file(file)
{
}

StreamPosition Minty::FileStream::get_position()
{
    return m_file->get_position();
}

void Minty::FileStream::set_position(StreamPosition const position, StreamDirection const direction)
{
    m_file->set_position(position, direction);
}

StreamSize Minty::FileStream::get_size() const
{
    return m_file->get_size();
}

void Minty::FileStream::write(AnyConst const data, Size const size)
{
    m_file->write(data, static_cast<StreamSize>(size));
}

Bool Minty::FileStream::read(Any data, Size const size)
{
    MINTY_ASSERT(!end_of_stream(), ErrorCode::Object_InvalidState);

    StreamPosition const start = m_file->get_position();

    StreamSize const bytesRead = m_file->read(data, static_cast<StreamSize>(size));

    // If no bytes were read, return false
    if (bytesRead == 0)
    {
        return false;
    }

    // If fewer bytes were read than requested, reset the position and return false
    if (bytesRead < static_cast<StreamSize>(size))
    {
        m_file->set_position(start, StreamDirection::Begin);
        return false;
    }

    // Read successfully
    return true;
}

Char Minty::FileStream::peek()
{
    if(end_of_stream())
    {
        return '\0';
    }

    return m_file->peek();
}

Bool Minty::FileStream::end_of_stream()
{
    return m_file->end_of_file();
}

void Minty::FileStream::flush()
{
    m_file->flush();
}
