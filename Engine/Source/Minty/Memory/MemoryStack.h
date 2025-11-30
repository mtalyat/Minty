#ifndef MINTY_MEMORY_MEMORYSTACK_H
#define MINTY_MEMORY_MEMORYSTACK_H

/**
 * @file MemoryStack.h
 * @brief Header file for the MemoryStack class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	struct MemoryStackInfo;

	/**
	 * @brief A stack-based memory allocator.
	 */
	class MemoryStack
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a MemoryStack using the given information.
		 * @param info The information for creating the MemoryStack.
		 */
		MemoryStack(MemoryStackInfo const& info);

		~MemoryStack();

		MemoryStack(MemoryStack const& other) = delete;
		MemoryStack(MemoryStack&& other) = delete;

#pragma endregion

#pragma region Operators

	public:
		MemoryStack& operator=(MemoryStack const& other) = delete;
		MemoryStack& operator=(MemoryStack&& other) = delete;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the total capacity of the memory stack in bytes.
		 * @return The capacity in bytes.
		 */
		Size get_capacity() const { return m_capacity; }

		/**
		 * @brief Gets the current size of allocated memory in bytes.
		 * @return The current size in bytes.
		 */
		Size get_size() const { return m_size; }

		/**
		 * @brief Gets a pointer to the internal data.
		 * @return A pointer to the internal data.
		 */
		Byte* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Allocates a block of memory from the stack.
		 * @param size The size of the memory block to allocate in bytes.
		 * @return A pointer to the allocated memory.
		 */
		Any allocate(Size const size);

		/**
		 * @brief Deallocates to the given pointer. All allocations after the pointer are invalidated.
		 * @param ptr The pointer to deallocate to.
		 */
		void deallocate(Any const ptr);

		/**
		 * @brief Resets the memory stack, deallocating all memory.
		 */
		inline void reset() { m_size = 0; }

#pragma endregion

#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		Size m_alignment;
		Byte* mp_data;

#pragma endregion
	};
}

#endif // MINTY_MEMORY_MEMORYSTACK_H