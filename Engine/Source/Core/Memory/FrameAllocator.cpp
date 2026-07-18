#include "FrameAllocator.hpp"

using namespace Minty;

void Minty::FrameAllocator::reset()
{
    // do nothing if not initialized
    if (sp_memoryStack != nullptr)
    {
        sp_memoryStack->reset();
    }
}

void Minty::FrameAllocator::initialize(MemoryStackInfo const &info)
{
    MINTY_ASSERT(sp_memoryStack == nullptr, ErrorCodeEnum::Memory_AllocatorNotInitialized);
    sp_memoryStack = new MemoryStack(info);
}

void Minty::FrameAllocator::dispose()
{
    delete sp_memoryStack;
    sp_memoryStack = nullptr;
}

Pointer Minty::FrameAllocator::allocate_raw(Size const size)
{
    MINTY_ASSERT(sp_memoryStack != nullptr, ErrorCodeEnum::Memory_AllocatorNotInitialized);
    Pointer const ptr = sp_memoryStack->allocate(size);
    return ptr;
}

void Minty::FrameAllocator::deallocate_raw(Pointer const ptr) noexcept
{
    // NOOP
}