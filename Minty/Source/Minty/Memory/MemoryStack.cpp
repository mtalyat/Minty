#include "pch.h"
#include "MemoryStack.h"

using namespace Minty;

void* Minty::MemoryStack::allocate(Size const size)
{
	MINTY_ASSERT(size > 0, "Cannot allocate 0 bytes.");
	MINTY_ASSERT(m_size + size <= m_capacity, "MemoryStack is full.");

	void* ptr = mp_data + m_size;
	m_size += size;
	return ptr;
}

void Minty::MemoryStack::deallocate(Size const size)
{
	MINTY_ASSERT(size > 0, "Cannot deallocate 0 bytes.");
	MINTY_ASSERT(size <= m_size, "Cannot deallocate more memory than is allocated.");

	m_size -= size;
}

void Minty::MemoryStack::clear()
{
	m_size = 0;
}
