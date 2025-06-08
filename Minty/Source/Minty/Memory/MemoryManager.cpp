#include "pch.h"
#include "MemoryManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Core/Format.h"

using namespace Minty;

void Minty::MemoryManager::dispose()
{
	// clear all memory
	m_temporary.clear();
	for (Size i = 0; i < m_tasks.get_size(); ++i)
	{
		m_tasks[i].clear();
	}
	for (Size i = 0; i < m_persistents.get_size(); ++i)
	{
		m_persistents[i].clear();
	}

	// ensure nothing left
	MINTY_ASSERT_ERROR(m_staticSize == 0, F("MemoryManager has static memory leaks. {} bytes of data leaked.", m_staticSize));

	m_taskIndex = 0;
	m_staticSize = 0;
	m_dynamicSize = 0;

	Manager::dispose();
}

void Minty::MemoryManager::update(Time const& time)
{
	// free memory of single frame allocator
	m_staticSize -= m_temporary.get_size();
	m_temporary.clear();

	// move to next task
	m_taskIndex = (m_taskIndex + 1) % m_tasks.get_size();

	// free all of its remaining memory
	m_staticSize -= m_tasks[m_taskIndex].get_size();
	m_tasks[m_taskIndex].clear();
}

Minty::MemoryManager::MemoryManager(MemoryManagerBuilder const& builder)
	: Manager()
	, m_temporary(builder.temporary)
	, m_tasks(builder.taskCount)
	, m_taskIndex(0)
	, m_persistents(builder.persistents.get_size())
	, m_staticSize(0)
	, m_dynamicSize(0)
{
	// temporary memory stack made above

	// create the task memory stacks
	// they are all the same size
	for (Size i = 0; i < builder.taskCount; i++)
	{
		m_tasks.add(MemoryStack(builder.task));
	}
	
	// create the persistent memory pools
	for (auto const& poolBuilder : builder.persistents)
	{
		m_persistents.add(MemoryPool(poolBuilder));
	}
}

Size Minty::MemoryManager::get_persistent_index(Size const size) const
{
	Size index = 0;
	for (; index < m_persistents.get_size() && size > m_persistents[index].get_block_size(); ++index) {}
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
		return m_tasks[m_taskIndex].allocate(size);
	case Allocator::Persistent:
	{
		// find the pool to use, based on the size
		Size index = get_persistent_index(size);

		MINTY_ASSERT(index != m_persistents.get_size(), F("Cannot allocate memory of size {} bytes. No pool large enough is available.", size));

		// if pool is full, do not allocate
		if (m_persistents[index].is_full())
		{
			MINTY_ERROR(F("Persistent memory pool is full. Pool capacity: {} bytes.", m_persistents[index].get_block_size()));
			return nullptr;
		}

		// allocate memory
		m_staticSize += size;
		return m_persistents[index].allocate();
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
		for (; taskIndex < m_tasks.get_size(); ++taskIndex)
		{
			if (ptr >= m_tasks[taskIndex].get_data() && ptr < m_tasks[taskIndex].get_data() + m_tasks[taskIndex].get_size())
			{
				temp = Allocator::Task;
				break;
			}
		}

		// if taskIndex != m_taskIndex, then it is from a task, but not the current one
		MINTY_ASSERT(temp != Allocator::Task || taskIndex == m_taskIndex, "The given pointer is not from the current task.");

		Size index = get_persistent_index(size);
		if (index != m_persistents.get_size() && ptr >= m_persistents[index].get_data() && ptr < m_persistents[index].get_data() + m_persistents[index].get_block_size())
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
		MINTY_ASSERT(size <= m_tasks[m_taskIndex].get_size() && m_tasks[m_taskIndex].get_data() + m_tasks[m_taskIndex].get_size() - size == ptr, "The given pointer is not the last element of the stack.");
		m_tasks[m_taskIndex].deallocate(size);
		m_staticSize -= size;
		break;
	case Allocator::Persistent:
	{
		// find the pool to use, based on the size
		Size index = get_persistent_index(size);

		// deallocate memory
		m_persistents[index].deallocate(ptr);
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
