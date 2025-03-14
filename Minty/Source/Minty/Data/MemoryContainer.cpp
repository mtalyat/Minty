#include "pch.h"
#include "MemoryContainer.h"
#include "Minty/Core/Macro.h"

using namespace Minty;

void Minty::MemoryContainer::set_at(void const* const data, Size const size, Size const index)
{
	MINTY_ASSERT(data != nullptr, "Cannot set nullptr data.");
	MINTY_ASSERT(index + size <= m_size, "Cannot set data that exceeds the get_size of the container.");

	// copy into data
	memcpy(&mp_data[index], data, size);
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
		Size newCapacity = m_capacity << 1;
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
