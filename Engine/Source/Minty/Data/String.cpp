#include "String.h"
#include "Minty/Memory/HeapAllocator.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Tool/String.h"
#include "Minty/Core/Constant.h"

using namespace Minty;

static constexpr Char *EMPTY_STRING = const_cast<Char *>("");

Minty::String::String()
    : mp_data(nullptr), m_size(0), m_allocator()
{
    mp_data = EMPTY_STRING;
}

Minty::String::String(StringView const view)
    : mp_data(nullptr), m_size(view.get_size()), m_allocator()
{
    if (view.get_size() == 0)
    {
        mp_data = EMPTY_STRING;
        return;
    }

    mp_data = static_cast<Char *>(m_allocator.allocate(sizeof(Char) * (m_size + 1)));
    MINTY_ASSERT_F(mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_size + 1));
    memcpy(mp_data, view.get_data(), sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(Char const *const cstr)
    : mp_data(nullptr), m_size(std::char_traits<Char>::length(cstr)), m_allocator()
{
    if (m_size == 0)
    {
        mp_data = EMPTY_STRING;
        return;
    }

    mp_data = static_cast<Char *>(m_allocator.allocate(sizeof(Char) * (m_size + 1)));
    MINTY_ASSERT_F(mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_size + 1));
    memcpy(mp_data, cstr, sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(Char const c, Size const count)
    : mp_data(nullptr), m_size(count), m_allocator()
{
    if (m_size == 0)
    {
        mp_data = EMPTY_STRING;
        return;
    }

    mp_data = static_cast<Char *>(m_allocator.allocate(sizeof(Char) * (m_size + 1)));
    MINTY_ASSERT_F(mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_size + 1));
    memset(mp_data, c, sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(String const &other)
    : mp_data(nullptr), m_size(other.m_size), m_allocator()
{
    if (m_size == 0)
    {
        mp_data = EMPTY_STRING;
        return;
    }

    mp_data = static_cast<Char *>(m_allocator.allocate(sizeof(Char) * (m_size + 1)));
    MINTY_ASSERT_F(mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_size + 1));
    memcpy(mp_data, other.mp_data, sizeof(Char) * m_size);
    mp_data[m_size] = '\0';
}

Minty::String::String(String &&other) noexcept
    : mp_data(other.mp_data), m_size(other.m_size), m_allocator(std::move(other.m_allocator))
{
    other.mp_data = nullptr;
    other.m_size = 0;
}

Minty::String::~String()
{
    if (!is_empty())
    {
        m_allocator.deallocate(mp_data);
    }
}

String &Minty::String::operator=(String const &other)
{
    if (this != &other)
    {
        // deallocate current data
        if (!is_empty())
        {
            m_allocator.deallocate(mp_data);
        }

        // copy data from other
        m_allocator = DefaultAllocator();
        m_size = other.m_size;
        if (m_size == 0)
        {
            mp_data = EMPTY_STRING;
        }
        else
        {
            mp_data = static_cast<Char *>(m_allocator.allocate(sizeof(Char) * (m_size + 1)));
            MINTY_ASSERT_F(mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (m_size + 1));
            memcpy(mp_data, other.mp_data, sizeof(Char) * m_size);
            mp_data[m_size] = '\0';
        }
    }
    return *this;
}

String &Minty::String::operator=(String &&other) noexcept
{
    if (this != &other)
    {
        // deallocate current data
        if (!is_empty())
        {
            m_allocator.deallocate(mp_data);
        }

        // move data from other
        mp_data = other.mp_data;
        m_size = other.m_size;
        m_allocator = std::move(other.m_allocator);
        other.mp_data = nullptr;
        other.m_size = 0;
    }
    return *this;
}

String Minty::String::operator+(StringView const other) const
{
    String result;
    result.m_size = m_size + other.get_size();
    result.mp_data = static_cast<Char *>(result.m_allocator.allocate(sizeof(Char) * (result.m_size + 1)));
    MINTY_ASSERT_F(result.mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (result.m_size + 1));
    memcpy(result.mp_data, mp_data, sizeof(Char) * m_size);
    memcpy(result.mp_data + m_size, other.get_data(), sizeof(Char) * other.get_size());
    result.mp_data[result.m_size] = '\0';
    return result;
}

StringView Minty::String::get_view(Size const startIndex, Size const count) const noexcept
{
    if (startIndex >= m_size)
    {
        return StringView();
    }

    Size actualCount = count;
    if (count == INVALID_INDEX || startIndex + count > m_size)
    {
        actualCount = m_size - startIndex;
    }

    return StringView(mp_data + startIndex, actualCount);
}

Char Minty::String::index(Size const index) const
{
    MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfRange, index);
    return mp_data[index];
}

Char const &Minty::String::at(Size const index) const
{
    MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfRange, index);
    return mp_data[index];
}

Int Minty::String::compare(StringView const other) const noexcept
{
    return Tool::compare(mp_data, m_size, other);
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
    return Tool::find_first(mp_data, m_size, str, startIndex);
}

Size Minty::String::find_last(Char const c, Size const startIndex) const noexcept
{
    return Tool::find_last(mp_data, m_size, c, startIndex);
}

Size Minty::String::find_last(StringView const str, Size const startIndex) const noexcept
{
    return Tool::find_last(mp_data, m_size, str, startIndex);
}

Size Minty::String::find_first_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_first_of(mp_data, m_size, chars, startIndex);
}

Size Minty::String::find_last_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_last_of(mp_data, m_size, chars, startIndex);
}

Size Minty::String::find_first_not_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_first_not_of(mp_data, m_size, chars, startIndex);
}

Size Minty::String::find_last_not_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_last_not_of(mp_data, m_size, chars, startIndex);
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
    return Tool::starts_with(mp_data, m_size, str);
}

Bool Minty::String::ends_with(StringView const str) const noexcept
{
    return Tool::ends_with(mp_data, m_size, str);
}

String Minty::String::to_lower() const
{
    String result('\0', m_size);
    for (Size i = 0; i < m_size; ++i)
    {
        result.mp_data[i] = static_cast<Char>(std::tolower(mp_data[i]));
    }
    return result;
}

String Minty::String::to_upper() const
{
    String result('\0', m_size);
    for (Size i = 0; i < m_size; ++i)
    {
        result.mp_data[i] = static_cast<Char>(std::toupper(mp_data[i]));
    }
    return result;
}

String Minty::String::trim_start(StringView const chars) const
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
    return sub(startIndex, INVALID_INDEX);
}

String Minty::String::trim_end(StringView const chars) const
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
    return sub(0, endIndex);
}

String Minty::String::trim(StringView const chars) const
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
    Size endIndex = m_size;
    while (endIndex > startIndex)
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
    return sub(startIndex, endIndex - startIndex);
}

String Minty::String::strip(StringView const chars) const
{
    String result;
    result.m_size = m_size;
    result.mp_data = static_cast<Char *>(result.m_allocator.allocate(sizeof(Char) * (result.m_size + 1)));
    MINTY_ASSERT_F(result.mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (result.m_size + 1));

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
            result.mp_data[writeIndex] = mp_data[readIndex];
            writeIndex++;
        }
    }
    result.m_size = writeIndex;
    result.mp_data[result.m_size] = '\0';
    return result;
}

String Minty::String::replace(Char const oldChar, Char const newChar) const
{
    String result;
    result.m_size = m_size;
    result.mp_data = static_cast<Char *>(result.m_allocator.allocate(sizeof(Char) * (result.m_size + 1)));
    MINTY_ASSERT_F(result.mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (result.m_size + 1));

    for (Size i = 0; i < m_size; ++i)
    {
        if (mp_data[i] == oldChar)
        {
            result.mp_data[i] = newChar;
        }
        else
        {
            result.mp_data[i] = mp_data[i];
        }
    }
    result.mp_data[result.m_size] = '\0';
    return result;
}

String Minty::String::replace(StringView const oldStr, StringView const newStr) const
{
    if (oldStr.get_size() == 0)
    {
        return *this;
    }

    // First, count occurrences of oldStr
    Size count = 0;
    Size index = 0;
    while (index < m_size)
    {
        Size foundIndex = find_first(oldStr, index);
        if (foundIndex == INVALID_INDEX)
        {
            break;
        }
        count++;
        index = foundIndex + oldStr.get_size();
    }

    // Calculate new size
    Size newSize = m_size + count * (newStr.get_size() - oldStr.get_size());
    String result;
    result.m_size = newSize;
    result.mp_data = static_cast<Char *>(result.m_allocator.allocate(sizeof(Char) * (result.m_size + 1)));
    MINTY_ASSERT_F(result.mp_data != nullptr, ErrorCode::Memory_AllocationFailed, sizeof(Char) * (result.m_size + 1));

    // Perform replacement
    Size readIndex = 0;
    Size writeIndex = 0;
    while (readIndex < m_size)
    {
        Size foundIndex = find_first(oldStr, readIndex);
        if (foundIndex == INVALID_INDEX)
        {
            // Copy remaining characters
            while (readIndex < m_size)
            {
                result.mp_data[writeIndex++] = mp_data[readIndex++];
            }
            break;
        }

        // Copy characters before found substring
        while (readIndex < foundIndex)
        {
            result.mp_data[writeIndex++] = mp_data[readIndex++];
        }

        // Copy new substring
        for (Size j = 0; j < newStr.get_size(); ++j)
        {
            result.mp_data[writeIndex++] = newStr[j];
        }

        readIndex += oldStr.get_size();
    }

    result.mp_data[result.m_size] = '\0';
    return result;
}
