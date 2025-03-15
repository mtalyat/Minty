#pragma once
#include "Minty/Data/MemoryContainer.h"

namespace Minty
{
	/// <summary>
	/// A Container with a fixed capacity and size.
	/// </summary>
	class ConstantContainer
		: public MemoryContainer
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty ConstantContainer.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		ConstantContainer(Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
		}

		/// <summary>
		/// Creates a ConstantContainer with the given size.
		/// </summary>
		/// <param name="size">The size of the ConstantContainer in bytes.</param>
		/// <param name="allocator">The Allocator to use.</param>
		ConstantContainer(Size const size, Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
			if (size)
			{
				m_capacity = size;
				m_size = size;
				mp_data = static_cast<Byte*>(allocate(size, m_allocator));
			}
		}

		/// <summary>
		/// Creates a ConstantContainer with the given data and size.
		/// </summary>
		/// <param name="data">The byte data.</param>
		/// <param name="size">The size of the data in bytes.</param>
		ConstantContainer(void const* const data, Size const size, Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
			if (data && size)
			{
				m_capacity = size;
				m_size = size;
				mp_data = static_cast<Byte*>(allocate(size, m_allocator));
				memcpy(mp_data, data, size);
			}
		}

		/// <summary>
		/// Copies the given ConstantContainer.
		/// </summary>
		/// <param name="other">The ConstantContainer to copy.</param>
		ConstantContainer(ConstantContainer const& other)
			: MemoryContainer(other)
		{
		}

		/// <summary>
		/// Moves the given ConstantContainer.
		/// </summary>
		/// <param name="other">The ConstantContainer to move.</param>
		ConstantContainer(ConstantContainer&& other) noexcept
			: MemoryContainer(other)
		{
		}

#pragma endregion

#pragma region Operators

	public:
		ConstantContainer& operator=(ConstantContainer const& other)
		{
			if (this != &other)
			{
				MemoryContainer::operator=(other);
			}

			return *this;
		}

		ConstantContainer& operator=(ConstantContainer&& other) noexcept
		{
			if (this != &other)
			{
				MemoryContainer::operator=(std::move(other));
			}

			return *this;
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="data">The data to append.</param>
		/// <param name="size">The number of bytes.</param>
		/// <returns>False.</returns>
		Bool append(void const* const data, Size const size) override { return false; }

		/// <summary>
		/// Clears all data out of this Container.
		/// </summary>
		void clear() override;

		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="size">The size in bytes.</param>
		/// <returns>True if size is equal to the current size, otherwise false.</returns>
		Bool resize(Size const size) override { return size == m_size; }

		/// <summary>
		/// Does nothing.
		/// </summary>
		/// <param name="capacity">The capacity in bytes.</param>
		/// <returns>True if capacity is equal to the current capacity, otherwise false.</returns>
		Bool reserve(Size const capacity) override { return capacity == m_capacity; }

#pragma endregion
	};
}