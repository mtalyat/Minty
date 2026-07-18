#include "pch.hpp"
#include "MemoryStack.hpp"
#include "MemoryStackInfo.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

Minty::MemoryStack::MemoryStack(MemoryStackInfo const &info)
	: m_capacity(info.capacity), m_size(0), m_alignment(info.alignment), mp_data(nullptr)
{
	MINTY_ASSERT(m_capacity > 0, ErrorCodeEnum::Argument_ExpectedAboveZero);

	mp_data = static_cast<Byte *>(std::malloc(m_capacity));
}

Minty::MemoryStack::~MemoryStack()
{
	std::free(mp_data);
}

void *Minty::MemoryStack::allocate(Size const size)
{
	MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	if (m_size + size > m_capacity)
	{
		// stack is full, cannot allocate more memory
		return nullptr;
	}

	// allocate memory and update size
	m_size += size;
	return static_cast<Pointer>(mp_data + m_size);
}

void Minty::MemoryStack::deallocate(Pointer const ptr)
{
	// do nothing if ptr is null
	if (ptr == nullptr)
	{
		return;
	}

	Byte *const bytePtr = static_cast<Byte *>(ptr);

#ifdef MINTY_DEBUG

	// Check that pointer is within stack memory range
	MINTY_ASSERT(bytePtr >= mp_data && bytePtr < mp_data + m_capacity,
				 ErrorCodeEnum::Argument_ForeignPointer);

	// Check that pointer is aligned to alignment size
	MINTY_ASSERT((bytePtr - mp_data) % m_alignment == 0,
				 ErrorCodeEnum::Argument_AlignmentMismatch);

	// Check that pointer is not beyond current offset
	MINTY_ASSERT(bytePtr <= mp_data + m_size,
				 ErrorCodeEnum::Argument_OutOfRange);

#endif // MINTY_DEBUG

	// deallocate all data from this pointer and afterwards
	m_size = static_cast<Size>(bytePtr - mp_data);
}
