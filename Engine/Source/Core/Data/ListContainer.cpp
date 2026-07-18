#include "pch.hpp"
#include "ListContainer.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

Minty::ListContainer::ListContainer()
	: DynamicContainer(), m_stride(sizeof(Byte))
{
}

Minty::ListContainer::ListContainer(Size const stride, Size const capacity)
	: DynamicContainer(), m_stride(stride)
{
	MINTY_ASSERT(stride > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	reserve(capacity);
}

Minty::ListContainer::ListContainer(PointerConst const data, Size const stride, Size const count)
	: DynamicContainer(), m_stride(stride)
{
	MINTY_ASSERT(stride > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	if (data && count)
	{
		set(data, count);
	}
}

void Minty::ListContainer::set_at(PointerConst const data, Size const count, Size const index)
{
	DynamicContainer::set_at(data, count * m_stride, index * m_stride);
}

void const *Minty::ListContainer::get_at(Size const index) const
{
	return DynamicContainer::get_at(index * m_stride);
}

Bool Minty::ListContainer::set(PointerConst const data, Size const count)
{
	return DynamicContainer::set(data, count);
}

Bool Minty::ListContainer::append(PointerConst const data, Size const count)
{
	MINTY_ASSERT(data != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(count > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

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
