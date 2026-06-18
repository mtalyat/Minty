#ifndef MINTY_MEMORY_HEAPALLOCATOR_H
#define MINTY_MEMORY_HEAPALLOCATOR_H

/**
 * @file HeapAllocator.h
 * @brief Header file for the HeapAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Memory/Allocator.h"

namespace Minty
{
    /**
     * @brief A heap allocator that uses the global new and delete operators.
     */
    class HeapAllocator
        : public Allocator<HeapAllocator>
    {
        friend class Allocator<HeapAllocator>;

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
         * @brief Initializes the HeapAllocator.
         */
        static void initialize()
        {
        }

        /**
         * @brief Disposes the HeapAllocator.
         */
        static void dispose()
        {
#ifdef MINTY_DEBUG
            MINTY_CHECK(s_globalAllocated == 0, ErrorCode::Memory_StrongLeakDetected);
#endif // MINTY_DEBUG
        }

    private:
        Any allocate_raw(Size const size)
        {
            if (size == 0)
            {
                return nullptr;
            }
            
#ifdef MINTY_DEBUG
            // Allocate memory and space for size
            Size const totalSize = size + sizeof(Size);
            Any const ptr = ::operator new(totalSize);
            if (ptr == nullptr)
            {
                return nullptr;
            }

            // Update allocation counters
            s_globalAllocated += totalSize;

            // Store size at the beginning of the block
            return Tool::create_block_ptr(ptr, totalSize);
#else
            Any const ptr = ::operator new(size);
            return ptr;
#endif // MINTY_DEBUG
        };

        void deallocate_raw(Any const ptr) noexcept
        {
#ifdef MINTY_DEBUG
            if (ptr == nullptr)
            {
                return;
            }

            // Retrieve size stored at the beginning of the block
            Any const blockPtr = Tool::get_block_ptr(ptr);
            Size const totalSize = *static_cast<Size const *>(blockPtr) + sizeof(Size); // Account for the size storage
            MINTY_ASSERT(s_globalAllocated >= totalSize, ErrorCode::Memory_DeallocationFailed);

            // Update allocation counters
            s_globalAllocated -= totalSize; // Account for the size storage

            // Deallocate the entire block
            ::operator delete(blockPtr);
#else
            ::operator delete(ptr);
#endif // MINTY_DEBUG
        }

#pragma endregion

#pragma region Variables

    protected:
#ifdef MINTY_DEBUG
        inline static Size s_globalAllocated = 0;
#endif // MINTY_DEBUG

#pragma endregion
    };
}

#endif // MINTY_MEMORY_HEAPALLOCATOR_H