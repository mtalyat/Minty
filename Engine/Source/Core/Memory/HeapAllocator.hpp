#pragma once

/**
 * @file HeapAllocator.hpp
 * @brief Header file for the HeapAllocator class.
 * @author Mitchell Talyat
 */

#include "Allocator.hpp"

namespace Minty
{
    /**
     * @brief A heap allocator that uses the global new and delete operators.
     */
    class HeapAllocator
        : public Allocator<HeapAllocator>
    {
        friend class Allocator<HeapAllocator>;

#pragma region Methods

    public:
        /**
         * @brief Initializes the HeapAllocator.
         */
        static void initialize();

        /**
         * @brief Disposes the HeapAllocator.
         */
        static void dispose();

    private:
        Pointer allocate_raw(Size const size);

        void deallocate_raw(Pointer const ptr) noexcept;

#pragma endregion

#pragma region Variables

    protected:
#ifdef MINTY_DEBUG
        inline static Size s_globalAllocated = 0;
#endif // MINTY_DEBUG

#pragma endregion
    };
}