#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
	/// <summary>
	/// Manages a stack of memory.
	/// </summary>
	class MemoryStack
	{
#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		Byte* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new MemoryStack with the given capacity in Bytes.
		/// </summary>
		/// <param name="capacity">The capacity in Bytes.</param>
		MemoryStack(Size const capacity)
			: m_capacity(capacity)
			, m_size(0)
			, mp_data(new Byte[capacity])
		{}

		MemoryStack(MemoryStack const& other) = delete;

		MemoryStack(MemoryStack&& other) noexcept
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.mp_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

#pragma endregion

#pragma region Operators

	public:
		MemoryStack& operator=(MemoryStack const& other) = delete;

		MemoryStack& operator=(MemoryStack&& other) noexcept
		{
			if (this != &other)
			{
				delete[] mp_data;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = other.mp_data;
				other.mp_data = nullptr;
				other.m_size = 0;
				other.m_capacity = 0;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of this MemoryStack.
		/// </summary>
		/// <returns>The maximum number of bytes that can be allocated at once.</returns>
		Size get_capacity() const { return m_capacity; }

		/// <summary>
		/// Gets the number of allocated bytes.
		/// </summary>
		/// <returns>The number of bytes that have been allocated.</returns>
		Size get_size() const { return m_size; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Allocates the given number of bytes.
		/// </summary>
		/// <param name="size">The number of bytes to allocate.</param>
		/// <returns>The pointer to the allocated data.</returns>
		void* allocate(Size const size);

		/// <summary>
		/// Deallocates the given number of bytes.
		/// </summary>
		/// <param name="size">The number of bytes to free from memory.</param>
		void deallocate(Size const size);

		/// <summary>
		/// Deallocates all memory.
		/// </summary>
		void clear();

#pragma endregion
	};
}