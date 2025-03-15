#include "pch.h"
#include "StaticContainer.h"

using namespace Minty;

Bool Minty::StaticContainer::append(void const* const data, Size const size)
{
	// can append to a static container, as long as the capacity allows for it
	if (m_size + size > m_capacity)
	{
		return false;
	}

	// save index to insert data at
	Size index = m_size;

	// increase size
	m_size += size;

	// set the data
	set_at(data, size, index);

	return true;
}

Bool Minty::StaticContainer::resize(Size const size)
{
	// do nothing if already that size
	if (size == m_size)
	{
		return true;
	}

	// do nothing if goes over capacity
	if (size > m_capacity)
	{
		return false;
	}

	// set size
	m_size = size;

	return true;
}
