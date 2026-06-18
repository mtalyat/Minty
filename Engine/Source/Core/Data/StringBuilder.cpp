#include "pch.h"
#include "StringBuilder.h"
#include "Core/Debug/Debug.h"

using namespace Minty;

Minty::StringBuilder::StringBuilder()
    : mp_data(nullptr), m_size(0), m_capacity(0), m_allocator()
{
}

Minty::StringBuilder::StringBuilder(Size const initialCapacity)
    : mp_data(nullptr), m_size(0), m_capacity(0), m_allocator()
{
    reserve(initialCapacity);
}

Minty::StringBuilder::StringBuilder(StringView const& initialString)
    : mp_data(nullptr), m_size(0), m_capacity(0), m_allocator()
{
    reserve(initialString.get_size());
    append(initialString);
}

Minty::StringBuilder::~StringBuilder()
{
    if (mp_data)
    {
        m_allocator.deallocate(mp_data);
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
    Char *const newData = m_allocator.allocate<Char>(newCapacity + 1);
    MINTY_ASSERT(newData != nullptr, ErrorCodeEnum::Memory_AllocationFailed);
    if (mp_data)
    {
        std::memcpy(newData, mp_data, m_size * sizeof(Char));
        m_allocator.deallocate(mp_data);
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
        reserve(m_capacity == 0 ? DEFAULT_COLLECTION_SIZE : m_capacity * 2);
    }

    // Append character
    mp_data[m_size] = c;
    m_size++;
    mp_data[m_size] = '\0';
}

void Minty::StringBuilder::append(Char const *const cstr)
{
    // skip if null or empty
    if(cstr == nullptr || cstr[0] == '\0')
    {
        return;
    }

    append(StringView(cstr));
}

void Minty::StringBuilder::append(StringView const &str)
{
    // skip if empty
    if(str.get_size() == 0)
    {
        return;
    }

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


Char Minty::StringBuilder::index(Size const index) const
{
    MINTY_ASSERT_A(index < m_size, ErrorCodeEnum::Argument_OutOfRange, index);
    return mp_data[index];
}

Char const &Minty::StringBuilder::at(Size const index) const
{
    MINTY_ASSERT_A(index < m_size, ErrorCodeEnum::Argument_OutOfRange, index);
    return mp_data[index];
}

Int Minty::StringBuilder::compare(StringView const other) const noexcept
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

Size Minty::StringBuilder::find_first(Char const c, Size const startIndex) const noexcept
{
    for (Size i = startIndex; i < m_size; ++i)
    {
        if (mp_data[i] == c)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_first(StringView const str, Size const startIndex) const noexcept
{
    if (str.get_size() == 0 || str.get_size() > m_size)
    {
        return INVALID_SIZE;
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
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_last(Char const c, Size const startIndex) const noexcept
{
    Size start = (startIndex == INVALID_SIZE) ? m_size - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        if (mp_data[i] == c)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_last(StringView const str, Size const startIndex) const noexcept
{
    if (str.get_size() == 0 || str.get_size() > m_size)
    {
        return INVALID_SIZE;
    }

    Size start = (startIndex == INVALID_SIZE) ? m_size - str.get_size() : startIndex;
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
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_first_of(StringView const chars, Size const startIndex) const noexcept
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
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_last_of(StringView const chars, Size const startIndex) const noexcept
{
    Size start = (startIndex == INVALID_SIZE) ? m_size - 1 : startIndex;
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
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_first_not_of(StringView const chars, Size const startIndex) const noexcept
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
    return INVALID_SIZE;
}

Size Minty::StringBuilder::find_last_not_of(StringView const chars, Size const startIndex) const noexcept
{
    Size start = (startIndex == INVALID_SIZE) ? m_size - 1 : startIndex;
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
    return INVALID_SIZE;
}

String Minty::StringBuilder::sub(Size const startIndex, Size const count) const noexcept
{
    if (startIndex >= m_size)
    {
        return String();
    }

    Size actualCount = count;
    if (count == INVALID_SIZE || startIndex + count > m_size)
    {
        actualCount = m_size - startIndex;
    }

    return String(StringView(mp_data + startIndex, actualCount));
}

void Minty::StringBuilder::slice(Size const startIndex, Size const count) noexcept
{
    if (startIndex >= m_size)
    {
        clear();
        return;
    }

    Size actualCount = count;
    if (count == INVALID_SIZE || startIndex + count > m_size)
    {
        actualCount = m_size - startIndex;
    }

    if (startIndex > 0)
    {
        std::memmove(mp_data, mp_data + startIndex, actualCount * sizeof(Char));
    }
    m_size = actualCount;
    mp_data[m_size] = '\0';
}

Bool Minty::StringBuilder::starts_with(StringView const str) const noexcept
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

Bool Minty::StringBuilder::ends_with(StringView const str) const noexcept
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

void Minty::StringBuilder::to_lower()
{
    for (Size i = 0; i < m_size; ++i)
    {
        mp_data[i] = static_cast<Char>(std::tolower(mp_data[i]));
    }
}

void Minty::StringBuilder::to_upper()
{
    for (Size i = 0; i < m_size; ++i)
    {
        mp_data[i] = static_cast<Char>(std::toupper(mp_data[i]));
    }
}

void Minty::StringBuilder::trim_start(StringView const chars)
{
    Size startIndex = 0;
    while (startIndex < m_size)
    {
        Bool found = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[startIndex] == chars[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            break;
        }
        startIndex++;
    }
    if (startIndex > 0)
    {
        Size newSize = m_size - startIndex;
        std::memmove(mp_data, mp_data + startIndex, newSize * sizeof(Char));
        m_size = newSize;
        mp_data[m_size] = '\0';
    }
}

void Minty::StringBuilder::trim_end(StringView const chars)
{
    Size endIndex = m_size;
    while (endIndex > 0)
    {
        Bool found = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[endIndex - 1] == chars[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            break;
        }
        endIndex--;
    }
    if (endIndex < m_size)
    {
        m_size = endIndex;
        mp_data[m_size] = '\0';
    }
}

void Minty::StringBuilder::trim(StringView const chars)
{
    trim_start(chars);
    trim_end(chars);
}

void Minty::StringBuilder::strip(StringView const chars)
{
    Size writeIndex = 0;
    for (Size readIndex = 0; readIndex < m_size; ++readIndex)
    {
        Bool toStrip = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (mp_data[readIndex] == chars[j])
            {
                toStrip = true;
                break;
            }
        }
        if (!toStrip)
        {
            mp_data[writeIndex] = mp_data[readIndex];
            writeIndex++;
        }
    }
    m_size = writeIndex;
    mp_data[m_size] = '\0';
}

void Minty::StringBuilder::replace(StringView const target, StringView const replacement)
{
    MINTY_NOT_IMPLEMENTED();
}

void Minty::StringBuilder::reverse() noexcept
{
    Size const halfSize = m_size / 2;
    Size const sizeMinusOne = m_size - 1;
    for (Size i = 0; i < halfSize; ++i)
    {
        Char temp = mp_data[i];
        mp_data[i] = mp_data[sizeMinusOne - i];
        mp_data[sizeMinusOne - i] = temp;
    }
}
