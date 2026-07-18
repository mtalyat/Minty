#pragma once

/**
 * @file MemoryStackInfo.h
 * @brief Header file for MemoryStackInfo structure.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

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