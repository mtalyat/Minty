#include "StringView.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Tool/String.h"

using namespace Minty;

Char Minty::StringView::index(Size const index) const
{
    MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfRange, index, m_size);
    return mp_data[index];
}

Size Minty::StringView::find_first(Char const c, Size const startIndex) const noexcept
{
    return Tool::find_first(mp_data, m_size, c, startIndex);
}

Size Minty::StringView::find_first(StringView const str, Size const startIndex) const noexcept
{
    return Tool::find_first(mp_data, m_size, str, startIndex);
}

Size Minty::StringView::find_last(Char const c, Size const startIndex) const noexcept
{
    return Tool::find_last(mp_data, m_size, c, startIndex);
}

Size Minty::StringView::find_last(StringView const str, Size const startIndex) const noexcept
{
    return Tool::find_last(mp_data, m_size, str, startIndex);
}

Size Minty::StringView::find_first_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_first_of(mp_data, m_size, chars, startIndex);
}

Size Minty::StringView::find_last_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_last_of(mp_data, m_size, chars, startIndex);
}

Size Minty::StringView::find_first_not_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_first_not_of(mp_data, m_size, chars, startIndex);
}

Size Minty::StringView::find_last_not_of(StringView const chars, Size const startIndex) const noexcept
{
    return Tool::find_last_not_of(mp_data, m_size, chars, startIndex);
}

Int Minty::StringView::compare(StringView const &other) const noexcept
{
    return Tool::compare(mp_data, m_size, other);
}

Bool Minty::StringView::starts_with(StringView const prefix) const noexcept
{
    return Tool::starts_with(mp_data, m_size, prefix);
}

Bool Minty::StringView::ends_with(StringView const suffix) const noexcept
{
    return Tool::ends_with(mp_data, m_size, suffix);
}

StringView Minty::StringView::sub(Size const startIndex, Size const size) const noexcept
{
    // if size is SIZE_MAX, return from startIndex to the end
    if(size == SIZE_MAX)
    {
        return StringView(mp_data + startIndex, m_size - startIndex);
    }

    // otherwise use the provided size
    // need to make two comparisons to avoid overflow
    MINTY_ASSERT_F(size <= m_size && startIndex + size <= m_size, ErrorCode::Argument_OutOfRange, startIndex, m_size);
    return StringView(mp_data + startIndex, size);
}
