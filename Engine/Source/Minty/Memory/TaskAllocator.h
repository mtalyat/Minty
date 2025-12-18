#ifndef MINTY_MEMORY_TASKALLOCATOR_H
#define MINTY_MEMORY_TASKALLOCATOR_H

/**
 * @file TaskAllocator.h
 * @brief Header file for the TaskAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    class MemoryStack;
    struct MemoryStackInfo;

    class TaskAllocator
    {
#pragma region Constructors

    public:
        TaskAllocator() = delete;
        ~TaskAllocator() = delete;

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Initialize the task allocator with the specified information.
         * @param info The MemoryStackInfo containing initialization parameters.
         * @param count The number of stacks to create.
         */
        static void initialize(MemoryStackInfo const& info, Size const count);

        /**
         * @brief Shutdown the task allocator, freeing all allocated memory.
         */
        static void shutdown();

        /**
         * @brief Allocate memory using the task allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any allocate(Size const size);

        /**
         * @brief Deallocate memory using the task allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void deallocate(Any const ptr);

        /**
         * @brief Advance to the next task memory stack, freeing the new one.
         */
        static void advance();

        /**
         * @brief Construct an object of type T using the allocator.
         * @tparam T The type of the object to construct.
         */
        template<typename T, typename... Args>
        static T* construct(Args&&... args)
        {
            Any const ptr = allocate(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Construct an array of objects of type T using the allocator.
         * @tparam T The type of the objects to construct.
         */
        template<typename T, typename... Args>
        static T* construct_array(Size const count, Args&&... args)
        {
            Any const ptr = allocate(sizeof(T) * count);
            T* array = static_cast<T*>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&array[i]) T(std::forward<Args>(args)...);
            }
            return array;
        }

        /**
         * @brief Destruct an object of type T and deallocate its memory.
         * @tparam T The type of the object to destruct.
         */
        template<typename T>
        static void destruct(T* const object)
        {
            if (object == nullptr)
            {
                return;
            }

            object->~T();
            deallocate(static_cast<Any>(object));
        }

        /**
         * @brief Destruct an array of objects of type T and deallocate their memory.
         * @tparam T The type of the objects to destruct.
         */
        template<typename T>
        static void destruct_array(T* const array, Size const count)
        {
            if (array == nullptr)
            {
                return;
            }

            for (Size i = 0; i < count; ++i)
            {
                array[i].~T();
            }
            deallocate(static_cast<Any>(array));
        }

#pragma endregion

#pragma region Variables

    private:
        static MemoryStack* s_memoryStacks;
        static Size s_stackCount;
        static Size s_currentStack;

#pragma endregion
    };
}

#endif // MINTY_MEMORY_TASKALLOCATOR_H