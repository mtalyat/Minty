#include "pch.h"
#include "BufferContainer.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Render/Buffer.h"

using namespace Minty;

Minty::BufferContainer::BufferContainer()
	: Container(), m_buffer(nullptr), m_usage(BufferUsage::Undefined), m_capacity(0), m_size(0)
{
}

Minty::BufferContainer::BufferContainer(BufferUsage const usage)
	: Container(), m_buffer(nullptr), m_usage(usage), m_capacity(0), m_size(0)
{
}

Minty::BufferContainer::BufferContainer(Size const capacity, BufferUsage const usage)
	: Container(), m_buffer(nullptr), m_usage(usage), m_capacity(0), m_size(0)
{
	reserve(capacity);
}

Minty::BufferContainer::BufferContainer(BufferContainer const &other)
	: Container(), m_buffer(other.m_buffer), m_usage(other.m_usage), m_capacity(other.m_capacity), m_size(other.m_size)
{
}

Minty::BufferContainer::BufferContainer(BufferContainer &&other) noexcept
	: Container(), m_buffer(std::move(other.m_buffer)), m_usage(std::move(other.m_usage)), m_capacity(std::move(other.m_capacity)), m_size(std::move(other.m_size))
{
	other.m_buffer = nullptr;
	other.m_capacity = 0;
	other.m_size = 0;
}

BufferContainer &Minty::BufferContainer::operator=(BufferContainer const &other)
{
	if (this != &other)
	{
		m_buffer = other.m_buffer;
		m_usage = other.m_usage;
		m_capacity = other.m_capacity;
		m_size = other.m_size;
	}

	return *this;
}

BufferContainer &Minty::BufferContainer::operator=(BufferContainer &&other) noexcept
{
	if (this != &other)
	{
		m_buffer = std::move(other.m_buffer);
		m_usage = std::move(other.m_usage);
		m_capacity = std::move(other.m_capacity);
		m_size = std::move(other.m_size);
	}
	return *this;
}

void Minty::BufferContainer::set_at(void const *const data, Size const size, Size const index)
{
	MINTY_ASSERT(data != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(index + size <= m_size, ErrorCode::Argument_InvalidSize, size);

	Byte *containerData = static_cast<Byte *>(m_buffer->get_data());

	memcpy(&containerData[index], data, size);
}

void const *Minty::BufferContainer::get_at(Size const index) const
{
	MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds, index);
	Byte *containerData = static_cast<Byte *>(m_buffer->get_data());
	return &containerData[index];
}

Bool Minty::BufferContainer::append(void const *const data, Size const size)
{
	MINTY_ASSERT(data != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedNonZero);

	// if new size will surpass the capacity, double the capacity
	Size newSize = m_size + size;

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

		reserve(newCapacity);
	}
	else
	{
		// no capacity yet, just allocate what is needed
		reserve(newSize);
	}

	Size index = m_size;

	// resize first
	resize(newSize);

	// set data in the new space
	set_at(data, size, index);

	return true;
}

void Minty::BufferContainer::clear()
{
	m_size = 0;
}

Bool Minty::BufferContainer::reserve(Size const newCapacity)
{
	// ignore if below capacity
	if (newCapacity <= m_capacity)
		return true;

	// allocate a new buffer, using this buffer's current data, if there is one
	BufferInfo info{};
	if (m_buffer != nullptr)
	{
		info.data = m_buffer->get_data();
	}
	info.frequent = true;
	info.size = newCapacity;
	info.usage = m_usage;

	Owner<Buffer> newBuffer = Buffer::create(info);

	// update reference and data
	m_buffer = newBuffer;
	m_capacity = newCapacity;

	return true;
}

Bool Minty::BufferContainer::resize(Size const newSize)
{
	if (newSize > m_capacity)
	{
		// need to resize: try double capacity or new size, whichever is larger
		Size newCapacity = m_capacity << 1;
		if (newSize > newCapacity)
			newCapacity = newSize;

		// resize if able
		if (!reserve(newCapacity))
			return false;
	}

	// set size
	m_size = newSize;

	return true;
}