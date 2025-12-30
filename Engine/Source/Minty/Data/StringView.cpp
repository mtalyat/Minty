#include "StringView.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Char Minty::StringView::index(Size const index) const
{
    MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfRange, index, m_size);
    return mp_data[index];
}

Bool Minty::StringView::starts_with(StringView const prefix) const noexcept
{
    for (Size i = 0; i < prefix.m_size; ++i)
    {
        if (i >= m_size || mp_data[i] != prefix.mp_data[i])
        {
            return false;
        }
    }
    return true;
}

Bool Minty::StringView::ends_with(StringView const suffix) const noexcept
{
    if (suffix.m_size > m_size)
    {
        return false;
    }

    Size const startIndex = m_size - suffix.m_size;
    for (Size i = 0; i < suffix.m_size; ++i)
    {
        if (mp_data[startIndex + i] != suffix.mp_data[i])
        {
            return false;
        }
    }
    return true;
}

StringView Minty::StringView::sub(Size const startIndex, Size const size) const noexcept
{
    MINTY_ASSERT_F(startIndex + size <= m_size, ErrorCode::Argument_OutOfRange, startIndex, m_size);
    return StringView(mp_data + startIndex, size);
}
