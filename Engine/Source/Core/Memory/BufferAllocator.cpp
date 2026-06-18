#include "pch.h"
#include "BufferAllocator.h"

using namespace Minty;

Minty::BufferAllocator::BufferAllocator()
    : Allocator(),
    mp_buffer(nullptr),
    m_capacity(0)
{
}

Minty::BufferAllocator::BufferAllocator(Pointer const buffer, Size const bufferSize)
    : Allocator(),
    mp_buffer(static_cast<Byte*>(buffer)),
    m_capacity(bufferSize)
{
}

Pointer Minty::BufferAllocator::allocate_raw(Size const size)
{
    if (size == 0 || m_size + size > m_capacity)
    {
        return nullptr;
    }

    Pointer const ptr = mp_buffer + m_size;
    m_size += size;
    return ptr;
}

void Minty::BufferAllocator::deallocate_raw(Pointer const ptr) noexcept
{
    // BufferAllocator does not support deallocation of individual blocks, so this function does nothing.
}
