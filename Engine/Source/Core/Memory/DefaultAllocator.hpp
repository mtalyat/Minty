#pragma once

/**
 * @file DefaultAllocator.hpp
 * @brief Header file for the DefaultAllocator class.
 * @author Mitchell Talyat
 */

#ifdef MINTY_DEBUG
#include "DebugAllocator.hpp"
#else
#include "HeapAllocator.hpp"
#endif // MINTY_DEBUG

namespace Minty
{
#ifdef MINTY_DEBUG
    using DefaultAllocator = DebugAllocator;
#else
    using DefaultAllocator = HeapAllocator;
#endif // MINTY_DEBUG
}