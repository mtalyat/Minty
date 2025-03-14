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
		/// Clears all data out of this Container.
		/// </summary>
		void clear() override;

		/// <summary>
		/// Sets the new size for this Container.
		/// </summary>
		/// <param name="size">The number of bytes.</param>
		/// <returns>True on success.</returns>
		virtual Bool resize(Size const size) override;

#pragma endregion
	};
}