#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
	/// <summary>
	/// A Container of bytes that holds a list of elements.
	/// </summary>
	class ListContainer
		: public DynamicContainer
	{
#pragma region Variables

	protected:
		Size m_stride; // size of each element in bytes

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty ListContainer.
		/// </summary>
		/// <param name="allocator">The allocator to use.</param>
		ListContainer(Allocator const allocator = Allocator::Default)
			: DynamicContainer(allocator)
			, m_stride(sizeof(Byte))
		{
		}

		/// <summary>
		/// Creates a ListContainer with the given capacity.
		/// </summary>
		/// <param name="stride">The size of each element in bytes.</param>
		/// <param name="capacity">The initial capacity in elements.</param>
		/// <param name="allocator">The allocator to use.</param>
		ListContainer(Size const stride, Size const capacity = DEFAULT_COLLECTION_SIZE, Allocator const allocator = Allocator::Default)
			: DynamicContainer(allocator)
			, m_stride(stride)
		{
			MINTY_ASSERT(stride > 0, "Stride must be greater than 0.");

			reserve(capacity);
		}

		/// <summary>
		/// Creates a ListContainer with the given data and size.
		/// </summary>
		/// <param name="data">The byte data.</param>
		/// <param name="stride">The size of each element in bytes.</param>
		/// <param name="count">The size of the data in elements.</param>
		/// <param name="allocator">The allocator to use.</param>
		ListContainer(void const* const data, Size const stride, Size const count, Allocator const allocator = Allocator::Default)
			: DynamicContainer(allocator)
			, m_stride(stride)
		{
			MINTY_ASSERT(stride > 0, "Stride must be greater than 0.");

			if (data && count)
			{
				set(data, count);
			}
		}

		/// <summary>
		/// Copies the given DynamicAllocator.
		/// </summary>
		/// <param name="other">The DynamicAllocator to copy.</param>
		ListContainer(ListContainer const& other)
			: DynamicContainer(other)
			, m_stride(other.m_stride)
		{
		}

		/// <summary>
		/// Moves the given DynamicAllocator.
		/// </summary>
		/// <param name="other">The DynamicAllocator to move.</param>
		ListContainer(ListContainer&& other) noexcept
			: DynamicContainer(std::move(other))
			, m_stride(std::move(other.m_stride))
		{
		}

#pragma endregion

#pragma region Operators

	public:
		ListContainer& operator=(ListContainer const& other)
		{
			if (this != &other)
			{
				DynamicContainer::operator=(other);
				m_stride = other.m_stride;
			}
			return *this;
		}

		ListContainer& operator=(ListContainer&& other) noexcept
		{
			if (this != &other)
			{
				DynamicContainer::operator=(std::move(other));
				m_stride = std::move(other.m_stride);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of each element in bytes.
		/// </summary>
		/// <returns>The size of an element in bytes.</returns>
		Size get_stride() const { return m_stride; }

		/// <summary>
		/// Sets the stride (size of each element in bytes) for this Container.
		/// </summary>
		/// <param name="stride">The size of an element in bytes.</param>
		void set_stride(Size const stride)
		{
			MINTY_ASSERT(stride > 0, "Stride must be greater than 0.");
			MINTY_ASSERT(m_size % stride == 0, "Size of the Container must be a multiple of the stride.");
			m_stride = stride;
		}

		/// <summary>
		/// Gets the number of elements in this Container.
		/// </summary>
		/// <returns>The number of elements.</returns>
		Size get_count() const { return m_size / m_stride; }

#pragma endregion

#pragma region Methods

	protected:
		Bool append_one(void const* const object, Size const size) override
		{
			MINTY_ASSERT(size == m_stride, "Size of the object being appended must match the stride of the ListContainer.");
			return append(object, 1);
		}

	public:
		/// <summary>
		/// Sets the element bytes at the given element index and count.
		/// </summary>
		/// <param name="data">The bytes of the element(s) to set.</param>
		/// <param name="count">The number of elements to set.</param>
		/// <param name="index">The index of the element(s) to set.</param>
		void set_at(void const* const data, Size const count, Size const index) override;

		/// <summary>
		/// Gets the element bytes at the given element index.
		/// </summary>
		/// <param name="index">The index to the element.</param>
		/// <returns>A pointer to the element at the given index.</returns>
		void const* get_at(Size const index) const override;

		/// <summary>
		/// Resizes and sets the data to the given element bytes.
		/// </summary>
		/// <param name="data">The element bytes to set.</param>
		/// <param name="size">The number of elements to set.</param>
		/// <returns>True if set successfully.</returns>
		Bool set(void const* const data, Size const count) override;

		/// <summary>
		/// Adds the given element bytes to the end of the data within this Container. Reserves more space if needed.
		/// </summary>
		/// <param name="data">The bytes of the element(s) to append.</param>
		/// <param name="count">The number of elements to append.</param>
		/// <returns>True if appended successfully.</returns>
		Bool append(void const* const data, Size const count = 1) override;

		/// <summary>
		/// Sets the new capacity for this Container.
		/// </summary>
		/// <param name="capacity">The new capacity to set, in elements.</param>
		/// <returns>True on success.</returns>
		Bool reserve(Size const newCapacity) override;

		/// <summary>
		/// Sets the new size for this Container.
		/// </summary>
		/// <param name="count">The number of elements.</param>
		/// <returns>True on success.</returns>
		Bool resize(Size const count) override;

#pragma endregion
	};
}