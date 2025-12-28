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

void Minty::Transition::serialize(Writer& writer, String const& name) const
{

}

Bool Minty::Transition::deserialize(Reader& reader, Size const index)
{


	return true;
}

void Minty::ItemSerializer<Transition>::serialize_item(Writer &writer, StringView const name, Transition const &value)
{
	FSM const* fsm = static_cast<FSM const*>(writer.get_user_data());
	MINTY_ASSERT(fsm != nullptr, ErrorCode::InvalidUserData);

	String stateName = fsm->get_state_name(value.m_stateId);
	writer.write(name, stateName);
	writer.write(name, value.m_conditions);
}

void Minty::ItemSerializer<Transition>::deserialize_item(Reader &reader, Size const index, Transition &value)
{
		FSM* fsm = static_cast<FSM*>(reader.get_user_data());
	MINTY_ASSERT(fsm != nullptr, ErrorCode::InvalidUserData);

	String stateName;
	if (reader.read(index, stateName))
	{
		// name read successfully
		value.m_stateId = fsm->find_state(stateName);
	}
	reader.read(index, value.m_conditions);
}