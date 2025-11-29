#ifndef MINTY_MEMORY_DEFAULTALLOCATOR_H
#define MINTY_MEMORY_DEFAULTALLOCATOR_H

/**
 * @file DefaultAllocator.h
 * @brief Header file for the DefaultAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
    /**
     * @class DefaultAllocator
     * @brief Static class providing memory allocation and deallocation using the default allocator.
     */
    class DefaultAllocator
    {
#pragma region Constructors

    public:
        DefaultAllocator() = delete;
        ~DefaultAllocator() = delete;

#pragma endregion

#pragma region Accessors

    public:
#ifdef MINTY_DEBUG
        /**
         * @brief Get the size of memory allocated by the default allocator.
         * @return The size of allocated memory in bytes.
         */
        static Size get_size_DEBUG();
#endif // MINTY_DEBUG

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Allocate memory using the default allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any allocate(Size const size);

        /**
         * @brief Deallocate memory using the default allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void deallocate(Any const ptr);

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
#ifdef MINTY_DEBUG
        static Size s_size;
#endif // MINTY_DEBUG

#pragma endregion
    };
}

#endif // MINTY_MEMORY_DEFAULTALLOCATOR_H