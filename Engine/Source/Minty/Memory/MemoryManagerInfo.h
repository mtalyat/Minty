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
		MemoryStackInfo* temporaryStackInfo = nullptr;

        /**
         * @brief Information for the task memory stacks.
         */
		MemoryStackInfo* taskStackInfo = nullptr;

        /**
         * @brief The number of task memory stacks to create.
         */
		Size taskStackCount = 0;

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