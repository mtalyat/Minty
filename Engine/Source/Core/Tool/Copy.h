#pragma once

/**
 * @file Copy.h
 * @brief Header file for memory copy utilities.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"

namespace Minty::Tool
{
    /**
     * @brief Copies a block of memory from the source to the destination.
     * @param source A pointer to the source memory block.
     * @param destination A pointer to the destination memory block.
     * @param size The number of bytes to copy.
     */
    inline void copy(PointerConst const source, Pointer const destination, Size const size)
    {
        if (source == nullptr || destination == nullptr || size == 0)
        {
            return;
        }

        std::memcpy(destination, source, size);
    }

    /**
     * @brief Performs a shallow copy of objects from the source to the destination.
     * @tparam T The type of the objects to copy.
     * @param source A pointer to the first element of the source array.
     * @param destination A pointer to the first element of the destination array.
     * @param count The number of elements to copy.
     */
    template<typename T>
    inline void shallow_copy(T const* const source, T *const destination, Size const count = 1)
    {
        if (source == nullptr || destination == nullptr || count == 0)
        {
            return;
        }

        std::memcpy(destination, source, count * sizeof(T));
    }

    /**
     * @brief Performs a deep copy of objects from the source to the destination.
     * @tparam T The type of the objects to copy. Must be copy-assignable.
     * @param source A pointer to the first element of the source array.
     * @param destination A pointer to the first element of the destination array.
     * @param count The number of elements to copy.
     */
    template<typename T>
    void deep_copy(T const* const source, T *const destination, Size const count = 1)
    {
        if (source == nullptr || destination == nullptr || count == 0)
        {
            return;
        }

        for (Size i = 0; i < count; ++i)
        {
            destination[i] = source[i];
        }
    }
}