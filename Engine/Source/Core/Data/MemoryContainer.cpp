#include "pch.hpp"
#include "MemoryContainer.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

Minty::MemoryContainer::MemoryContainer()
	: m_capacity(0), m_size(0), mp_data(nullptr), m_allocator()
{
}

Minty::MemoryContainer::MemoryContainer(MemoryContainer const &other)
	: m_capacity(other.m_capacity), m_size(other.m_size), mp_data(nullptr), m_allocator()

{
	if(m_size == 0)
	{
		return;
	}
	mp_data = m_allocator.allocate<Byte>(m_capacity);
	memcpy(mp_data, other.mp_data, m_size);
}

Minty::MemoryContainer::MemoryContainer(MemoryContainer &&other) noexcept
	: m_capacity(other.m_capacity), m_size(other.m_size), mp_data(other.mp_data), m_allocator(std::move(other.m_allocator))
{
	other.m_capacity = 0;
	other.m_size = 0;
	other.mp_data = nullptr;
}

Minty::MemoryContainer::~MemoryContainer()
{
	if (mp_data)
	{
		m_allocator.deallocate(mp_data);
		mp_data = nullptr;
	}
	m_capacity = 0;
	m_size = 0;
}

MemoryContainer &Minty::MemoryContainer::operator=(MemoryContainer const &other)
{
	if (this != &other)
	{
		if (mp_data)
		{
			m_allocator.deallocate(mp_data);
		}
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		if (m_capacity == 0)
		{
			mp_data = nullptr;
		} else
		{
			mp_data = m_allocator.allocate<Byte>(m_capacity);
			memcpy(mp_data, other.mp_data, m_size);
		}
	}
	return *this;
}

MemoryContainer &Minty::MemoryContainer::operator=(MemoryContainer &&other) noexcept
{
	if (this != &other)
	{
		if (mp_data)
		{
			m_allocator.deallocate(mp_data);
		}
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		mp_data = other.mp_data;
		m_allocator = std::move(other.m_allocator);
		other.m_capacity = 0;
		other.m_size = 0;
		other.mp_data = nullptr;
	}
	return *this;
}

void Minty::MemoryContainer::set_at(PointerConst const data, Size const size, Size const index)
{
	MINTY_ASSERT(data != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedNonZero);
	MINTY_ASSERT_A(index + size <= m_size, ErrorCodeEnum::Argument_InvalidSize, size);

	// copy into data
	memcpy(&mp_data[index], data, size);
}

void const *Minty::MemoryContainer::get_at(Size const index) const
{
	MINTY_ASSERT_A(index < m_size, ErrorCodeEnum::Argument_OutOfRange, index);
	return &mp_data[index];
}

void Minty::MemoryContainer::clear()
{
	m_size = 0;
}

Bool Minty::MemoryContainer::resize(Size const size)
{
	if (size > m_capacity)
	{
		// need to resize: try double capacity or new size, whichever is larger
		Size newCapacity = m_capacity * 2;
		if (size > newCapacity)
		{
			newCapacity = size;
		}

		// resize if able
		if (!reserve(newCapacity))
		{
			return false;
		}
	}

	// set size
	m_size = size;

	return true;
}
