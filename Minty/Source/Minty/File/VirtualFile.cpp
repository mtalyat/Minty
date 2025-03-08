#include "pch.h"
#include "VirtualFile.h"

using namespace Minty;

PhysicalFile::Size_t Minty::VirtualFile::get_size() const
{
    return m_virtualSize;
}

void Minty::VirtualFile::open(Path const& path, Flags const flags, Position_t const offset, Size const size)
{
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
    return PhysicalFile::end_of_file() || (tell_read() >= m_virtualSize);
}

PhysicalFile::Position_t Minty::VirtualFile::tell_read()
{
    return PhysicalFile::tell_read() - m_virtualOffset;
}

PhysicalFile::Position_t Minty::VirtualFile::tell_write()
{
    return PhysicalFile::tell_write() - m_virtualOffset;
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

void Minty::VirtualFile::write(void const* const buffer, Size_t const size)
{
    // ensure will not write out of bounds
    if (tell_read() + size >= m_virtualSize)
    {
        MINTY_ERROR("Failed to write to virtual file. Out of bounds.");
        return;
    }

    // write as per normal
    PhysicalFile::write(buffer, size);
}
