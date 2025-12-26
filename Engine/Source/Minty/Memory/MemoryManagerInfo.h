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
    struct MemoryStackInfo;
    struct MemoryPoolInfo;

    /**
     * @brief Structure containing information for initializing a MemoryManager.
     */
	struct MemoryManagerInfo
	{
        /** 
         * @brief Information for the temporary memory stack.
         */
		MemoryStackInfo* frameStackInfo = nullptr;

        /**
         * @brief Information for the persistent memory pools.
         */
		MemoryPoolInfo* persistentPoolInfos = nullptr;

        /**
         * @brief The number of persistent memory pools to create.
         */
        Size persistentPoolInfoCount = 0;
	};
}

#endif // MINTY_MEMORY_MEMORYMANAGERINFO_H