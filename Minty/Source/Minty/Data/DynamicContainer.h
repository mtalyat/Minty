#pragma once
#include "Minty/Data/MemoryContainer.h"

namespace Minty
{
	/// <summary>
	/// A Container of Bytes with a dynamic capacity and size.
	/// </summary>
	class DynamicContainer
		: public MemoryContainer
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty DynamicContainer.
		/// </summary>
		/// <param name="allocator">The allocator to use.</param>
		DynamicContainer(Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
		}

		/// <summary>
		/// Creates a DynamicContainer with the given capacity.
		/// </summary>
		/// <param name="capacity">The initial capacity in bytes.</param>
		/// <param name="allocator">The allocator to use.</param>
		DynamicContainer(Size const capacity, Allocator const allocator = Allocator::Default)
			: MemoryContainer(allocator)
		{
			reserve(capacity);
		}

		/// <summary>
		/// Copies the given DynamicAllocator.
		/// </summary>
		/// <param name="other">The DynamicAllocator to copy.</param>
		DynamicContainer(DynamicContainer const& other)
			: MemoryContainer(other)
		{
		}

		/// <summary>
		/// Moves the given DynamicAllocator.
		/// </summary>
		/// <param name="other">The DynamicAllocator to move.</param>
		DynamicContainer(DynamicContainer&& other) noexcept
			: MemoryContainer(other)
		{
		}

#pragma endregion

#pragma region Operators

	public:
		DynamicContainer& operator=(DynamicContainer const& other)
		{
			if (this != &other)
			{
				MemoryContainer::operator=(other);
			}

			return *this;
		}

		DynamicContainer& operator=(DynamicContainer&& other) noexcept
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
		/// Adds the given bytes to the end of the data within this Container. Reserves more space if needed.
		/// </summary>
		/// <param name="data">The bytes to append.</param>
		/// <param name="size">The number of bytes to append.</param>
		/// <returns>True if appended successfully.</returns>
		Bool append(void const* const data, Size const size) override;

		/// <summary>
		/// Sets the new capacity for this Container.
		/// </summary>
		/// <param name="capacity">The new capacity to set, in bytes.</param>
		/// <returns>True on success.</returns>
		Bool reserve(Size const newCapacity) override;

#pragma endregion
	};
}