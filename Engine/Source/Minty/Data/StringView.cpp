#include "StringView.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Char Minty::StringView::index(Size const index) const
{
    MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfRange, index, m_size);
    return mp_data[index];
}

StringView Minty::StringView::sub(Size const startIndex, Size const size) const noexcept
{
    MINTY_ASSERT_F(startIndex + size <= m_size, ErrorCode::Argument_OutOfRange, startIndex, m_size);
    return StringView(mp_data + startIndex, size);
}
