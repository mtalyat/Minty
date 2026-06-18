#include "StringView.h"
#include "Core/Debug/DebugF.h"
#include "Core/Tool/String.h"

using namespace Minty;

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
