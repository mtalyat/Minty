#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Container.h"

namespace Minty
{
	/// <summary>
	/// Holds a collection of bytes in memory.
	/// </summary>
	class MemoryContainer
		: public Container
	{
#pragma region Variables

	protected:
		Allocator m_allocator;
		Size m_capacity;
		Size m_size;
		Byte* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		MemoryContainer(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
		}

		MemoryContainer(MemoryContainer const& other)
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(static_cast<Byte*>(allocate(m_capacity, m_allocator)))
		{
			memcpy(mp_data, other.mp_data, m_size);
		}

		MemoryContainer(MemoryContainer&& other) noexcept
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_allocator = Allocator::Default;
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		virtual ~MemoryContainer()
		{
			if (mp_data)
			{
				deallocate(mp_data, m_size, m_allocator);
				mp_data = nullptr;
			}
			m_capacity = 0;
			m_size = 0;
		}

#pragma endregion

#pragma region Operators

	public:
		MemoryContainer& operator=(MemoryContainer const& other)
		{
			if (this != &other)
			{
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = static_cast<Byte*>(allocate(m_capacity, m_allocator));
				memcpy(mp_data, other.mp_data, m_size);
			}
			return *this;
		}

		MemoryContainer& operator=(MemoryContainer&& other) noexcept
		{
			if (this != &other)
			{
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = other.mp_data;
				other.m_allocator = Allocator::Default;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_data = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the internal data pointer.
		/// </summary>
		/// <returns>A pointer to the internal data.</returns>
		void* get_data() const override { return mp_data; }

		/// <summary>
		/// Gets the number of bytes in this Container.
		/// </summary>
		/// <returns>The size in bytes.</returns>
		Size get_size() const override { return m_size; }

		/// <summary>
		/// Gets the maximum number of bytes in this Container.
		/// </summary>
		/// <returns>The capacity in bytes.</returns>
		Size get_capacity() const override { return m_capacity; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Sets the bytes at the given index and size.
		/// </summary>
		/// <param name="data">The bytes to set.</param>
		/// <param name="size">The number of bytes to set.</param>
		/// <param name="index">The index of the bytes to set.</param>
		void set_at(void const* const data, Size const size, Size const index) override;
		
		/// <summary>
		/// Gets the pointer to the data at the given index.
		/// </summary>
		/// <param name="index">The index in bytes.</param>
		/// <returns>A pointer to the data.</returns>
		void const* get_at(Size const index) const override;

		/// <summary>
		/// Clears all data out of this Container.
		/// </summary>
		virtual void clear() override;

		/// <summary>
		/// Sets the new size for this Container.
		/// </summary>
		/// <param name="size">The number of bytes.</param>
		/// <returns>True on success.</returns>
		virtual Bool resize(Size const size) override;

#pragma endregion
	};
}