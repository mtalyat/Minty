#include "HeapAllocator.hpp"
#include "Core/Debug/Debug.hpp"
#include "Core/Tool/Memory.hpp"

using namespace Minty;

void Minty::HeapAllocator::initialize()
{
}

void Minty::HeapAllocator::dispose()
{
#ifdef MINTY_DEBUG
    MINTY_CHECK(s_globalAllocated == 0, ErrorCodeEnum::Memory_StrongLeakDetected);
#endif // MINTY_DEBUG
}

Pointer Minty::HeapAllocator::allocate_raw(Size const size)
{
    if (size == 0)
    {
        return nullptr;
    }

#ifdef MINTY_DEBUG
    // Allocate memory and space for size
    Size const totalSize = size + sizeof(Size);
    Pointer const ptr = ::operator new(totalSize);
    if (ptr == nullptr)
    {
        return nullptr;
    }

    // Update allocation counters
    s_globalAllocated += totalSize;

    // Store size at the beginning of the block
    return Tool::create_block_ptr(ptr, totalSize);
#else
    Pointer const ptr = ::operator new(size);
    return ptr;
#endif // MINTY_DEBUG
}

void Minty::HeapAllocator::deallocate_raw(Pointer const ptr) noexcept
{
#ifdef MINTY_DEBUG
    if (ptr == nullptr)
    {
        return;
    }

    // Retrieve size stored at the beginning of the block
    Pointer const blockPtr = Tool::get_block_ptr(ptr);
    Size const totalSize = *static_cast<Size const *>(blockPtr) + sizeof(Size); // Account for the size storage
    MINTY_ASSERT(s_globalAllocated >= totalSize, ErrorCodeEnum::Memory_DeallocationFailed);

    // Update allocation counters
    s_globalAllocated -= totalSize; // Account for the size storage

    // Deallocate the entire block
    ::operator delete(blockPtr);
#else
    ::operator delete(ptr);
#endif // MINTY_DEBUG
}