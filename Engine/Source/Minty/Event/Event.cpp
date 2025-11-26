#include "Event.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

void Minty::Event::set_state(EventState const state)
{
    MINTY_ASSERT(state != EventState::Unhandled, ErrorCode::Argument_ExpectedNonDefault);
    m_state = state;
}