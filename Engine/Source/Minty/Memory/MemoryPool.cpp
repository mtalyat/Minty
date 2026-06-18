#include "pch.h"
#include "MemoryPool.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/MemoryPoolInfo.h"

using namespace Minty;

Minty::MemoryPool::MemoryPool(MemoryPoolInfo const &info)
	: m_blockSize(info.blockSize + sizeof(Size)), m_blockCountCapacity(info.blockCount), mp_data(nullptr), mpp_freeBlocks(nullptr), m_freeCount(0)
{
	MINTY_ASSERT(info.blockSize > 0, ErrorCode::Argument_ExpectedNonZero);
	MINTY_ASSERT(info.blockCount > 0, ErrorCode::Argument_ExpectedNonZero);

	mp_data = static_cast<Byte *>(std::malloc(m_blockSize * m_blockCountCapacity));
	MINTY_ASSERT(mp_data != nullptr, ErrorCode::Memory_AllocationFailed);
	mpp_freeBlocks = static_cast<Byte **>(std::malloc(sizeof(Byte *) * m_blockCountCapacity));
	MINTY_ASSERT(mpp_freeBlocks != nullptr, ErrorCode::Memory_AllocationFailed);

	initialize_free_blocks();
}

Minty::MemoryPool::~MemoryPool()
{
	std::free(mp_data);
	std::free(mpp_freeBlocks);
}

Any Minty::MemoryPool::allocate()
{
	// do nothing if no free blocks
	if (m_freeCount == 0)
	{
		return nullptr;
	}

	// get index of block next free block
	Any const ptr = mpp_freeBlocks[--m_freeCount];

	// add size header for deallocation later
	Size const externalSize = get_block_size();
	*reinterpret_cast<Size *>(ptr) = externalSize;

	// return pointer to block after size header
	return static_cast<Any>(static_cast<Byte *>(ptr) + sizeof(Size));
}

void Minty::MemoryPool::deallocate(Any const ptr)
{
	// do nothing if null
	if (ptr == nullptr)
	{
		return;
	}

    Byte* const bytePtr = static_cast<Byte*>(ptr) - sizeof(Size);

#ifdef MINTY_DEBUG

	// Check that pointer is within pool memory range
	MINTY_ASSERT(bytePtr >= mp_data && bytePtr < mp_data + (m_blockSize * m_blockCountCapacity),
				 ErrorCode::Argument_ForeignPointer);

	// Check that pointer is aligned to block size
	MINTY_ASSERT((bytePtr - mp_data) % m_blockSize == 0,
				 ErrorCode::Argument_AlignmentMismatch);

	// Check that pool is not empty
	MINTY_ASSERT(m_freeCount < m_blockCountCapacity, ErrorCode::Memory_DeallocationFailed);

	// Check that pointer is not already in free stack
	for (Size i = 0; i < m_freeCount; i++)
	{
		MINTY_ASSERT(mpp_freeBlocks[i] != bytePtr,
					 ErrorCode::Memory_DeallocationFailed);
	}

#endif // MINTY_DEBUG

	// add block back to free stack
	mpp_freeBlocks[m_freeCount++] = bytePtr;
}

void Minty::MemoryPool::reset()
{
	m_freeCount = 0;
	initialize_free_blocks();
}

void Minty::MemoryPool::initialize_free_blocks()
{
	for (Size i = 0; i < m_blockCountCapacity; ++i)
	{
		mpp_freeBlocks[m_blockCountCapacity - i - 1] = mp_data + (i * m_blockSize);
	}
}
