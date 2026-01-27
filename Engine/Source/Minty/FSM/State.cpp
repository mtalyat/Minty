#include "pch.h"
#include "State.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::State::add_transition(Transition const& transition)
{
	m_transitions.add(transition);
}

UUID Minty::State::evaluate(Scope const& scope) const
{
	for (auto const& transition : m_transitions)
	{
		if (transition.evaluate(scope))
		{
			return transition.get_state_id();
		}
	}
	return UUID();
}

void Minty::Serializer<State>::serialize(Writer &writer, State const &value)
{
	writer.write("Value", value.m_value);
	writer.write("Transitions", value.m_transitions);
}

Bool Minty::Serializer<State>::deserialize(Reader &reader, State &value)
{
	reader.read("Value", value.m_value);
	reader.read("Transitions", value.m_transitions);
	return true;
}