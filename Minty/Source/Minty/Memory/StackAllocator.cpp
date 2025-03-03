#include "pch.h"
#include "StackAllocator.h"

using namespace Minty;

void* Minty::StackAllocator::allocate(Size const size)
{
	if (m_size + size > m_capacity)
	{
		return nullptr;
	}

    Byte* ptr = mp_data + m_size;
    m_size += size;
    return ptr;
}

void Minty::StackAllocator::clear()
{
	for (auto& destructor : m_destructors)
	{
		destructor();
	}
	m_destructors.clear();
	m_size = 0;
}
