#pragma once

/**
 * @file Memory.hpp
 * @brief Header file for memory management utilities.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty::Tool
{
    /**
     * @brief Creates a block pointer with a size header.
     * @param ptr The original pointer to the memory block.
     * @param size The size of the memory block.
     */
    Pointer create_block_ptr(Pointer const ptr, Size const size);

    /**
     * @brief Retrieves the original block pointer from a block pointer with a size header.
     * @param ptr The block pointer with a size header.
     * @return The original block pointer.
     */
    Pointer get_block_ptr(Pointer const ptr);

    /**
     * @brief Extracts the size of the memory block from a block pointer with a size header.
     * @param ptr The block pointer with a size header.
     * @return The size of the memory block.
     */
    Size get_block_size(Pointer const ptr);
}