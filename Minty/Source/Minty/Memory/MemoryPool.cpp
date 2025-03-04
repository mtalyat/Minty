#include "pch.h"
#include "MemoryPool.h"

using namespace Minty;

Minty::MemoryPool::MemoryPool(Size const blockSize, Size const blockCountCapacity)
	: m_blockSize(blockSize)
	, m_blockCountCapacity(blockCountCapacity)
	, m_blockCount(0)
	, mp_data(new Byte[blockSize * blockCountCapacity])
	, mp_freeBlocks(new Size[blockCountCapacity])
{
	for (Size i = 0; i < m_blockCountCapacity; ++i)
	{
		// flip the order of the free blocks, so it starts allocating from the beginning
		mp_freeBlocks[i] = m_blockCountCapacity - 1 - i;
	}
}

Minty::MemoryPool::~MemoryPool()
{
	delete[] mp_data;
	delete[] mp_freeBlocks;
}

void* Minty::MemoryPool::allocate()
{
	MINTY_ASSERT(!is_full(), "Cannot allocate memory, MemoryPool is full.");

	// get index of block
	Size const index = mp_freeBlocks[m_blockCount++];

	// return pointer to block
	return mp_data + (index * m_blockSize);
}

void Minty::MemoryPool::deallocate(void* const ptr)
{
	MINTY_ASSERT(ptr != nullptr, "Cannot deallocate nullptr.");
	MINTY_ASSERT(m_blockCount > 0, "Cannot deallocate memory, MemoryPool is empty.");
	MINTY_ASSERT(ptr >= mp_data, "Cannot deallocate memory, ptr is invalid (index < 0).");

	// get index of block
	Size const index = static_cast<Size>(static_cast<Byte*>(ptr) - mp_data) / m_blockSize;

	MINTY_ASSERT(index < m_blockCountCapacity, "Cannot deallocate memory, ptr is invalid (index >= capacity).");

	// add index to free blocks
	mp_freeBlocks[--m_blockCount] = index;
}

void Minty::MemoryPool::clear()
{
	for (Size i = 0; i < m_blockCountCapacity; ++i)
	{
		mp_freeBlocks[i] = i;
	}
	m_blockCount = 0;
}
