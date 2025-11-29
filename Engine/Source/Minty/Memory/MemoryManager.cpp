#include "pch.h"
#include "MemoryManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Memory/MemoryManagerInfo.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"
#include "Minty/Memory/FrameAllocator.h"
#include "Minty/Memory/DefaultAllocator.h"
#include "Minty/Memory/TaskAllocator.h"
#include "Minty/Memory/PersistentAllocator.h"
#ifdef MINTY_DEBUG
#include <unordered_map>
#endif // MINTY_DEBUG

using namespace Minty;

#define MINTY_PERSISTENT_ALLOCATOR_INITIALIZE_CASE(size) \
				case size: \
					PersistentAllocator<size>::initialize(poolInfo); \
					break;

#define MINTY_PERSISTENT_ALLOCATOR_SHUTDOWN_CASE(size) \
				case size: \
					PersistentAllocator<size>::shutdown(); \
					break;

#define MINTY_PERSISTENT_ALLOCATOR_ALLOCATE_CASE(size) \
		case size: \
			return PersistentAllocator<size>::allocate(); \
			break;

#define MINTY_PERSISTENT_ALLOCATOR_DEALLOCATE_CASE(size) \
		case size: \
			PersistentAllocator<size>::deallocate(ptr); \
			break;

#define MINTY_PERSISTENT_ALLOCATOR_CASES(action) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(8) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(16) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(32) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(64) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(128) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(256) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(512) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(1024) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(2048) \
	MINTY_PERSISTENT_ALLOCATOR_##action##_CASE(4096)

Minty::MemoryManager::MemoryManager(MemoryManagerInfo const &info)
	: Manager()
{	
	MINTY_ASSERT(info.taskStackInfo != nullptr && info.taskStackCount > 0, ErrorCode::Memory_AllocatorNotInitialized);
	MINTY_ASSERT(info.persistentPoolInfos != nullptr || info.persistentPoolInfoCount > 0, ErrorCode::Memory_AllocatorNotInitialized);
	MINTY_ASSERT(info.persistentPoolInfoCount <= MAX_PERSISTENT_POOLS, ErrorCode::Argument_OutOfBounds);

	m_frameInitialized = info.frameStackInfo != nullptr;
	m_taskInitialized = info.taskStackInfo != nullptr && info.taskStackCount > 0;
	m_persistentInitialized = info.persistentPoolInfos != nullptr && info.persistentPoolInfoCount > 0;

	if (m_frameInitialized)
	{
		FrameAllocator::initialize(*info.frameStackInfo);
	}

	if (m_taskInitialized)
	{
		TaskAllocator::initialize(*info.taskStackInfo, info.taskStackCount);
	}

	if (m_persistentInitialized)
	{
		for (Size i = 0; i < info.persistentPoolInfoCount; ++i)
		{
			MemoryPoolInfo const& poolInfo = info.persistentPoolInfos[i];
			switch (poolInfo.blockSize)
			{
				MINTY_PERSISTENT_ALLOCATOR_CASES(INITIALIZE)
				default:
					MINTY_ABORT(ErrorCode::Memory_SizeMismatch, poolInfo.blockSize);
			}
			m_persistentSizes[i] = poolInfo.blockSize;
		}
	}
}

Minty::MemoryManager::~MemoryManager()
{
	if(m_frameInitialized)
	{
		FrameAllocator::shutdown();
	}

	if(m_taskInitialized)
	{
		TaskAllocator::shutdown();
	}

	if(m_persistentInitialized)
	{
		for(Size i = 0; i < MAX_PERSISTENT_POOLS; ++i)
		{
			Size const poolSize = m_persistentSizes[i];
			if (poolSize == 0)
			{
				// no more pools to shutdown
				break;
			}
			switch (poolSize)
			{
				MINTY_PERSISTENT_ALLOCATOR_CASES(SHUTDOWN)
				default:
					MINTY_ABORT(ErrorCode::Memory_SizeMismatch, poolSize);
			}
		}

		// generate the persistent size map
		for (Size size = 1; size <= MAX_PERSISTENT_POOL_SIZE; ++size)
		{
			m_persistentMap[size] = SIZE_MAX;
			for (Size i = 0; i < MAX_PERSISTENT_POOLS; ++i)
			{
				Size const poolSize = m_persistentSizes[i];
				if (poolSize == 0)
				{
					// no more pools
					break;
				}
				if (size <= poolSize)
				{
					m_persistentMap[size] = i;
					break;
				}
			}
		}
	}
}

void Minty::MemoryManager::frame_update(Timestep const &time)
{
	MINTY_TRACE_SCOPE();

	if(m_frameInitialized)
	{
		FrameAllocator::reset();
	}

	if(m_frameInitialized)
	{
		TaskAllocator::advance();
	}
}

Any Minty::MemoryManager::allocate(AllocatorType const allocator, Size const size)
{
	static Any (MemoryManager::*allocateFunctions[])(Size const) = {
		&MemoryManager::allocate_default,
		&MemoryManager::allocate_frame,
		&MemoryManager::allocate_task,
		&MemoryManager::allocate_persistent};

	return (this->*allocateFunctions[static_cast<Size>(allocator)])(size);
}

Any Minty::MemoryManager::allocate_default(Size const size)
{
	return DefaultAllocator::allocate(size);
}

Any Minty::MemoryManager::allocate_frame(Size const size)
{
	MINTY_ASSERT(m_frameInitialized, ErrorCode::Memory_AllocatorNotInitialized);

	return FrameAllocator::allocate(size);
}

Any Minty::MemoryManager::allocate_task(Size const size)
{
	MINTY_ASSERT(m_taskInitialized, ErrorCode::Memory_AllocatorNotInitialized);

	return TaskAllocator::allocate(size);
}

Any Minty::MemoryManager::allocate_persistent(Size const size)
{
	MINTY_ASSERT(m_persistentInitialized, ErrorCode::Memory_AllocatorNotInitialized);

	Size const poolIndex = get_persistent_index(size);

	MINTY_ASSERT(poolIndex != SIZE_MAX, ErrorCode::Memory_NoSuitableAllocatorFound);

	switch(m_persistentSizes[poolIndex])
	{
		MINTY_PERSISTENT_ALLOCATOR_CASES(ALLOCATE)
		default:
			MINTY_ABORT(ErrorCode::Memory_SizeMismatch, m_persistentSizes[poolIndex]);
	}
}

void Minty::MemoryManager::deallocate(AllocatorType const allocator, Any const ptr)
{
	static void (MemoryManager::*s_deallocateFunctions[])(Any) = {
		&MemoryManager::deallocate_default,
		&MemoryManager::deallocate_frame,
		&MemoryManager::deallocate_task,
		&MemoryManager::deallocate_persistent};

	(this->*s_deallocateFunctions[static_cast<Size>(allocator)])(ptr);
}

void Minty::MemoryManager::deallocate_default(Any const ptr)
{
	DefaultAllocator::deallocate(ptr);
}

void Minty::MemoryManager::deallocate_frame(Any const ptr)
{
	MINTY_ASSERT(m_frameInitialized, ErrorCode::Memory_AllocatorNotInitialized);

	FrameAllocator::deallocate(ptr);
}

void Minty::MemoryManager::deallocate_task(Any const ptr)
{
	MINTY_ASSERT(m_taskInitialized, ErrorCode::Memory_AllocatorNotInitialized);

	TaskAllocator::deallocate(ptr);
}

void Minty::MemoryManager::deallocate_persistent(Any const ptr)
{
	MINTY_ASSERT(m_persistentInitialized, ErrorCode::Memory_AllocatorNotInitialized);

	Size const size = MemoryPool::extract_size(ptr);
	Size const poolIndex = get_persistent_index(size);

	MINTY_ASSERT(poolIndex != SIZE_MAX, ErrorCode::Memory_NoSuitableAllocatorFound);

	switch (m_persistentSizes[poolIndex])
	{
		MINTY_PERSISTENT_ALLOCATOR_CASES(DEALLOCATE)
		default:
			MINTY_ABORT(ErrorCode::Memory_SizeMismatch, m_persistentSizes[poolIndex]);
	}
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
	MINTY_ASSERT(m_persistentInitialized, ErrorCode::Memory_AllocatorNotInitialized);
	MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedNonZero);

	if(size == 0 || size > MAX_PERSISTENT_POOL_SIZE)
	{
		return SIZE_MAX;
	}

	return m_persistentMap[size];
}

#undef MINTY_PERSISTENT_ALLOCATOR_INITIALIZE_CASE
#undef MINTY_PERSISTENT_ALLOCATOR_SHUTDOWN_CASE
#undef MINTY_PERSISTENT_ALLOCATOR_ALLOCATE_CASE
#undef MINTY_PERSISTENT_ALLOCATOR_DEALLOCATE_CASE
#undef MINTY_PERSISTENT_ALLOCATOR_CASES