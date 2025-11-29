#include "TaskAllocator.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryStackInfo.h"

void Minty::TaskAllocator::initialize(MemoryStackInfo const &info, Size const count)
{
    MINTY_ASSERT(s_memoryStacks == nullptr, ErrorCode::Object_AlreadyInitialized);

    s_memoryStacks = reinterpret_cast<MemoryStack*>(new Byte[count * sizeof(MemoryStack)]);
    s_stackCount = count;
    s_currentStack = 0;
    for (Size i = 0; i < count; i++)
    {
        new (&s_memoryStacks[i]) MemoryStack(info);
    }
}

void Minty::TaskAllocator::shutdown()
{
    MINTY_ASSERT(s_memoryStacks != nullptr, ErrorCode::Object_NotInitialized);

    for (Size i = 0; i < s_stackCount; i++)
    {
        s_memoryStacks[i].~MemoryStack();
    }
    delete[] reinterpret_cast<Byte*>(s_memoryStacks);
    s_memoryStacks = nullptr;
    s_stackCount = 0;
    s_currentStack = 0;
}

Any Minty::TaskAllocator::allocate(Size const size)
{
    MINTY_ASSERT(s_memoryStacks != nullptr, ErrorCode::Object_NotInitialized);

    return s_memoryStacks[s_currentStack].allocate(size);
}

void Minty::TaskAllocator::deallocate(Any const ptr)
{
    MINTY_ASSERT(s_memoryStacks != nullptr, ErrorCode::Object_NotInitialized);

    s_memoryStacks[s_currentStack].deallocate(ptr);
}

void Minty::TaskAllocator::advance()
{
    MINTY_ASSERT(s_memoryStacks != nullptr, ErrorCode::Object_NotInitialized);

    s_currentStack = (s_currentStack + 1) % s_stackCount;
    s_memoryStacks[s_currentStack].reset();
}
