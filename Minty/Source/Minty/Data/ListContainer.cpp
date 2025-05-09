#include "pch.h"
#include "ListContainer.h"

using namespace Minty;

void Minty::ListContainer::set_at(void const* const data, Size const size, Size const index)
{
	DynamicContainer::set_at(data, size * m_stride, index * m_stride);
}

Bool Minty::ListContainer::append(void const* const data, Size const size)
{
	return DynamicContainer::append(data, size * m_stride);
}

Bool Minty::ListContainer::reserve(Size const newCapacity)
{
	return DynamicContainer::reserve(newCapacity * m_stride);
}

Bool Minty::ListContainer::resize(Size const size)
{
	return DynamicContainer::resize(size * m_stride);
}
