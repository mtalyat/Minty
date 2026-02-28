#ifndef MINTY_MEMORY_DEFAULTALLOCATOR_H
#define MINTY_MEMORY_DEFAULTALLOCATOR_H

/**
 * @file DefaultAllocator.h
 * @brief Header file for the DefaultAllocator class.
 * @author Mitchell Talyat
 */

#ifdef MINTY_DEBUG
#include "Minty/Memory/DebugAllocator.h"
#else
#include "Minty/Memory/HeapAllocator.h"
#endif // MINTY_DEBUG

namespace Minty
{
#ifdef MINTY_DEBUG
    using DefaultAllocator = DebugAllocator;
#else
    using DefaultAllocator = HeapAllocator;
#endif // MINTY_DEBUG
}

#endif // MINTY_MEMORY_DEFAULTALLOCATOR_H