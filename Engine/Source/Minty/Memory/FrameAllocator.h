#ifndef MINTY_MEMORY_FRAMEALLOCATOR_H
#define MINTY_MEMORY_FRAMEALLOCATOR_H

/**
 * @file FrameAllocator.h
 * @brief Header file for the FrameAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Memory/Allocator.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryStackInfo.h"

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
         * @brief Allocates memory of the given size.
         * @param size The size of memory to allocate.
         * @return A pointer to the allocated memory, or nullptr if allocation fails.
         */
        Any allocate(Size const size)
        {
            return this->allocate_impl(size);
        }

        /**
         * @brief Deallocates the memory pointed to by ptr.
         * @param ptr The pointer to the memory to deallocate.
         */
        void deallocate(Any const ptr) noexcept
        {
            this->deallocate_raw(ptr);
        }
        
        /**
         * @brief Clears the current memory stack.
         */
        static void reset()
        {
            // do nothing if not initialized
            if (sp_memoryStack != nullptr)
            {
                sp_memoryStack->reset();
            }
        }

        /**
         * @brief Initializes the frame allocator with a memory stack.
         * @param info The information for creating the memory stack.
         */
        static void initialize(MemoryStackInfo const &info)
        {
            MINTY_ASSERT(sp_memoryStack == nullptr, ErrorCode::Memory_AllocatorNotInitialized);
            sp_memoryStack = new MemoryStack(info);
        }

        /**
         * @brief Disposes of the memory stack.
         */
        static void dispose()
        {
            delete sp_memoryStack;
            sp_memoryStack = nullptr;
        }

    private:
        Any allocate_raw(Size const size)
        {
            MINTY_ASSERT(sp_memoryStack != nullptr, ErrorCode::Memory_AllocatorNotInitialized);
            Any const ptr = sp_memoryStack->allocate(size);
            return ptr;
        };

        void deallocate_raw(Any const ptr) noexcept
        {
            // NOOP
        }

#pragma endregion

#pragma region Variables

    protected:
        inline static MemoryStack *sp_memoryStack = nullptr;

#pragma endregion
    };
}

#endif // MINTY_MEMORY_FRAMEALLOCATOR_H