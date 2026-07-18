#pragma once

/**
 * @file FrameAllocator.h
 * @brief Header file for the FrameAllocator class.
 * @author Mitchell Talyat
 */

#include "Allocator.hpp"
#include "MemoryStack.hpp"
#include "MemoryStackInfo.hpp"

namespace Minty
{
    /**
     * @brief A default allocator that uses the global new and delete operators.
     */
    class FrameAllocator
        : public Allocator<FrameAllocator>
    {
        friend class Allocator<FrameAllocator>;

#pragma region Methods

    public:
        /**
         * @brief Clears the current memory stack.
         */
        static void reset();

        /**
         * @brief Initializes the frame allocator with a memory stack.
         * @param info The information for creating the memory stack.
         */
        static void initialize(MemoryStackInfo const &info);

        /**
         * @brief Disposes of the memory stack.
         */
        static void dispose();

    private:
        Pointer allocate_raw(Size const size);

        void deallocate_raw(Pointer const ptr) noexcept;

#pragma endregion

#pragma region Variables

    protected:
        inline static MemoryStack *sp_memoryStack = nullptr;

#pragma endregion
    };
}