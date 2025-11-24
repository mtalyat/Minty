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
	if (m_capacity > 0)
	{
		mp_data = static_cast<Byte*>(malloc(m_capacity * sizeof(Byte)));
	}
}

Minty::MemoryStack::~MemoryStack()
{
	free(mp_data);
}

void* Minty::MemoryStack::allocate(Size const size)
{
	MINTY_ASSERT(size > 0, "Cannot allocate 0 bytes.");

	if (m_size + size > m_capacity)
	{
		// stack is full, cannot allocate more memory
		return nullptr;
	}

	// allocate memory
	void* ptr = mp_data + m_size;
	m_size += size;
	return ptr;
}

void Minty::MemoryStack::deallocate(Size const size)
{
	MINTY_ASSERT(size > 0, "Cannot deallocate 0 bytes.");

	if (size >= m_size)
	{
		m_size = 0;
	}

	m_size -= size;
}

void Minty::MemoryStack::clear()
{
	m_size = 0;
}
