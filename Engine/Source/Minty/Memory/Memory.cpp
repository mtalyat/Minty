#include "Memory.h"
#include "Minty/Memory/MemoryManager.h"

using namespace Minty;

Any Minty::Memory::Allocate(Allocator const allocator, Size const size)
{
    return MemoryManager::get_singleton().allocate()
}