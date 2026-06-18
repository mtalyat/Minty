#ifndef MINTY_MEMORY_ALLOCATOR_H
#define MINTY_MEMORY_ALLOCATOR_H

/**
 * @file Allocator.h
 * @brief Header file for the Allocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Tool/Memory.h"

namespace Minty
{
    /**
     * @brief A base class for memory allocators using the Curiously Recurring Template Pattern (CRTP).
     * @tparam Derived The derived allocator class that implements the actual allocation and deallocation logic
     * by providing allocate_raw and deallocate_raw methods.
     */
    template<typename Derived>
    class Allocator
    {
#pragma region Methods

    public:
        /**
         * @brief Allocates and constructs an object of type T with the given arguments.
         * @tparam T The type of the object to construct.
         * @param args The constructor arguments for the object.
         * @return A pointer to the newly constructed object.
         */
        template <typename T, typename... Args>
        T *construct(Args &&...args)
        {
            Any const ptr = allocate_impl(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Allocates and constructs an array of type T with the given arguments.
         * @tparam T The type of the objects to construct.
         * @param count The number of objects to construct.
         * @param args The constructor arguments for the objects.
         * @return A pointer to the first element of the newly constructed array.
         */
        template <typename T, typename... Args>
        T *construct_array(Size const count, Args &&...args)
        {      
            Any const ptr = allocate_impl(sizeof(T) * count);
            if (ptr == nullptr)
            {
                return nullptr;
            }
            T *array = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&array[i]) T(std::forward<Args>(args)...);
            }
            return array;
        }

        /**
         * @brief Destructs and deallocates an object of type T.
         * @tparam T The type of the object to destruct.
         * @param object A pointer to the object to destruct and deallocate.
         */
        template<typename T>
        void destruct(T *const object)
        {
            if (object == nullptr)
            {
                return;
            }

            object->~T();
            deallocate_impl(static_cast<Any>(object));
        }

        /**
         * @brief Destructs and deallocates an array of type T.
         * @tparam T The type of the objects to destruct.
         * @param array A pointer to the first element of the array to destruct and deallocate.
         * @param count The number of elements in the array.
         */
        template<typename T>
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
            deallocate_impl(static_cast<Any>(array));
        }

    protected:
        Any allocate_impl(Size const size)
        {
            MINTY_ASSERT(size > 0, ErrorCode::Memory_UnallowedSize);

            auto* const derived = static_cast<Derived *>(this);
            Any const ptr = derived->allocate_raw(size);
            if (ptr == nullptr)
            {
                return nullptr;
            }
            return ptr;
        }

        void deallocate_impl(Any const ptr) noexcept
        {
            auto* const derived = static_cast<Derived *>(this);
            derived->deallocate_raw(ptr);
        }

#pragma endregion
    };
}

#endif // MINTY_MEMORY_ALLOCATOR_H