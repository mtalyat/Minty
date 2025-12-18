#include "FrameAllocator.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryStackInfo.h"

using namespace Minty;

MemoryStack* FrameAllocator::s_memoryStack = nullptr;

void Minty::FrameAllocator::initialize(MemoryStackInfo const &info)
{
    MINTY_ASSERT(s_memoryStack == nullptr,  ErrorCode::Object_AlreadyInitialized);

    s_memoryStack = new MemoryStack(info);
}

void Minty::FrameAllocator::shutdown()
{
    MINTY_ASSERT(s_memoryStack != nullptr, ErrorCode::Object_NotInitialized);
    MINTY_ASSERT(s_memoryStack->get_size() == 0, ErrorCode::Memory_WeakLeakDetected);

    delete s_memoryStack;
    s_memoryStack = nullptr;
}

Any Minty::FrameAllocator::allocate(Size const size)
{
    MINTY_ASSERT(s_memoryStack != nullptr, ErrorCode::Object_NotInitialized);

    return s_memoryStack->allocate(size);
}

void Minty::FrameAllocator::deallocate(Any const ptr)
{
    MINTY_ASSERT(s_memoryStack != nullptr, ErrorCode::Object_NotInitialized);

    // s_memoryStack->deallocate(ptr);
    // Note: FrameAllocator deallocation is a no-op. Memory is freed on reset.
}

void Minty::FrameAllocator::reset()
{
    MINTY_ASSERT(s_memoryStack != nullptr, ErrorCode::Object_NotInitialized);

    s_memoryStack->reset();
}
