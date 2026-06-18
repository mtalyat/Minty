#include "PersistentAllocator.h"
#include "Core/Debug/DebugF.h"
#include "Core/Tool/Memory.h"
#include "MemoryPoolInfo.h"

using namespace Minty;

void Minty::PersistentAllocator::reset()
{
    // do nothing if not initialized
    if (sp_memoryPools != nullptr)
    {
        for (Size i = 0; i < s_memoryPoolCount; ++i)
        {
            sp_memoryPools[i].reset();
        }
    }
}

void Minty::PersistentAllocator::initialize(MemoryPoolInfo const *infos, Size const count)
{
    MINTY_ASSERT(count > 0, ErrorCodeEnum::Argument_ExpectedAboveZero);

    s_memoryPoolCount = count;
    sp_memoryPools = static_cast<MemoryPool *>(::operator new(sizeof(MemoryPool) * count));

    Size lastSize = 0;
    for (Size i = 0; i < count; ++i)
    {
        MINTY_ASSERT_B(infos[i].blockSize > lastSize, ErrorCodeEnum::Memory_SizeMismatch, infos[i].blockSize, lastSize);
        new (&sp_memoryPools[i]) MemoryPool(infos[i]);
        lastSize = infos[i].blockSize;
    }

    // Determine the maximum size and create the pool map
    s_maxSize = infos[count - 1].blockSize;
    spp_memoryPoolMap = static_cast<MemoryPool **>(::operator new(sizeof(MemoryPool *) * (s_maxSize + 1)));
    Size poolIndex = 0;
    for (Size i = 0; i <= s_maxSize; ++i)
    {
        Size blockSize = infos[poolIndex].blockSize;
        if (i > blockSize && poolIndex < count - 1)
        {
            ++poolIndex;
            blockSize = infos[poolIndex].blockSize;
        }
        new (&spp_memoryPoolMap[i]) MemoryPool *(sp_memoryPools + poolIndex);
    }
}

void Minty::PersistentAllocator::dispose()
{
    if (sp_memoryPools == nullptr || spp_memoryPoolMap == nullptr)
    {
        return;
    }
    for (Size i = 0; i < s_memoryPoolCount; ++i)
    {
        MINTY_CHECK_A(sp_memoryPools[i].get_count() == 0, ErrorCodeEnum::Memory_WeakLeakDetected, sp_memoryPools[i].get_count() * sp_memoryPools[i].get_block_size());
        sp_memoryPools[i].~MemoryPool();
    }
    ::operator delete(sp_memoryPools);
    ::operator delete(spp_memoryPoolMap);
    sp_memoryPools = nullptr;
    spp_memoryPoolMap = nullptr;
    s_memoryPoolCount = 0;
    s_maxSize = 0;
}

Pointer Minty::PersistentAllocator::allocate_raw(Size const size)
{
    MINTY_ASSERT(sp_memoryPools != nullptr, ErrorCodeEnum::Memory_AllocatorNotInitialized);
    MINTY_ASSERT(size <= s_maxSize, ErrorCodeEnum::Memory_UnallowedSize);

    MemoryPool &pool = *spp_memoryPoolMap[size];
    Pointer const ptr = pool.allocate();
    return ptr;
}

void Minty::PersistentAllocator::deallocate_raw(Pointer const ptr) noexcept
{
    if (ptr == nullptr || sp_memoryPools == nullptr)
    {
        return;
    }

    // Find which pool this allocation belongs to
    Size const size = Tool::get_block_size(ptr);
    MemoryPool &pool = *spp_memoryPoolMap[size];
    pool.deallocate(ptr);
}