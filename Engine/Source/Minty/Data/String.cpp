#include "String.h"
#include "Minty/Memory/DefaultAllocator.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Minty::String::String()
    : mp_data(nullptr), m_size(0), m_capacity(0)
{
}

Minty::String::String(StringView const view)
    : mp_data(nullptr), m_size(view.get_size()), m_capacity(m_size)
{
    Any const ptr = DefaultAllocator::allocate(sizeof(Char) * (m_capacity + 1));
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_capacity + 1));
    mp_data = static_cast<Char *>(ptr);
    memcpy(mp_data, view.get_data(), sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(Char const *const cstr)
    : mp_data(nullptr), m_size(std::char_traits<Char>::length(cstr)), m_capacity(m_size)
{
    Any const ptr = DefaultAllocator::allocate(sizeof(Char) * (m_capacity + 1));
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_capacity + 1));
    mp_data = static_cast<Char *>(ptr);
    memcpy(mp_data, cstr, sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(Char const c, Size const count)
    : mp_data(nullptr), m_size(count), m_capacity(count)
{
    Any const ptr = DefaultAllocator::allocate(sizeof(Char) * (m_capacity + 1));
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_capacity + 1));
    mp_data = static_cast<Char *>(ptr);
    memset(mp_data, c, sizeof(Char) * m_capacity);
    mp_data[m_size] = '\0';
}

Minty::String::String(String const &other)
    : mp_data(nullptr), m_size(other.m_size), m_capacity(other.m_size)
{
    Any const ptr = DefaultAllocator::allocate(sizeof(Char) * (m_capacity + 1));
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_capacity + 1));
    mp_data = static_cast<Char *>(ptr);
    memcpy(mp_data, other.mp_data, sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(String &&other) noexcept
    : mp_data(other.mp_data), m_size(other.m_size), m_capacity(other.m_capacity)
{
    other.mp_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

Minty::String::~String()
{
    if (mp_data != nullptr)
    {
        DefaultAllocator::deallocate(static_cast<Any>(mp_data));
    }
}

String &Minty::String::operator=(String const &other)
{
    if (this != &other)
    {
        // deallocate current data
        if (mp_data != nullptr)
        {
            DefaultAllocator::deallocate(static_cast<Any>(mp_data));
        }

        // copy data from other
        m_size = other.m_size;
        m_capacity = other.m_size;
        Any const ptr = DefaultAllocator::allocate(sizeof(Char) * (m_capacity + 1));
        MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_capacity + 1));
        mp_data = static_cast<Char *>(ptr);
        memcpy(mp_data, other.mp_data, sizeof(Char) * m_size);
        mp_data[m_size] = '\0';
    }
    return *this;
}

String &Minty::String::operator=(String &&other) noexcept
{
    if (this != &other)
    {
        // deallocate current data
        if (mp_data != nullptr)
        {
            DefaultAllocator::deallocate(static_cast<Any>(mp_data));
        }

        // move data from other
        mp_data = other.mp_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.mp_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

String Minty::String::operator+(StringView const other) const
{
    String result;
    result.m_size = m_size + other.get_size();
    result.m_capacity = result.m_size;
    Any const ptr = DefaultAllocator::allocate(sizeof(Char) * (result.m_capacity + 1));
    MINTY_ASSERT(ptr != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (result.m_capacity + 1));
    result.mp_data = static_cast<Char *>(ptr);
    memcpy(result.mp_data, mp_data, sizeof(Char) * m_size);
    memcpy(result.mp_data + m_size, other.get_data(), sizeof(Char) * other.get_size());
    result.mp_data[result.m_size] = '\0';
    return result;
}

Char Minty::String::index(Size const index) const
{
    MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds, index);
    return mp_data[index];
}

Char const &Minty::String::at(Size const index) const
{
    MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds, index);
    return mp_data[index];
}

Int Minty::String::compare(StringView const other) const noexcept
{
    if (m_size < other.get_size())
    {
        return -1;
    }
    else if (m_size > other.get_size())
    {
        return 1;
    }

    for (Size i = 0; i < m_size; ++i)
    {
        if (mp_data[i] < other[i])
        {
            return -1;
        }
        else if (mp_data[i] > other[i])
        {
            return 1;
        }
    }
    return 0;
}

Size Minty::String::find_first(Char const c, Size const startIndex) const noexcept
{
    for (Size i = startIndex; i < m_size; ++i)
    {
        if (mp_data[i] == c)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_first(StringView const str, Size const startIndex) const noexcept
{
    if (str.get_size() == 0 || str.get_size() > m_size)
    {
        return INVALID_INDEX;
    }

    for (Size i = startIndex; i <= m_size - str.get_size(); ++i)
    {
        Bool found = true;
        for (Size j = 0; j < str.get_size(); ++j)
        {
            if (mp_data[i + j] != str[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_last(Char const c, Size const startIndex) const noexcept
{
    Size start = (startIndex == INVALID_INDEX) ? m_size - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        if (mp_data[i] == c)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_last(StringView const str, Size const startIndex) const noexcept
{
    if (str.get_size() == 0 || str.get_size() > m_size)
    {
        return INVALID_INDEX;
    }

    Size start = (startIndex == INVALID_INDEX) ? m_size - str.get_size() : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        Bool found = true;
        for (Size j = 0; j < str.get_size(); ++j)
        {
            if (mp_data[i + j] != str[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_first_of(StringView const chars, Size const startIndex) const noexcept
{
    for (Size i = startIndex; i < m_size; ++i)
    {
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[i] == chars[j])
            {
                return i;
            }
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_last_of(StringView const chars, Size const startIndex) const noexcept
{
    Size start = (startIndex == INVALID_INDEX) ? m_size - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[i] == chars[j])
            {
                return i;
            }
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_first_not_of(StringView const chars, Size const startIndex) const noexcept
{
    for (Size i = startIndex; i < m_size; ++i)
    {
        Bool found = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[i] == chars[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

Size Minty::String::find_last_not_of(StringView const chars, Size const startIndex) const noexcept
{
    Size start = (startIndex == INVALID_INDEX) ? m_size - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        Bool found = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[i] == chars[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

String Minty::String::sub(Size const startIndex, Size const count) const noexcept
{
    if (startIndex >= m_size)
    {
        return String();
    }

    Size actualCount = count;
    if (count == INVALID_INDEX || startIndex + count > m_size)
    {
        actualCount = m_size - startIndex;
    }

    return String(StringView(mp_data + startIndex, actualCount));
}

Bool Minty::String::starts_with(StringView const str) const noexcept
{
    for (Size i = 0; i < str.get_size(); ++i)
    {
        if (m_size < str.get_size() || mp_data[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

Bool Minty::String::ends_with(StringView const str) const noexcept
{
    for (Size i = 0; i < str.get_size(); ++i)
    {
        if (m_size < str.get_size() || mp_data[m_size - str.get_size() + i] != str[i])
        {
            return false;
        }
    }
    return true;
}
