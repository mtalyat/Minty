#pragma once

/**
 * @file DebugAllocator.h
 * @brief Header file for the DebugAllocator class.
 * @author Mitchell Talyat
 */

#include "Allocator.hpp"
#include "Core/Tool/Memory.hpp"

namespace Minty
{
#ifdef MINTY_DEBUG
    /**
     * @brief A debug allocator that uses the global new and delete operators.
     */
    class DebugAllocator
        : public Allocator<DebugAllocator>
    {
        friend class Allocator<DebugAllocator>;

#pragma region Constructors

    public:
        DebugAllocator();

        DebugAllocator(DebugAllocator const &other) noexcept;

        DebugAllocator(DebugAllocator &&other) noexcept;

        ~DebugAllocator();

#pragma endregion

#pragma region Operators

    public:
        DebugAllocator &operator=(DebugAllocator const &other) noexcept;

        DebugAllocator &operator=(DebugAllocator &&other) noexcept;

#pragma endregion

#pragma region Methods

    public:        
        /**
         * @brief Initializes the DebugAllocator.
         */
        static void initialize();

        /**
         * @brief Disposes the DebugAllocator.
         */
        static void dispose();

    private:
        Pointer allocate_raw(Size const size);

        void deallocate_raw(Pointer const ptr) noexcept;

#pragma endregion

#pragma region Variables

    private:
        Size m_localAllocated;

#pragma endregion
    };
#endif // MINTY_DEBUG
}