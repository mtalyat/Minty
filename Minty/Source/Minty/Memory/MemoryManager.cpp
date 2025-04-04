#include "pch.h"
#include "MemoryManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Core/Format.h"

using namespace Minty;

void Minty::MemoryManager::update()
{
	// free memory of single frame allocator
	m_staticSize -= m_temporary.get_size();
	m_temporary.clear();

	// move to next task
	m_taskIndex = (m_taskIndex + 1) % TASK_MEMORY_COUNT;

	// free all of its remaining memory
	m_staticSize -= m_task[m_taskIndex].get_size();
	m_task[m_taskIndex].clear();
}

Size Minty::MemoryManager::get_persistent_index(Size const size) const
{
	Size index = 0;
	for (; index < PERSISTENT_MEMORY_COUNT && size > m_persistent[index].get_block_size(); ++index) {}
	return index;
}

void* Minty::MemoryManager::allocate(Size const size, Allocator const allocator)
{
	MINTY_ASSERT(size > 0, "Cannot allocate 0 bytes.");

	switch (allocator)
	{
	case Allocator::Temporary:
		m_staticSize += size;
		return m_temporary.allocate(size);
	case Allocator::Task:
		m_staticSize += size;
		return m_task[m_taskIndex].allocate(size);
	case Allocator::Persistent:
	{
		// find the pool to use, based on the size
		Size index = get_persistent_index(size);

		MINTY_ASSERT(index != PERSISTENT_MEMORY_COUNT, F("Cannot allocate memory of size {} bytes. No pool large enough is available.", size));

		// if pool is full, do not allocate
		if (m_persistent[index].is_full())
		{
			MINTY_ERROR(F("Persistent memory pool is full. Pool capacity: {} bytes.", m_persistent[index].get_block_size()));
			return nullptr;
		}

		// allocate memory
		m_staticSize += size;
		return m_persistent[index].allocate();
	}
	default:
		m_dynamicSize += size;
		return malloc(size);
	}
}

void Minty::MemoryManager::deallocate(void* const ptr, Size const size, Allocator const allocator)
{
	MINTY_ASSERT(ptr != nullptr, "Cannot deallocate nullptr.");
	MINTY_ASSERT(size > 0, "Cannot deallocate 0 bytes.");

#ifdef MINTY_DEBUG

	// ensure the pointer belongs to the given allocator
	Allocator temp = Allocator::Default;
	if (ptr >= m_temporary.get_data() && ptr < m_temporary.get_data() + m_temporary.get_size())
	{
		temp = Allocator::Temporary;
	}
	else
	{
		Size taskIndex = 0;
		for (; taskIndex < TASK_MEMORY_COUNT; ++taskIndex)
		{
			if (ptr >= m_task[taskIndex].get_data() && ptr < m_task[taskIndex].get_data() + m_task[taskIndex].get_size())
			{
				temp = Allocator::Task;
				break;
			}
		}

		// if taskIndex != m_taskIndex, then it is from a task, but not the current one
		MINTY_ASSERT(temp != Allocator::Task || taskIndex == m_taskIndex, "The given pointer is not from the current task.");

		Size index = get_persistent_index(size);
		if (index != PERSISTENT_MEMORY_COUNT && ptr >= m_persistent[index].get_data() && ptr < m_persistent[index].get_data() + m_persistent[index].get_block_size())
		{
			temp = Allocator::Persistent;
		}
	}

	MINTY_ASSERT(temp == allocator, "The given pointer does not belong to the given allocator.");

#endif // MINTY_DEBUG

	switch (allocator)
	{
	case Allocator::Temporary:
		// verify that this pointer is the last element of the stack
		MINTY_ASSERT(size <= m_temporary.get_size() && m_temporary.get_data() + m_temporary.get_size() - size == ptr, "The given pointer is not the last element of the stack.");
		m_temporary.deallocate(size);
		m_staticSize -= size;
		break;
	case Allocator::Task:
		// verify that this pointer is the last element of the stack
		MINTY_ASSERT(size <= m_task[m_taskIndex].get_size() && m_task[m_taskIndex].get_data() + m_task[m_taskIndex].get_size() - size == ptr, "The given pointer is not the last element of the stack.");
		m_task[m_taskIndex].deallocate(size);
		m_staticSize -= size;
		break;
	case Allocator::Persistent:
	{
		// find the pool to use, based on the size
		Size index = get_persistent_index(size);

		// deallocate memory
		m_persistent[index].deallocate(ptr);
		m_staticSize -= size;
		break;
	}
	default:
		free(ptr);
		m_dynamicSize -= size;
		break;
	}
}

Owner<MemoryManager> Minty::MemoryManager::create(MemoryManagerBuilder const& builder)
{
	return Owner<MemoryManager>(builder);
}

MemoryManager& Minty::MemoryManager::get_singleton()
{
	return Context::get_singleton().get_memory_manager();
}
