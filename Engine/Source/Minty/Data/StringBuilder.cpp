#include "StringBuilder.h"
#include "Minty/Memory/MemoryManager.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

Minty::StringBuilder::StringBuilder(Allocator const allocator)
    : mp_data(nullptr), m_size(0), m_capacity(0), m_allocator(allocator)
{
}

Minty::StringBuilder::StringBuilder(Size const initialCapacity, Allocator const allocator)
    : mp_data(nullptr), m_size(0), m_capacity(0), m_allocator(allocator)
{
    reserve(initialCapacity);
}

Minty::StringBuilder::StringBuilder(String const initialString, Allocator const allocator)
    : mp_data(nullptr), m_size(0), m_capacity(0), m_allocator(allocator)
{
    reserve(initialString.get_size());
}

Minty::StringBuilder::~StringBuilder()
{
    if (mp_data)
    {
        MemoryManager& memoryManager = MemoryManager::get_singleton();
        memoryManager.deallocate(mp_data, (m_capacity + 1) * sizeof(Char), m_allocator);
    }
}

void Minty::StringBuilder::reserve(Size const newCapacity)
{
    // Do not reserve if the new capacity is less than or equal to current capacity
    if (newCapacity <= m_capacity)
    {
        return;
    }

    // Allocate new memory and copy existing data
        MemoryManager& memoryManager = MemoryManager::get_singleton();
    void* const ptr = memoryManager.allocate((newCapacity) * sizeof(Char), m_allocator);
    // MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed);
    Char* const newData = static_cast<Char*>(ptr);
    if (mp_data)
    {
        std::memcpy(newData, mp_data, m_size * sizeof(Char));
        memoryManager.deallocate(mp_data, (m_capacity + 1) * sizeof(Char), m_allocator);
    }
    mp_data = newData;
    m_capacity = newCapacity;
}

void Minty::StringBuilder::clear() noexcept
{
    m_size = 0;
    if (mp_data)
    {
        mp_data[0] = '\0';
    }
}

void Minty::StringBuilder::append(Char const c)
{
    // Reserve more space if needed
    if (m_size + 1 >= m_capacity || m_capacity == 0)
    {
        reserve(m_capacity * 2);
    }

    // Append character
    mp_data[m_size] = c;
    m_size++;
    mp_data[m_size] = '\0';
}

void Minty::StringBuilder::append(String const str)
{
    // Reserve more space if needed
    Size const requiredCapacity = m_size + str.get_size();
    if (requiredCapacity > m_capacity)
    {
        if (requiredCapacity > m_capacity * 2 || m_capacity == 0)
        {
            reserve(requiredCapacity);
        }
        else
        {
            reserve(m_capacity * 2);
        }
    }

    // Copy new data
    std::memcpy(mp_data + m_size, str.get_data(), str.get_size() * sizeof(Char));
    m_size += str.get_size();
    mp_data[m_size] = '\0';
}

String Minty::StringBuilder::to_string(Allocator const allocator) const
{
    return String(mp_data, allocator);
}
