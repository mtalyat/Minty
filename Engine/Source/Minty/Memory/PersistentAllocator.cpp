#include "PersistentAllocator.h"
#include "Minty/Memory/MemoryPool.h"

using namespace Minty;

MemoryPool* PersistentAllocator<PERSISTENT_ALLOCATOR_MIN>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<16>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<32>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<64>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<128>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<256>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<512>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<1024>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<2048>::s_memoryPool = nullptr;
MemoryPool* PersistentAllocator<PERSISTENT_ALLOCATOR_MAX>::s_memoryPool = nullptr;