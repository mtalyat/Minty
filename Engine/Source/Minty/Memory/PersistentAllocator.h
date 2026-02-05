#ifndef MINTY_MEMORY_PERSISTENTALLOCATOR_H
#define MINTY_MEMORY_PERSISTENTALLOCATOR_H

/**
 * @file PersistentAllocator.h
 * @brief Header file for the PersistentAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"

namespace Minty
{
    struct PersistentAllocatorBase
    {
#pragma region Methods

    public:
        /**
         * @brief Resets all memory pools, making all blocks available again.
         * WARNING: This invalidates all pointers allocated from this allocator.
         */
        static void reset()
        {
            // do nothing if not initialized
            if (sp_memoryPools != nullptr)
            {
                for (Size i = 0; i < s_memoryPoolCount; ++i)
                {
                    sp_memoryPools[i].reset();
                }
            }
        }

        /**
         * @brief Initializes the persistent allocator with multiple memory pools of different sizes.
         * @param infos Array of MemoryPoolInfo structures defining pool configurations.
         * @param count Number of pools to create.
         */
        static void initialize(MemoryPoolInfo const *infos, Size const count)
        {
            MINTY_ASSERT(count > 0, ErrorCode::Argument_ExpectedAboveZero);

            s_memoryPoolCount = count;
            sp_memoryPools = static_cast<MemoryPool *>(::operator new(sizeof(MemoryPool) * count));

            Size lastSize = 0;
            for (Size i = 0; i < count; ++i)
            {
                MINTY_ASSERT_F(infos[i].blockSize > lastSize, ErrorCode::Memory_SizeMismatch, infos[i].blockSize, lastSize);
                new (&sp_memoryPools[i]) MemoryPool(infos[i]);
                lastSize = infos[i].blockSize;
            }

            // Determine the maximum size and create the pool map
            s_maxSize = infos[count - 1].blockSize;
            spp_memoryPoolMap = static_cast<MemoryPool **>(::operator new(sizeof(MemoryPool *) * (s_maxSize + 1)));
            Size poolIndex = 0;
            for (Size i = 0; i <= s_maxSize; ++i)
            {
                Size blockSize = infos[poolIndex].blockSize;
                if (i > blockSize && poolIndex < count - 1)
                {
                    ++poolIndex;
                    blockSize = infos[poolIndex].blockSize;
                }
                new (&spp_memoryPoolMap[i]) MemoryPool *(sp_memoryPools + poolIndex);
            }
        }

        /**
         * @brief Disposes of all memory pools and resets the allocator.
         */
        static void dispose()
        {
            if (sp_memoryPools == nullptr || spp_memoryPoolMap == nullptr)
            {
                return;
            }
            for (Size i = 0; i < s_memoryPoolCount; ++i)
            {
                MINTY_CHECK_F(sp_memoryPools[i].get_count() == 0, ErrorCode::Memory_WeakLeakDetected, sp_memoryPools[i].get_count() * sp_memoryPools[i].get_block_size());
                sp_memoryPools[i].~MemoryPool();
            }
            ::operator delete(sp_memoryPools);
            ::operator delete(spp_memoryPoolMap);
            sp_memoryPools = nullptr;
            spp_memoryPoolMap = nullptr;
            s_memoryPoolCount = 0;
            s_maxSize = 0;
        }

#pragma endregion

#pragma region Variables

    protected:
        inline static MemoryPool *sp_memoryPools = nullptr;
        inline static MemoryPool **spp_memoryPoolMap = nullptr;
        inline static Size s_memoryPoolCount = 0;
        inline static Size s_maxSize = 0;

#pragma endregion
    };

    /**
     * @brief A persistent allocator that allocates from multiple memory pools.
     * @tparam T The type to allocate.
     */
    template <typename T>
    struct PersistentAllocator
        : public PersistentAllocatorBase
    {
#pragma region Types

    public:
        using value_type = T;

#pragma endregion

#pragma region Constructors

    public:
        PersistentAllocator() = default;
        template <class U>
        PersistentAllocator(const PersistentAllocator<U> &) noexcept {}

#pragma endregion

#pragma region Methods

    public:
        T *allocate(Size const count)
        {
            MINTY_ASSERT(sp_memoryPools != nullptr, ErrorCode::Memory_AllocatorNotInitialized);
            MINTY_ASSERT(count > 0 && count * sizeof(T) <= s_maxSize, ErrorCode::Memory_UnallowedSize);

            Size const size = count * sizeof(T);
            MemoryPool &pool = *spp_memoryPoolMap[size];
            Any const ptr = pool.allocate();
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
            return array;
        }

        void deallocate(T *const ptr, Size const count) noexcept
        {
            if (ptr == nullptr || sp_memoryPools == nullptr)
            {
                return;
            }

            // Find which pool this allocation belongs to
            Size const size = count * sizeof(T);
            MemoryPool &pool = *spp_memoryPoolMap[size];
            pool.deallocate(static_cast<Any>(ptr));
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

#endif // MINTY_MEMORY_PERSISTENTALLOCATOR_H