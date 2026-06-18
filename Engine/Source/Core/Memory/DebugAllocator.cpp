#include "DebugAllocator.h"

using namespace Minty;

Minty::DebugAllocator::DebugAllocator()
    : Allocator(),
      m_localAllocated(0)
{
}

Minty::DebugAllocator::DebugAllocator(DebugAllocator const &other) noexcept
    : Allocator(),
      m_localAllocated(0)
{
}

Minty::DebugAllocator::DebugAllocator(DebugAllocator &&other) noexcept
    : Allocator(),
      m_localAllocated(other.m_localAllocated)
{
    other.m_localAllocated = 0;
}

Minty::DebugAllocator::~DebugAllocator()
{
    MINTY_CHECK(m_localAllocated == 0, ErrorCodeEnum::Memory_StrongLeakDetected);
}

DebugAllocator &Minty::DebugAllocator::operator=(DebugAllocator const &other) noexcept
{
    if (this != &other)
    {
        m_localAllocated = 0;
    }
    return *this;
}

DebugAllocator &Minty::DebugAllocator::operator=(DebugAllocator &&other) noexcept
{
    if (this != &other)
    {
        m_localAllocated = other.m_localAllocated;
        other.m_localAllocated = 0;
    }
    return *this;
}

void Minty::DebugAllocator::initialize()
{
}

void Minty::DebugAllocator::dispose()
{
}

Pointer Minty::DebugAllocator::allocate_raw(Size const size)
{
    if (size == 0)
    {
        return nullptr;
    }

    // Allocate memory and space for size
    Size const totalSize = size + sizeof(Size);
    Pointer const ptr = ::operator new(totalSize);
    if (ptr == nullptr)
    {
        return nullptr;
    }

    // Update allocation counters
    m_localAllocated += totalSize;

    // Store size at the beginning of the block
    return Tool::create_block_ptr(ptr, totalSize);
}

void Minty::DebugAllocator::deallocate_raw(Pointer const ptr) noexcept
{
    if (ptr == nullptr)
    {
        return;
    }

    // Retrieve size stored at the beginning of the block
    Pointer const blockPtr = Tool::get_block_ptr(static_cast<Pointer>(ptr));
    Size const size = *static_cast<Size *>(blockPtr) + sizeof(Size); // Account for the size storage
    MINTY_ASSERT(m_localAllocated >= size, ErrorCodeEnum::Memory_DeallocationFailed);

    // Update allocation counters
    m_localAllocated -= size; // Account for the size storage

    // Deallocate the entire block
    ::operator delete(blockPtr);
}