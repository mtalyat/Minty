#include "pch.h"
#include "DynamicContainer.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

Bool Minty::DynamicContainer::append(void const* const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, "Cannot append nullptr data.");
	MINTY_ASSERT(size > 0, "Cannot append data without a size.");

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
	if (capacity <= m_capacity) return true;

	// allocate a new array
	Byte* newData = static_cast<Byte*>(allocate(capacity, m_allocator));

	// copy over existing data, if any
	if (mp_data)
	{
		memcpy(newData, mp_data, m_size);

		// delete old array
		deallocate(mp_data, m_capacity, m_allocator);
	}

	// update reference and data
	mp_data = newData;
	m_capacity = capacity;

	return true;
}
