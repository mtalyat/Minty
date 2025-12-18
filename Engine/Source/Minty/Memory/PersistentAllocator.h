#ifndef MINTY_MEMORY_PERSISTENTALLOCATOR_H
#define MINTY_MEMORY_PERSISTENTALLOCATOR_H

/**
 * @file PersistentAllocator.h
 * @brief Header file for the PersistentAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"

namespace Minty
{
    constexpr Size PERSISTENT_ALLOCATOR_MIN = 8;
    constexpr Size PERSISTENT_ALLOCATOR_MAX = 4096;

    /**
     * @class PersistentAllocator
     * @brief Static class providing memory allocation and deallocation using the persistent allocator.
     */
    template<Size N>
    class PersistentAllocator
    {
        static_assert((N & (N - 1)) == 0 && N >= PERSISTENT_ALLOCATOR_MIN && N <= PERSISTENT_ALLOCATOR_MAX, "N must be a power of 2, between PERSISTENT_ALLOCATOR_MIN and PERSISTENT_ALLOCATOR_MAX inclusive.");

#pragma region Constructors

    public:
        PersistentAllocator() = delete;
        ~PersistentAllocator() = delete;

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Initialize the persistent allocator with the specified information.
         * @param info The MemoryPoolInfo containing initialization parameters.
         */
        static void initialize(MemoryPoolInfo const& info)
        {
            MINTY_ASSERT(s_memoryPool == nullptr, ErrorCode::Object_AlreadyInitialized);
            MINTY_ASSERT(info.blockSize == N, ErrorCode::Memory_SizeMismatch);

            s_memoryPool = new MemoryPool(info);
        }

        /**
         * @brief Shutdown the persistent allocator, freeing all allocated memory.
         */
        static void shutdown()
        {
            MINTY_ASSERT(s_memoryPool != nullptr, ErrorCode::Object_NotInitialized);

            delete s_memoryPool;
        }

        /**
         * @brief Allocate memory using the persistent allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any allocate()
        {
            MINTY_ASSERT(s_memoryPool != nullptr, ErrorCode::Object_NotInitialized);

            return s_memoryPool->allocate();
        }

        /**
         * @brief Deallocate memory using the persistent allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void deallocate(Any const ptr)
        {
            MINTY_ASSERT(s_memoryPool != nullptr, ErrorCode::Object_NotInitialized);

            s_memoryPool->deallocate(ptr);
        }

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
        static MemoryPool* s_memoryPool;

#pragma endregion
    };
}

#endif // MINTY_MEMORY_PERSISTENTALLOCATOR_H