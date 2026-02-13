#include "Memory.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Any Minty::Tool::create_block_ptr(Any const ptr, Size const size)
{
    if (ptr == nullptr)
    {
        return nullptr;
    }

    MINTY_ASSERT(size > sizeof(Size), ErrorCode::Memory_UnallowedSize);

    Size const objectSize = size - sizeof(Size);
    Size* const sizePtr = static_cast<Size *>(ptr);
    *sizePtr = objectSize;
    return static_cast<Any>(sizePtr + 1);
}

Any Minty::Tool::get_block_ptr(Any const ptr)
{
    if (ptr == nullptr)
    {
        return nullptr;
    }

    return static_cast<Any>(static_cast<Size *>(ptr) - 1);
}

Size Minty::Tool::get_block_size(Any const ptr)
{
    if (ptr == nullptr)
    {
        return 0;
    }

    Size const* const sizePtr = static_cast<Size const *>(get_block_ptr(ptr));
    return *sizePtr;
}
