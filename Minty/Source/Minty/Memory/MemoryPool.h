#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
	/// <summary>
	/// Manages a pool of memory blocks.
	/// </summary>
	class MemoryPool
	{
#pragma region Variables

	private:
		Size m_blockSize;
		Size m_blockCountCapacity;
		Size m_blockCount;
		Byte* mp_data;
		Size* mp_freeBlocks;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new MemoryPool with enough space for the given block size and count.
		/// </summary>
		/// <param name="blockSize">The size of each block when allocate() is called.</param>
		/// <param name="blockCountCapacity">The maximum number of blocks that can be allocated at once.</param>
		MemoryPool(Size const blockSize, Size const blockCountCapacity);

		MemoryPool(MemoryPool const& other) = delete;

		MemoryPool(MemoryPool&& other) noexcept
			: m_blockSize(other.m_blockSize)
			, m_blockCountCapacity(other.m_blockCountCapacity)
			, m_blockCount(other.m_blockCount)
			, mp_data(other.mp_data)
			, mp_freeBlocks(other.mp_freeBlocks)
		{
			other.m_blockSize = 0;
			other.m_blockCountCapacity = 0;
			other.m_blockCount = 0;
			other.mp_data = nullptr;
			other.mp_freeBlocks = nullptr;
		}

		~MemoryPool();

#pragma endregion

#pragma region Operators

	public:
		MemoryPool& operator=(MemoryPool const& other) = delete;

		MemoryPool& operator=(MemoryPool&& other) noexcept
		{
			if (this != &other)
			{
				delete[] mp_data;
				delete[] mp_freeBlocks;
				m_blockSize = other.m_blockSize;
				m_blockCountCapacity = other.m_blockCountCapacity;
				m_blockCount = other.m_blockCount;
				mp_data = other.mp_data;
				mp_freeBlocks = other.mp_freeBlocks;
				other.m_blockSize = 0;
				other.m_blockCountCapacity = 0;
				other.m_blockCount = 0;
				other.mp_data = nullptr;
				other.mp_freeBlocks = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of each block in this MemoryPool.
		/// </summary>
		/// <returns>The size of each block in bytes.</returns>
		Size get_block_size() const { return m_blockSize; }

		/// <summary>
		/// Gets the total number of blocks that can be allocated at once.
		/// </summary>
		/// <returns>The maximum number of blocks.</returns>
		Size get_capacity() const { return m_blockCountCapacity; }

		/// <summary>
		/// Gets the number of blocks that have been allocated.
		/// </summary>
		/// <returns>The number of blocks that have been allocated.</returns>
		Size get_count() const { return m_blockCount; }

#pragma endregion


#pragma region Methods

	public:
		/// <summary>
		/// Checks if this MemoryPool is out of space.
		/// </summary>
		/// <returns>True if no more blocks are free.</returns>
		Bool is_full() const { return m_blockCount == m_blockCountCapacity; }

		/// <summary>
		/// Allocates a block of memory and returns the address.
		/// </summary>
		/// <returns></returns>
		void* allocate();

		/// <summary>
		/// Deallocates the given block of memory.
		/// </summary>
		/// <param name="ptr">The pointer to the block of memory.</param>
		void deallocate(void* const ptr);

		/// <summary>
		/// Deallocates all of the memory within this MemoryPool.
		/// </summary>
		void clear();

#pragma endregion
	};
}