#ifndef MINTY_MEMORY_MEMORYMANAGERINFO_H
#define MINTY_MEMORY_MEMORYMANAGERINFO_H

/**
 * @file MemoryManagerInfo.h
 * @brief Header file for MemoryManagerInfo structure.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief Arguments for creating a MemoryPool.
     */
	struct MemoryPoolInfo
	{
        /**
         * @brief The size of each block in Bytes.
         */
		Size blockSize = 0;

        /**
         * @brief The number of blocks in the pool.
         */
		Size blockCount = 0;
	};
}

#endif // MINTY_MEMORY_MEMORYMANAGERINFO_H