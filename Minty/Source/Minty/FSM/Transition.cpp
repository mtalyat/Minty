#include "pch.h"
#include "Transition.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Transition::add_condition(Condition const& condition)
{
	m_conditions.add(condition);
}

Bool Minty::Transition::evaluate(BasicScope const& scope) const
{
	for (auto const& condition : m_conditions)
	{
		if (!condition.evaluate(scope))
		{
			return false;
		}
	}
	return true;
}

void Minty::Transition::serialize(Writer& writer) const
{
	FSM const* fsm = static_cast<FSM const*>(writer.get_user_data());
	MINTY_ASSERT(fsm != nullptr, "FSM is null.");

	String stateName = fsm->get_state_name(m_stateId);
	writer.write("State", stateName);
	writer.write("Conditions", m_conditions);
}

Bool Minty::Transition::deserialize(Reader& reader)
{
	FSM* fsm = static_cast<FSM*>(reader.get_user_data());
	MINTY_ASSERT(fsm != nullptr, "FSM is null.");

	String stateName;
	if (reader.read("State", stateName))
	{
		// name read successfully
		m_stateId = fsm->find_state(stateName);
	}
	reader.read("Conditions", m_conditions);

	return true;
}
