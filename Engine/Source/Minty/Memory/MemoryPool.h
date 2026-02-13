#ifndef MINTY_MEMORY_MEMORYPOOL_H
#define MINTY_MEMORY_MEMORYPOOL_H

/**
 * @file MemoryPool.h
 * @brief Header file for the MemoryPool class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
	struct MemoryPoolInfo;
	
	/**
	 * @brief A pool-based memory allocator.
	 */
	class MemoryPool
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a MemoryPool using the given information.
		 * @param info The information for creating the MemoryPool.
		 */
		MemoryPool(MemoryPoolInfo const& info);

		~MemoryPool();

		MemoryPool(MemoryPool const& other) = delete;
		MemoryPool(MemoryPool&& other) = delete;

#pragma endregion

#pragma region Operators

	public:
		MemoryPool& operator=(MemoryPool const& other) = delete;
		MemoryPool& operator=(MemoryPool&& other) = delete;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the size of each block in bytes.
		 * @return The block size in bytes.
		 */
		Size get_block_size() const { return m_blockSize - sizeof(Size); }

		/**
		 * @brief Gets the total capacity of the memory pool in blocks.
		 * @return The capacity in blocks.
		 */
		Size get_capacity() const { return m_blockCountCapacity; }

		/**
		 * @brief Gets the current number of allocated blocks.
		 * @return The number of allocated blocks.
		 */
		Size get_count() const { return m_blockCountCapacity - m_freeCount; }

		/**
		 * @brief Gets a pointer to the internal data.
		 * @return A pointer to the internal data.
		 */
		Byte* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Allocates a block of memory from the pool.
		 * @return A pointer to the allocated block.
		 */
		Any allocate();

		/**
		 * @brief Deallocates a previously allocated block of memory.
		 * @param ptr The pointer to the block to deallocate.
		 */
		void deallocate(Any const ptr);

		/**
		 * @brief Resets the memory pool, making all blocks available.
		 */
		void reset();

	private:
		void initialize_free_blocks();

#pragma endregion

#pragma region Variables

	private:
		Size m_blockSize;
		Size m_blockCountCapacity;
		Byte* mp_data;
		Byte** mpp_freeBlocks;
		Size m_freeCount;

#pragma endregion
	};
}

#endif // MINTY_MEMORY_MEMORYPOOL_H