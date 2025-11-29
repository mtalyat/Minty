#include "DefaultAllocator.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

#ifdef MINTY_DEBUG

Size DefaultAllocator::s_size = 0;

Size Minty::DefaultAllocator::get_size_DEBUG()
{
    return s_size;
}

#endif // MINTY_DEBUG

Any Minty::DefaultAllocator::allocate(Size const size)
{
#ifdef MINTY_DEBUG

    Any const ptr = std::malloc(size + sizeof(Size));
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed);
    s_size += size;
    *(static_cast<Size *>(ptr)) = size;
    return static_cast<Byte *>(ptr) + sizeof(Size);

#else // MINTY_DEBUG

    Any const ptr = std::malloc(size);
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed);
    return ptr;

#endif // !MINTY_DEBUG
}

void Minty::DefaultAllocator::deallocate(Any const ptr)
{
    if(ptr == nullptr)
    {
        return;
    }

#ifdef MINTY_DEBUG

    Any const realPtr = static_cast<Byte *>(ptr) - sizeof(Size);
    Size const size = *(static_cast<Size *>(realPtr));
    s_size -= size;
    std::free(realPtr);

#else // MINTY_DEBUG

    std::free(ptr);

#endif // !MINTY_DEBUG
}