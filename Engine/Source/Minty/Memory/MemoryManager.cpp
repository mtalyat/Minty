#include "pch.h"
#include "MemoryManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Memory/MemoryManagerInfo.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"
#ifdef MINTY_DEBUG
#include <unordered_map>
#endif // MINTY_DEBUG

using namespace Minty;

#ifdef MINTY_DEBUG
static std::unordered_map<Any, Size> gs_dynamicAllocationSizes_DEBUG;
#endif // MINTY_DEBUG

template <typename T, typename... Args>
static T *create_array(Size const count, Args &&...args)
{
	T *const ptr = static_cast<T *>(std::malloc(sizeof(T) * count));
	MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed);
	if constexpr (sizeof...(args) != 0)
	{
		for (Size i = 0; i < count; ++i)
		{
			new (ptr + i) T(std::forward<Args>(args)...);
		}
	}
	return ptr;
}

template <typename T>
static void destroy_array(T *const ptr, Size const count)
{
	if (ptr)
	{
		for (Size i = 0; i < count; ++i)
		{
			ptr[i].~T();
		}
		std::free(ptr);
	}
}

Minty::MemoryManager::MemoryManager(MemoryManagerInfo const &info)
	: Manager(), m_staticSize_DEBUG(0), m_dynamicSize_DEBUG(0), mp_temporaryStack(nullptr), mp_taskStacks(nullptr), m_taskStackCount(0), m_taskIndex(0), mp_persistentPools(nullptr), m_persistentPoolCount(0), mp_persistentPoolSizeMap(nullptr)
{
	if (info.temporaryStackInfo)
	{
		mp_temporaryStack = create_array<MemoryStack>(1, *info.temporaryStackInfo);
	}

	if (info.taskStackInfo)
	{
		MINTY_ASSERT(info.taskStackCount > 0, ErrorCode::Argument_ExpectedNonZero);
		mp_taskStacks = create_array<MemoryStack>(info.taskStackCount, *info.taskStackInfo);
		m_taskStackCount = info.taskStackCount;
	}

	if (info.persistentPoolInfos)
	{
		MINTY_ASSERT(info.persistentPoolInfoCount > 0, ErrorCode::Argument_ExpectedNonZero);

#ifdef MINTY_DEBUG
		Size lastSize = 0;
#endif // MINTY_DEBUG

		mp_persistentPools = create_array<MemoryPool>(info.persistentPoolInfoCount);
		for (Size i = 0; i < info.persistentPoolInfoCount; ++i)
		{
#ifdef MINTY_DEBUG
			MINTY_ASSERT(info.persistentPoolInfos[i].blockSize > lastSize, ErrorCode::Argument_IncorrectOrder);
			lastSize = info.persistentPoolInfos[i].blockSize;
#endif // MINTY_DEBUG

			new (mp_persistentPools + i) MemoryPool(info.persistentPoolInfos[i]);
		}
		m_persistentPoolCount = info.persistentPoolInfoCount;

		// Create size map for quick lookup
		Size maxBlockSize = mp_persistentPools[m_persistentPoolCount - 1].get_block_size();
		mp_persistentPoolSizeMap = new Size[maxBlockSize + 1];
		Size poolIndex = 0;
		for (Size size = 0; size <= maxBlockSize; size++)
		{
			while (poolIndex < m_persistentPoolCount - 1 &&
				   size > mp_persistentPools[poolIndex].get_block_size())
			{
				poolIndex++;
			}
			mp_persistentPoolSizeMap[size] = poolIndex;
		}
	}
}

Minty::MemoryManager::~MemoryManager()
{
	MINTY_ASSERT(m_staticSize_DEBUG == 0, ErrorCode::Memory_WeakLeakDetected);
	MINTY_ASSERT(m_dynamicSize_DEBUG == 0, ErrorCode::Memory_StrongLeakDetected);

	if (mp_temporaryStack)
	{
		destroy_array(mp_temporaryStack, 1);
	}

	if (mp_taskStacks)
	{
		destroy_array(mp_taskStacks, m_taskStackCount);
	}

	if (mp_persistentPools)
	{
		destroy_array(mp_persistentPools, m_persistentPoolCount);
		delete[] mp_persistentPoolSizeMap;
	}
}

void Minty::MemoryManager::frame_update(Timestep const &time)
{
	MINTY_TRACE_SCOPE();

	// free memory of single frame allocator
	if (mp_temporaryStack)
	{
#ifdef MINTY_DEBUG
		m_staticSize_DEBUG -= mp_temporaryStack->get_size();
#endif // MINTY_DEBUG
		mp_temporaryStack->reset();
	}

	// move to next task
	if (mp_taskStacks)
	{
		m_taskIndex = (m_taskIndex + 1) % mp_taskStacks->get_size();

		// free all of its remaining memory for reuse
#ifdef MINTY_DEBUG
		m_staticSize_DEBUG -= mp_taskStacks[m_taskIndex].get_size();
#endif // MINTY_DEBUG
		mp_taskStacks[m_taskIndex].reset();
	}
}

Any Minty::MemoryManager::allocate(Allocator const allocator, Size const size)
{
	static Any (MemoryManager::*allocateFunctions[])(Size const) = {
		&MemoryManager::allocate_default,
		&MemoryManager::allocate_temporary,
		&MemoryManager::allocate_task,
		&MemoryManager::allocate_persistent};

	return (this->*allocateFunctions[static_cast<Size>(allocator)])(size);
}

Any Minty::MemoryManager::allocate_default(Size const size)
{
#ifdef MINTY_DEBUG
	m_dynamicSize_DEBUG += size;
#endif // MINTY_DEBUG
	Any const ptr = std::malloc(size);
#ifdef MINTY_DEBUG
	MINTY_ASSERT(gs_dynamicAllocationSizes_DEBUG.find(ptr) == gs_dynamicAllocationSizes_DEBUG.end(), ErrorCode::Memory_AllocationFailed);
	gs_dynamicAllocationSizes_DEBUG.emplace(ptr, size);
#endif // MINTY_DEBUG
}

Any Minty::MemoryManager::allocate_temporary(Size const size)
{
	MINTY_ASSERT(mp_temporaryStack != nullptr, ErrorCode::Memory_AllocatorNotInitialized);

	Any const ptr = mp_temporaryStack->allocate(size);

#ifdef MINTY_DEBUG
	m_staticSize_DEBUG += size;
#endif // MINTY_DEBUG

	return ptr;
}

Any Minty::MemoryManager::allocate_task(Size const size)
{
	MINTY_ASSERT(mp_taskStacks != nullptr, ErrorCode::Memory_AllocatorNotInitialized);

	Any const ptr = mp_taskStacks[m_taskIndex].allocate(size);

#ifdef MINTY_DEBUG
	m_staticSize_DEBUG += size;
#endif // MINTY_DEBUG

	return ptr;
}

Any Minty::MemoryManager::allocate_persistent(Size const size)
{
	MINTY_ASSERT(mp_persistentPools != nullptr, ErrorCode::Memory_AllocatorNotInitialized);

	Size const poolIndex = get_persistent_index(size);

	if (poolIndex == SIZE_MAX)
	{
		// size too large for any pool
		return nullptr;
	}

	Any const ptr = mp_persistentPools[poolIndex].allocate();

#ifdef MINTY_DEBUG
	m_staticSize_DEBUG += mp_persistentPools[poolIndex].get_block_size();
#endif // MINTY_DEBUG

	return ptr;
}

void Minty::MemoryManager::deallocate(Allocator const allocator, Any const ptr)
{
	static void (MemoryManager::*s_deallocateFunctions[])(Any) = {
		&MemoryManager::deallocate_default,
		&MemoryManager::deallocate_temporary,
		&MemoryManager::deallocate_task,
		&MemoryManager::deallocate_persistent};

	(this->*s_deallocateFunctions[static_cast<Size>(allocator)])(ptr);
}

void Minty::MemoryManager::deallocate_default(Any const ptr)
{
#ifdef MINTY_DEBUG
	auto it = gs_dynamicAllocationSizes_DEBUG.find(ptr);
	MINTY_ASSERT(it != gs_dynamicAllocationSizes_DEBUG.end(), ErrorCode::Memory_DeallocationFailed);
	if (it != gs_dynamicAllocationSizes_DEBUG.end())
	{
		m_dynamicSize_DEBUG -= it->second;
		gs_dynamicAllocationSizes_DEBUG.erase(it);
	}
#endif // MINTY_DEBUG
	std::free(ptr);
}

void Minty::MemoryManager::deallocate_temporary(Any const ptr)
{
	MINTY_ASSERT(mp_temporaryStack != nullptr, ErrorCode::Memory_AllocatorNotInitialized);

#ifdef MINTY_DEBUG
	Size const previousSize = mp_temporaryStack->get_size();
#endif // MINTY_DEBUG

	mp_temporaryStack->deallocate(ptr);

#ifdef MINTY_DEBUG
	Size const ptrSize = previousSize - mp_temporaryStack->get_size();
	MINTY_ASSERT(m_staticSize_DEBUG >= ptrSize, ErrorCode::Memory_DeallocationFailed);
	m_staticSize_DEBUG -= ptrSize;
#endif // MINTY_DEBUG
}

void Minty::MemoryManager::deallocate_task(Any const ptr)
{
	MINTY_ASSERT(mp_taskStacks != nullptr, ErrorCode::Memory_AllocatorNotInitialized);

#ifdef MINTY_DEBUG
	Size const previousSize = mp_taskStacks[m_taskIndex].get_size();
#endif // MINTY_DEBUG

	mp_taskStacks[m_taskIndex].deallocate(ptr);

#ifdef MINTY_DEBUG
	Size const ptrSize = previousSize - mp_taskStacks[m_taskIndex].get_size();
	MINTY_ASSERT(m_staticSize_DEBUG >= ptrSize, ErrorCode::Memory_DeallocationFailed);
	m_staticSize_DEBUG -= ptrSize;
#endif // MINTY_DEBUG
}

void Minty::MemoryManager::deallocate_persistent(Any const ptr)
{
	MINTY_ASSERT(mp_persistentPools != nullptr, ErrorCode::Memory_AllocatorNotInitialized);

	// Retrieve block size stored before pointer
	Size const externalSize = MemoryPool::extract_size(ptr);
	Size const poolIndex = get_persistent_index(externalSize);

	MINTY_ASSERT(poolIndex != SIZE_MAX, ErrorCode::Memory_AllocatorMismatch);

	mp_persistentPools[poolIndex].deallocate(ptr);

#ifdef MINTY_DEBUG
	Size const blockSize = mp_persistentPools[poolIndex].get_block_size();
	MINTY_ASSERT(m_staticSize_DEBUG >= blockSize, ErrorCode::Memory_DeallocationFailed);
	m_staticSize_DEBUG -= blockSize;
#endif // MINTY_DEBUG
}

Owner<MemoryManager> Minty::MemoryManager::create(MemoryManagerInfo const &info)
{
	return Owner<MemoryManager>(info);
}

MemoryManager &Minty::MemoryManager::get_singleton()
{
	return Context::get_singleton().get_memory_manager();
}

Size Minty::MemoryManager::get_persistent_index(Size const size) const
{
	MINTY_ASSERT(mp_persistentPoolSizeMap != nullptr, ErrorCode::Memory_AllocatorNotInitialized);
	MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedNonZero);

	Size const maxBlockSize = mp_persistentPools[m_persistentPoolCount - 1].get_block_size();
	if (size > maxBlockSize)
	{
		// size too large for any pool
		return SIZE_MAX;
	}

	return mp_persistentPoolSizeMap[size];
}
