#pragma once

/**
 * @file BufferAllocator.hpp
 * @brief Header file for the BufferAllocator class, a simple allocator for temporary memory that is freed all at once by an outside source.
 * @author Mitchell Talyat
 */

#include "Allocator.hpp"

namespace Minty
{
    /**
     * @brief A simple allocator for temporary memory that is freed all at once by an outside source.
     */
    class BufferAllocator
        : public Allocator<BufferAllocator>
    {
        friend class Allocator<BufferAllocator>;

#pragma region Constructor

    public:
        BufferAllocator();

        BufferAllocator(Pointer const buffer, Size const capacity);

#pragma endregion

#pragma region Accessor

    public:
        inline Size get_capacity() const { return m_capacity; }

        inline Size get_size() const { return m_size; }

#pragma endregion

#pragma region Method

    private:
        Pointer allocate_raw(Size const size);

        void deallocate_raw(Pointer const ptr) noexcept;

#pragma endregion

#pragma region Variable

    private:
        Byte *mp_buffer;
        Size m_capacity;
        Size m_size;

#pragma endregion
    };
}