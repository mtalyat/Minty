#include "Init.h"
#include "Minty/Memory/DebugAllocator.h"
#include "Minty/Memory/HeapAllocator.h"

void Minty::initialize(MintyInfo const &info)
{
    // initialize memory
    HeapAllocator::initialize();
#ifdef MINTY_DEBUG
	DebugAllocator::initialize();
#endif // MINTY_DEBUG

    // initialize debug flags
    Debug::initialize(info.debugFlags);
}

void Minty::dispose()
{
    // dispose of debug
    Debug::dispose();
    
    // dispose of memory
#ifdef MINTY_DEBUG
    DebugAllocator::dispose();
#endif // MINTY_DEBUG
    HeapAllocator::dispose();
}
