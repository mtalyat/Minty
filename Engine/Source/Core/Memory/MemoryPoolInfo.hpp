#pragma once

/**
 * @file MemoryManagerInfo.h
 * @brief Header file for MemoryManagerInfo structure.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

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