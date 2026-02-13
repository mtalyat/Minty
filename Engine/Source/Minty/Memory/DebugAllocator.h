#ifndef MINTY_MEMORY_DEBUGALLOCATOR_H
#define MINTY_MEMORY_DEBUGALLOCATOR_H

/**
 * @file DebugAllocator.h
 * @brief Header file for the DebugAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Tool/Memory.h"
#include "Minty/Memory/Allocator.h"

namespace Minty
{
#ifdef MINTY_DEBUG
    /**
     * @brief A debug allocator that uses the global new and delete operators.
     */
    class DebugAllocator
        : public Allocator<DebugAllocator>
    {
        friend class Allocator<DebugAllocator>;

#pragma region Constructors

    public:
        DebugAllocator()
            : m_localAllocated(0)
        {
        }

        DebugAllocator(DebugAllocator const &other) noexcept
            : m_localAllocated(0)
        {
        }

        DebugAllocator(DebugAllocator &&other) noexcept
            : m_localAllocated(other.m_localAllocated)
        {
            other.m_localAllocated = 0;
        }

        ~DebugAllocator()
        {
            MINTY_CHECK(m_localAllocated == 0, ErrorCode::Memory_StrongLeakDetected);
        }

#pragma endregion

#pragma region Operators

    public:
        DebugAllocator &operator=(DebugAllocator const &other) noexcept
        {
            if(this != &other)
            {
                m_localAllocated = other.m_localAllocated;
            }
            return *this;
        }

        DebugAllocator &operator=(DebugAllocator &&other) noexcept
        {
            if(this != &other)
            {
                m_localAllocated = other.m_localAllocated;
                other.m_localAllocated = 0;
            }
            return *this;
        }

#pragma endregion

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
         * @brief Initializes the DebugAllocator.
         */
        static void initialize()
        {
            // NOOP
        }

        /**
         * @brief Disposes the DebugAllocator.
         */
        static void dispose()
        {
            // NOOP
        }

    private:
        Any allocate_raw(Size const size)
        {
            if (size == 0)
            {
                return nullptr;
            }
            
            // Allocate memory and space for size
            Size const totalSize = size + sizeof(Size);
            Any const ptr = ::operator new(totalSize);
            if (ptr == nullptr)
            {
                return nullptr;
            }

            // Update allocation counters
            m_localAllocated += totalSize;

            // Store size at the beginning of the block
            return Tool::create_block_ptr(ptr, totalSize);
        };

        void deallocate_raw(Any const ptr) noexcept
        {
            if (ptr == nullptr)
            {
                return;
            }

            // Retrieve size stored at the beginning of the block
            Any const blockPtr = Tool::get_block_ptr(static_cast<Any>(ptr));
            Size const size = *static_cast<Size *>(blockPtr) + sizeof(Size); // Account for the size storage
            MINTY_ASSERT(m_localAllocated >= size, ErrorCode::Memory_DeallocationFailed);

            // Update allocation counters
            m_localAllocated -= size; // Account for the size storage

            // Deallocate the entire block
            ::operator delete(blockPtr);
        }

#pragma endregion

#pragma region Variables

    private:
        Size m_localAllocated;

#pragma endregion
    };
#endif // MINTY_DEBUG
}

#endif // MINTY_MEMORY_DEBUGALLOCATOR_H