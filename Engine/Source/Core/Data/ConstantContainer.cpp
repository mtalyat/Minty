#include "pch.h"
#include "ConstantContainer.h"

using namespace Minty;

Minty::ConstantContainer::ConstantContainer()
	: MemoryContainer()
{
}

Minty::ConstantContainer::ConstantContainer(Size const size)
	: MemoryContainer()
{
	if (size > 0)
	{
		m_capacity = size;
		m_size = size;
		mp_data = m_allocator.allocate<Byte>(size);
	}
}

Minty::ConstantContainer::ConstantContainer(PointerConst const data, Size const size)
	: MemoryContainer()
{
	if (data && size)
	{
		m_capacity = size;
		m_size = size;
		mp_data = m_allocator.allocate<Byte>(size);
		memcpy(mp_data, data, size);
	}
}

void Minty::ConstantContainer::clear()
{
	memset(mp_data, 0, m_size);
}
