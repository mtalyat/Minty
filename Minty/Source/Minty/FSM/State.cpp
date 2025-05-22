#include "pch.h"
#include "State.h"

using namespace Minty;

void Minty::State::add_transition(Transition const& transition)
{
	m_transitions.add(transition);
}

UUID Minty::State::evaluate(BasicScope const& scope) const
{
	for (auto const& transition : m_transitions)
	{
		if (transition.evaluate(scope))
		{
			return transition.get_state_id();
		}
	}
	return INVALID_ID;
}

void Minty::State::serialize(Writer& writer) const
{
}

Bool Minty::State::deserialize(Reader& reader)
{
    return Bool();
}
