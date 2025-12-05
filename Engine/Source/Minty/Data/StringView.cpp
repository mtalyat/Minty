#include "StringView.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

Char Minty::StringView::index(Size const index) const
{
    MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfRange, index, m_size);
    return mp_data[index];
}