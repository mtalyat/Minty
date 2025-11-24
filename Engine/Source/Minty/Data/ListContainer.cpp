#include "pch.h"
#include "ListContainer.h"

using namespace Minty;

void Minty::ListContainer::set_at(void const* const data, Size const count, Size const index)
{
	DynamicContainer::set_at(data, count * m_stride, index * m_stride);
}

void const* Minty::ListContainer::get_at(Size const index) const
{
	return DynamicContainer::get_at(index * m_stride);
}

Bool Minty::ListContainer::set(void const* const data, Size const count)
{
	return DynamicContainer::set(data, count);
}

Bool Minty::ListContainer::append(void const* const data, Size const count)
{
	MINTY_ASSERT(data != nullptr, "Cannot append nullptr data.");
	MINTY_ASSERT(count > 0, "Cannot append data without a count.");

	// if new size will surpass the capacity, double the capacity
	Size newSize = m_size + count * m_stride;

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

			reserve(newCapacity / m_stride);
		}
		else
		{
			// no capacity yet, just allocate what is needed
			reserve(newSize / m_stride);
		}
	}

	Size index = m_size / m_stride;

	// resize first
	resize(newSize / m_stride);

	// set data in the new space
	set_at(data, count, index);

	return true;
}

Bool Minty::ListContainer::reserve(Size const newCapacity)
{
	return DynamicContainer::reserve(newCapacity * m_stride);
}

Bool Minty::ListContainer::resize(Size const count)
{
	Size size = count * m_stride;
	if (size > m_capacity)
	{
		// need to resize: try double capacity or new size, whichever is larger
		Size newCapacity = m_capacity * 2;
		if (size > newCapacity)
		{
			newCapacity = size;
		}

		// resize if able
		if (!reserve(newCapacity / m_stride))
		{
			return false;
		}
	}

	// set size
	m_size = size;

	return true;
}
