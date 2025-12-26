#ifndef MINTY_MEMORY_DEFAULTALLOCATOR_H
#define MINTY_MEMORY_DEFAULTALLOCATOR_H

/**
 * @file DefaultAllocator.h
 * @brief Header file for the DefaultAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
    /**
     * @struct DefaultAllocatorBase
     * @brief Base class for DefaultAllocator to hold static variables.
     */
    struct DefaultAllocatorBase
    {
#pragma region Methods

    public:
        /**
         * @brief Initializes the DefaultAllocator.
         */
        static void initialize()
        {
            MINTY_ASSERT(!s_initialized, ErrorCode::Memory_AllocatorAlreadyInitialized);
            s_initialized = true;
            s_totalAllocated = 0;
        }

        /**
         * @brief Disposes the DefaultAllocator.
         */
        static void dispose()
        {
            MINTY_ASSERT(s_initialized, ErrorCode::Memory_AllocatorNotInitialized);
            s_initialized = false;
            MINTY_CHECK_F(s_totalAllocated == 0, ErrorCode::Memory_StrongLeakDetected, s_totalAllocated);
            s_totalAllocated = 0;
        }

#pragma endregion

#pragma region Variables

    protected:
        inline static Size s_totalAllocated = 0;
        inline static Bool s_initialized = false;

#pragma endregion
    };

    /**
     * @brief A default allocator that uses the global new and delete operators.
     * @tparam T The type to allocate.
     */
    template <typename T>
    struct DefaultAllocator
        : public DefaultAllocatorBase
    {
#pragma region Types

    public:
        using value_type = T;

#pragma endregion

#pragma region Constructors

    public:
        DefaultAllocator() = default;
        template <class U>
        DefaultAllocator(const DefaultAllocator<U> &) noexcept {}

#pragma endregion

#pragma region Methods

    public:
        T *allocate(Size const count)
        {
            Any const ptr = ::operator new(count * sizeof(T));
            if (s_initialized)
            {
                s_totalAllocated += count * sizeof(T);
            }
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
            T *const array = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&array[i]) T();
            }
            return array;
        }

        void deallocate(T *const ptr, Size const count) noexcept
        {
            if (ptr == nullptr)
            {
                return;
            }

            if (s_initialized)
            {
                MINTY_ASSERT(s_totalAllocated >= count * sizeof(T), ErrorCode::Memory_DeallocationFailed);
                s_totalAllocated -= count * sizeof(T);
            }
            ::operator delete(static_cast<Any>(ptr));
        }

        void deallocate(T *const ptr) noexcept
        {
            return deallocate(ptr, 1);
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

#endif // MINTY_MEMORY_DEFAULTALLOCATOR_H