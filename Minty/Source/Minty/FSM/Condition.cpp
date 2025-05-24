#include "pch.h"
#include "Condition.h"
#include "Minty/Data/Scope.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Bool Minty::Condition::evaluate(BasicScope const& scope) const
{
	// get the variable value from the scope
	Int value = scope.get_value(m_variableId);

	// check the conditional
	return Minty::evaluate(value, m_conditional, m_value);
}

void Minty::Condition::serialize(Writer& writer, String const& name) const
{
    // get scope from user data
	FSM const* fsm = static_cast<FSM const*>(writer.get_user_data());
	MINTY_ASSERT(fsm != nullptr, "FSM is null.");
	BasicScope const& scope = fsm->get_scope();
	
    // get the variable name
	String const& variableName = scope.get_name(m_variableId);

	// compile into a string
	String conditionString = F("{} {} {}", variableName, Minty::to_string(m_conditional), m_value);

	// write the condition string
	writer.write(name, conditionString);
}

Bool Minty::Condition::deserialize(Reader& reader, Size const index)
{
	// read the condition string
	String conditionString;
	if (!reader.read(index, conditionString))
	{
		MINTY_ERROR(F("Failed to read condition string at index {}.", index));
		return false;
	}

	// split the condition string into parts
	Vector<String> parts = String::split(conditionString);
	MINTY_ASSERT(parts.get_size() == 3, "Condition string must have 3 parts, split by spaces.");

	// get the scope
	BasicScope* scope = static_cast<BasicScope*>(reader.get_user_data());

	// get the values
	m_variableId = scope->find(parts[0]);
	MINTY_ASSERT(m_variableId != INVALID_ID, F("No variable found with name {}.", parts[0]));
	m_conditional = parse_to_conditional(parts[1]);
	m_value = parse_to<Int>(parts[2]);

	return true;
}
