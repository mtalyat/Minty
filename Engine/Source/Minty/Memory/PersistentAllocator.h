#ifndef MINTY_MEMORY_PERSISTENTALLOCATOR_H
#define MINTY_MEMORY_PERSISTENTALLOCATOR_H

/**
 * @file PersistentAllocator.h
 * @brief Header file for the PersistentAllocator class.
 * @author Mitchell Talyat
 */

#include "Minty/Memory/Allocator.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"

namespace Minty
{
    /**
     * @brief A default allocator that uses the global new and delete operators.
     */
    class PersistentAllocator
        : public Allocator<PersistentAllocator>
    {
        friend class Allocator<PersistentAllocator>;

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

    private:
        Any allocate_raw(Size const size)
        {
            MINTY_ASSERT(sp_memoryPools != nullptr, ErrorCode::Memory_AllocatorNotInitialized);
            MINTY_ASSERT(size <= s_maxSize, ErrorCode::Memory_UnallowedSize);

            MemoryPool &pool = *spp_memoryPoolMap[size];
            Any const ptr = pool.allocate();
            return ptr;
        };

        void deallocate_raw(Any const ptr) noexcept
        {
            if (ptr == nullptr || sp_memoryPools == nullptr)
            {
                return;
            }

            // Find which pool this allocation belongs to
            Size const size = Tool::get_block_size(ptr);
            MemoryPool &pool = *spp_memoryPoolMap[size];
            pool.deallocate(ptr);
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
}

#endif // MINTY_MEMORY_PERSISTENTALLOCATOR_H