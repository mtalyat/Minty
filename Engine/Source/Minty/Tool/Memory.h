#ifndef MINTY_TOOL_MEMORY_H
#define MINTY_TOOL_MEMORY_H

/**
 * @file Memory.h
 * @brief Header file for memory management utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty::Tool
{
    /**
     * @brief Creates a block pointer with a size header.
     * @param ptr The original pointer to the memory block.
     * @param size The size of the memory block.
     */
    Any create_block_ptr(Any const ptr, Size const size);

    /**
     * @brief Retrieves the original block pointer from a block pointer with a size header.
     * @param ptr The block pointer with a size header.
     * @return The original block pointer.
     */
    Any get_block_ptr(Any const ptr);

    /**
     * @brief Extracts the size of the memory block from a block pointer with a size header.
     * @param ptr The block pointer with a size header.
     * @return The size of the memory block.
     */
    Size get_block_size(Any const ptr);
}

#endif // MINTY_TOOL_MEMORY_H