#pragma once
#include "Minty/Data/MemoryContainer.h"

namespace Minty
{
	/// <summary>
	/// A Container of bytes that has a constant capacity. The size is dynamic, but only within the capacity.
	/// </summary>
	class StaticContainer
		: public MemoryContainer
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty StaticContainer.
		/// </summary>
		/// <param name="allocator">The allocator to use.</param>
		StaticContainer(Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
		}

		/// <summary>
		/// Creates a StaticContainer with the given capacity.
		/// </summary>
		/// <param name="capacity">The capacity in bytes.</param>
		/// <param name="allocator">The allocator to use.</param>
		StaticContainer(Size const capacity, Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
			if (capacity)
			{
				m_capacity = capacity;
				mp_data = static_cast<Byte*>(allocate(capacity, allocator));
			}
		}

		/// <summary>
		/// Creates a ConstantContainer with the given data and size.
		/// </summary>
		/// <param name="data">The byte data.</param>
		/// <param name="size">The size of the data in bytes.</param>
		/// <param name="allocator">The allocator to use.</param>
		StaticContainer(void const* const data, Size const size, Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
			if (data && size)
			{
				m_capacity = size;
				m_size = size;
				mp_data = static_cast<Byte*>(allocate(size, allocator));
				memcpy(mp_data, data, size);
			}
		}

		/// <summary>
		/// Copies the given StaticContainer.
		/// </summary>
		/// <param name="other">The StaticContainer to copy.</param>
		StaticContainer(StaticContainer const& other)
			: MemoryContainer(other)
		{
		}

		/// <summary>
		/// Moves the given StaticContainer.
		/// </summary>
		/// <param name="other">The StaticContainer to copy.</param>
		StaticContainer(StaticContainer&& other) noexcept
			: MemoryContainer(other)
		{
		}

#pragma endregion

#pragma region Operators

	public:
		StaticContainer& operator=(StaticContainer const& other)
		{
			if (this != &other)
			{
				MemoryContainer::operator=(other);
			}

			return *this;
		}

		StaticContainer& operator=(StaticContainer&& other) noexcept
		{
			if (this != &other)
			{
				MemoryContainer::operator=(std::move(other));
			}

			return *this;
		}

#pragma endregion

	public:
		/// <summary>
		/// Adds the given bytes to the end of the data within this Container. Reserves more space if needed.
		/// </summary>
		/// <param name="data">The bytes to append.</param>
		/// <param name="size">The number of bytes to append.</param>
		/// <returns>True if appended successfully.</returns>
		Bool append(void const* const data, Size const size) override;

		/// <summary>
		/// Does nothing. Static containers cannot change capacity.
		/// </summary>
		/// <param name="capacity">The capacity in bytes.</param>
		/// <returns>True if capacity is equal to the current capacity, otherwise false.</returns>
		Bool reserve(Size const capacity) override { return capacity == m_capacity; }

		/// <summary>
		/// Sets the new size for this Container.
		/// </summary>
		/// <param name="size">The number of bytes.</param>
		/// <returns>True on success.</returns>
		Bool resize(Size const size) override;
	};
}