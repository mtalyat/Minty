#include "pch.h"
#include "Transition.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Transition::Transition()
	: m_stateId(), m_conditions()
{
}

Minty::Transition::Transition(UUID const stateId, Vector<Condition> const &conditions)
	: m_stateId(stateId), m_conditions(conditions)
{
}

void Minty::Transition::add_condition(Condition const &condition)
{
	m_conditions.add(condition);
}

Bool Minty::Transition::evaluate(Scope const &scope) const
{
	for (auto const &condition : m_conditions)
	{
		if (!condition.evaluate(scope))
		{
			return false;
		}
	}
	return true;
}

void Minty::Serializer<Transition>::serialize(Writer &writer, Transition const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Transition>::deserialize(Reader &reader, Transition &value)
{
	FSM *fsm = static_cast<FSM *>(reader.get_user_data());
	MINTY_ASSERT(fsm != nullptr, ErrorCode::InvalidUserData);

	String stateName;
	if (reader.read_inline(stateName))
	{
		// name read successfully
		value.m_stateId = fsm->find_state(stateName);
		MINTY_CHECK_F(value.m_stateId.is_valid(), ErrorCode::Serialization_InvalidData, stateName); // state not found
	}
	else
	{
		MINTY_ERROR(ErrorCode::Serialization_MissingValue);
	}

	value.m_conditions.clear();
	String dummy;
	Condition condition;
	while (reader.read_next(dummy, condition))
	{
		value.m_conditions.add(condition);
	}
	return true;
}