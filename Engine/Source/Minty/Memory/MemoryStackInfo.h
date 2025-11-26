#ifndef MINTY_MEMORY_MEMORYSTACKINFO_H
#define MINTY_MEMORY_MEMORYSTACKINFO_H

/**
 * @file MemoryStackInfo.h
 * @brief Header file for MemoryStackInfo structure.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief Arguments for creating a MemoryStack.
     */
	struct MemoryStackInfo
	{
        /**
         * @brief The capacity of the memory stack in Bytes.
         */
		Size capacity = 0;

        /**
         * @brief The alignment for allocations in the memory stack.
         */
        Size alignment = 0;
	};
}

#endif // MINTY_MEMORY_MEMORYSTACKINFO_H