#include "pch.h"
#include "MemoryContainer.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

void Minty::MemoryContainer::set_at(void const* const data, Size const size, Size const index)
{
	MINTY_ASSERT(data != nullptr, "Cannot set nullptr data.");
	MINTY_ASSERT(size > 0, "Cannot set data without a size.");
	MINTY_ASSERT(index + size <= m_size, "Cannot set data that exceeds the size of the container.");

	// copy into data
	memcpy(&mp_data[index], data, size);
}

void const* Minty::MemoryContainer::get_at(Size const index) const
{
	MINTY_ASSERT(index < m_size, "Index out of bounds.");
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
