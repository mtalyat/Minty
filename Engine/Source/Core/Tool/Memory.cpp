#include "Memory.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

Pointer Minty::Tool::create_block_ptr(Pointer const ptr, Size const size)
{
    if (ptr == nullptr)
    {
        return nullptr;
    }

    MINTY_ASSERT(size > sizeof(Size), ErrorCodeEnum::Memory_UnallowedSize);

    Size const objectSize = size - sizeof(Size);
    Size* const sizePtr = static_cast<Size *>(ptr);
    *sizePtr = objectSize;
    return static_cast<Pointer>(sizePtr + 1);
}

Pointer Minty::Tool::get_block_ptr(Pointer const ptr)
{
    if (ptr == nullptr)
    {
        return nullptr;
    }

    return static_cast<Pointer>(static_cast<Size *>(ptr) - 1);
}

Size Minty::Tool::get_block_size(Pointer const ptr)
{
    if (ptr == nullptr)
    {
        return 0;
    }

    Size const* const sizePtr = static_cast<Size const *>(get_block_ptr(ptr));
    return *sizePtr;
}
