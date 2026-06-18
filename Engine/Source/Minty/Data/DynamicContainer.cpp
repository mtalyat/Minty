#include "pch.h"
#include "DynamicContainer.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Minty::DynamicContainer::DynamicContainer()
	: MemoryContainer()
{
}

Minty::DynamicContainer::DynamicContainer(Size const capacity)
	: MemoryContainer()
{
	reserve(capacity);
}

Minty::DynamicContainer::DynamicContainer(AnyConst const data, Size const size)
	: MemoryContainer()
{
	if (data != nullptr && size > 0)
	{
		set(data, size);
	}
}

Bool Minty::DynamicContainer::append(AnyConst const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedNonZero);

	// if new size will surpass the capacity, double the capacity
	Size newSize = m_size + size;

	if (newSize > m_capacity)
	{
		if (m_capacity)
		{
			Size newCapacity;

			// reserve double current capacity, or more if needed
			if (newSize > (m_capacity << 1))
			{
				newCapacity = newSize;
			}
			else
			{
				newCapacity = m_capacity << 1;
			}

			reserve(newCapacity);
		}
		else
		{
			// no capacity yet, just allocate what is needed
			reserve(newSize);
		}
	}

	Size index = m_size;

	// resize first
	resize(newSize);

	// set data in the new space
	set_at(data, size, index);

	return true;
}

Bool Minty::DynamicContainer::reserve(Size const capacity)
{
	// ignore if below capacity
	if (capacity <= m_capacity)
	{
		return true;
	}

	// allocate a new array
	Byte *const newData = static_cast<Byte *>(m_allocator.allocate(capacity));

	// copy over existing data, if any
	if (mp_data)
	{
		memcpy(newData, mp_data, m_size);

		// delete old array
		m_allocator.deallocate(mp_data);
	}

	// update reference and data
	mp_data = newData;
	m_capacity = capacity;

	return true;
}
