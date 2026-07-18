#pragma once

/**
 * @file PersistentAllocator.h
 * @brief Header file for the PersistentAllocator class.
 * @author Mitchell Talyat
 */

#include "Allocator.hpp"
#include "MemoryPool.hpp"

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
         * @brief Resets all memory pools, making all blocks available again.
         * WARNING: This invalidates all pointers allocated from this allocator.
         */
        static void reset();

        /**
         * @brief Initializes the persistent allocator with multiple memory pools of different sizes.
         * @param infos Array of MemoryPoolInfo structures defining pool configurations.
         * @param count Number of pools to create.
         */
        static void initialize(MemoryPoolInfo const *infos, Size const count);

        /**
         * @brief Disposes of all memory pools and resets the allocator.
         */
        static void dispose();

    private:
        Pointer allocate_raw(Size const size);

        void deallocate_raw(Pointer const ptr) noexcept;

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