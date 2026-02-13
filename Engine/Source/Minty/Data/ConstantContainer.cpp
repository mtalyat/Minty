#include "pch.h"
#include "ConstantContainer.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/HeapAllocator.h"

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
		mp_data = static_cast<Byte*>(m_allocator.allocate(size));
	}
}

Minty::ConstantContainer::ConstantContainer(AnyConst const data, Size const size)
	: MemoryContainer()
{
	if (data && size)
	{
		m_capacity = size;
		m_size = size;
		mp_data = static_cast<Byte*>(m_allocator.allocate(size));
		memcpy(mp_data, data, size);
	}
}

void Minty::ConstantContainer::clear()
{
	memset(mp_data, 0, m_size);
}
