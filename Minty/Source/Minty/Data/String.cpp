#include "pch.h"
#include "String.h"
#include <cstring>

using namespace Minty;

Minty::String::String(Size const capacity)
	: m_capacity(0)
	, m_size(0)
	, mp_data(nullptr)
{
	// do nothing if no capacity
	if (capacity == 0)
	{
		return;
	}

	reserve(capacity);
}

Minty::String::String(Char const* data)
	: m_capacity(0)
	, m_size(0)
	, mp_data(nullptr)
{
	// do nothing if null
	if (!data)
	{
		return;
	}

	// calculate size
	Char const* ptr = data;
	while (*ptr)
	{
		m_size += 1;
		++ptr;
	}
	m_capacity = m_size;

	// allocate memory
	mp_data = new Char[m_capacity + 1];
	mp_data[m_capacity] = '\0';
	memcpy(mp_data, data, m_size * sizeof(Char));
}

void Minty::String::reserve(Size const capacity)
{
	// update capacity
	m_capacity = capacity;

	// cap size to capacity, if needed
	if (m_size > m_capacity)
	{
		m_size = m_capacity;
	}

	// if new capacity is zero, deallocate all memory
	if (m_capacity == 0)
	{
		if (mp_data)
		{
			delete[] mp_data;
			mp_data = nullptr;
		}
		return;
	}

	// allocate new memory
	Char* newData = new Char[m_capacity + 1];
	newData[m_size] = '\0';

	// copy over data, if any
	if (mp_data)
	{
		memcpy(newData, mp_data, m_size * sizeof(Char));

		// deallocate old memory
		delete[] mp_data;
	}

	// replace memory
	mp_data = newData;
}

void Minty::String::resize(Size const size)
{
	// if new size is above capacity, reserve more memory
	if (size > m_capacity)
	{
		reserve(size);
	}

	// in the new space, fill with spaces
	if (size > m_size)
	{
		memset(mp_data + m_size, ' ', (size - m_size) * sizeof(Char));
	}

	// update size
	m_size = size;

	// update null terminator, if possible
	if (m_capacity > 0)
	{
		mp_data[m_size] = '\0';
	}
}

String Minty::String::sub(Size const start, Size const length) const
{
	MINTY_ASSERT(start < m_size, "Start index is out of bounds.");
	MINTY_ASSERT(start + length <= m_size, "Start + length index is out of bounds.");

	// create new string
	String result;
	result.resize(length);
	memcpy(result.mp_data, mp_data + start, length * sizeof(Char));

	return result;
}

Size Minty::String::find(String const& sub) const
{
	if (is_empty() || sub.is_empty())
	{
		return INVALID_INDEX;
	}

	Size length = m_size - sub.m_size + 1;
	for (Size i = 0; i < length; ++i)
	{
		if (memcmp(mp_data + i, sub.mp_data, sub.m_size * sizeof(Char)) == 0)
		{
			return i;
		}
	}

	return INVALID_INDEX;
}