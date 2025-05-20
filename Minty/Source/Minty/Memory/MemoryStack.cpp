#include "pch.h"
#include "MemoryStack.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;


/// <summary>
/// Creates a new MemoryStack with the given capacity in Bytes.
/// </summary>
/// <param name="capacity">The capacity in Bytes.</param>
Minty::MemoryStack::MemoryStack(MemoryStackBuilder const& builder)
	: m_capacity(builder.capacity)
	, m_size(0)
	, mp_data(nullptr)
{
	MINTY_ASSERT(m_capacity > 0, "Cannot create MemoryStack with capacity of 0.");

	mp_data = new Byte[m_capacity];
}

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
