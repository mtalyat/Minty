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

Bool Minty::Transition::evaluate(Scope const& scope) const
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

void Minty::ItemSerializer<Transition>::serialize_item(Writer &writer, StringView const name, Transition const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

void Minty::ItemSerializer<Transition>::deserialize_item(Reader &reader, StringView const name, Transition &value)
{
	FSM* fsm = static_cast<FSM*>(reader.get_user_data());
	MINTY_ASSERT(fsm != nullptr, ErrorCode::InvalidUserData);

	String stateName;
	if (reader.read(name, stateName))
	{
		// name read successfully
		value.m_stateId = fsm->find_state(stateName);
	}
	reader.read(name, value.m_conditions);
}