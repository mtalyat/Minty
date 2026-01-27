#include "MemoryStream.h"

using namespace Minty;

MemoryStream::MemoryStream(Shared<Container> const& container)
    : m_container(container), m_position(0)
{
}

void MemoryStream::write(AnyConst const data, Size const size)
{
    // ensure there is enough capacity
    Size const requiredSize = m_position + size;
    if (requiredSize > m_container->get_capacity())
    {
        Size const newSize = m_container->get_capacity() == 0 ? requiredSize : m_container->get_capacity() * 2;
        Bool const reserved = m_container->reserve(newSize);
        MINTY_ASSERT(reserved, ErrorCode::Memory_AllocationFailed);
    }

    // copy data into container
    m_container->resize(requiredSize);
    m_container->set_at(data, size, m_position);
    m_position += size;
}

Bool MemoryStream::read(Any data, Size const size)
{
    // if not enough space to read, return false
    if (m_position + size > m_container->get_size())
    {
        return false;
    }

    // copy data from container to data
    std::memcpy(data, static_cast<Byte const*>(m_container->get_data()) + m_position, size);
    m_position += size;
    return true;
}

StreamPosition Minty::MemoryStream::get_position()
{
    return m_position;
}

void Minty::MemoryStream::set_position(StreamPosition const position, StreamDirection const direction)
{
    switch (direction)
    {
        case StreamDirection::Begin:
            MINTY_ASSERT(position >= 0 && position <= static_cast<StreamPosition>(m_container->get_size()), ErrorCode::Argument_OutOfRange);
            m_position = position;
            break;
        case StreamDirection::Current:
            MINTY_ASSERT(m_position + position <= static_cast<StreamPosition>(m_container->get_size()) && m_position + position >= 0, ErrorCode::Argument_OutOfRange);
            m_position += position;
            break;
        case StreamDirection::End:
            MINTY_ASSERT(position <= 0 && static_cast<StreamPosition>(m_container->get_size()) + position >= 0, ErrorCode::Argument_OutOfRange);
            m_position = static_cast<StreamPosition>(m_container->get_size()) + position;
            break;
        default:
            MINTY_NOT_IMPLEMENTED();
            break;
    }
}

StreamSize Minty::MemoryStream::get_size() const
{
    return static_cast<StreamSize>(m_container->get_size());
}

Char MemoryStream::peek()
{
    if (end_of_stream())
    {
        return '\0';
    }

    AnyConst const ptr = m_container->get_at(m_position);
    Char const ch = *static_cast<Char const*>(ptr);
    return ch;
}

Bool MemoryStream::end_of_stream()
{
    return m_position >= 0 && static_cast<Size>(m_position) >= m_container->get_size();
}

void Minty::MemoryStream::flush()
{
    // No-op for MemoryStream
}
