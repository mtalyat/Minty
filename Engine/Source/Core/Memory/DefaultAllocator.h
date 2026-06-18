#pragma once

/**
 * @file DefaultAllocator.h
 * @brief Header file for the DefaultAllocator class.
 * @author Mitchell Talyat
 */

#ifdef MINTY_DEBUG
#include "DebugAllocator.h"
#else
#include "HeapAllocator.h"
#endif // MINTY_DEBUG

namespace Minty
{
#ifdef MINTY_DEBUG
    using DefaultAllocator = DebugAllocator;
#else
    using DefaultAllocator = HeapAllocator;
#endif // MINTY_DEBUG
}