#ifndef MINTY_MEMORY_FRAMEALLOCATOR_H
#define MINTY_MEMORY_FRAMEALLOCATOR_H

/**
 * @file FrameAllocator.h
 * @brief Header file for the FrameAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryStackInfo.h"

namespace Minty
{
    struct FrameAllocatorBase
    {
#pragma region Methods

    public:
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

#pragma endregion

#pragma region Variables

    protected:
        inline static MemoryStack *sp_memoryStack = nullptr;

#pragma endregion
    };

    /**
     * @brief A frame allocator that allocates from a memory stack that is cleared at the start of each frame.
     * @tparam T The type to allocate.
     */
    template <typename T>
    struct FrameAllocator
        : public FrameAllocatorBase
    {
#pragma region Types

    public:
        using value_type = T;

#pragma endregion

#pragma region Constructors

        FrameAllocator() = default;
        template <class U>
        FrameAllocator(const FrameAllocator<U> &) noexcept {}

#pragma endregion

#pragma region Methods

        T *allocate(Size const count)
        {
            MINTY_ASSERT(sp_memoryStack != nullptr, ErrorCode::Memory_AllocatorNotInitialized);
            Any const ptr = sp_memoryStack->allocate(count * sizeof(T));
            return static_cast<T *>(ptr);
        }

        T *allocate()
        {
            return allocate(1);
        }

        template <typename... Args>
        T *construct(Args &&...args)
        {
            Any const ptr = allocate();
            return new (ptr) T(std::forward<Args>(args)...);
        }

        template <typename... Args>
        T *construct_array(Size const count, Args &&...args)
        {
            Any const ptr = allocate(count);
            T *array = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&array[i]) T(std::forward<Args>(args)...);
            }
            return array;
        }

        T *construct_array(Size const count)
        {
            Any const ptr = allocate(count);
            T *array = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&array[i]) T();
            }
            return static_cast<T *>(ptr);
        }

        void deallocate(T *const ptr, Size const count) noexcept
        {
            // No-op for frame allocator
        }

        void deallocate(T *const ptr) noexcept
        {
            deallocate(ptr, 1);
        }

        void destruct(T *const object)
        {
            if (object == nullptr)
            {
                return;
            }

            object->~T();
            deallocate(object);
        }

        void destruct_array(T *const array, Size const count)
        {
            if (array == nullptr)
            {
                return;
            }

            for (Size i = 0; i < count; ++i)
            {
                array[i].~T();
            }
            deallocate(array, count);
        }

#pragma endregion
    };
}

#endif // MINTY_MEMORY_FRAMEALLOCATOR_H