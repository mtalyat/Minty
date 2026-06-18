#include "pch.h"
#include "FileStream.h"
#include "Core/Debug/Debug.h"
#include "Core/File/File.h"

using namespace Minty;

Minty::FileStream::FileStream(Unique<File> &&file)
    : m_file(std::move(file))
{
}

StreamPosition Minty::FileStream::get_position()
{
    return m_file->get_position();
}

void Minty::FileStream::set_position(StreamPosition const position, StreamDirectionEnum const direction)
{
    m_file->set_position(position, direction);
}

StreamSize Minty::FileStream::get_size() const
{
    return m_file->get_size();
}

void Minty::FileStream::write(PointerConst const data, Size const size)
{
    m_file->write(data, static_cast<StreamSize>(size));
}

Bool Minty::FileStream::read(Pointer data, Size const size)
{
    MINTY_ASSERT(!end_of_stream(), ErrorCodeEnum::Object_InvalidState);

    StreamPosition const start = m_file->get_position();

    Bool const bytesRead = m_file->read(data, static_cast<StreamSize>(size));

    // If no bytes were read, return false
    if (!bytesRead)
    {
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
