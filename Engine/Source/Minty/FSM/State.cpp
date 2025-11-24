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
	writer.write("Value", m_value);
	writer.write("Transitions", m_transitions);
}

Bool Minty::State::deserialize(Reader& reader)
{
	reader.read("Value", m_value);
	reader.read("Transitions", m_transitions);

	return true;
}
