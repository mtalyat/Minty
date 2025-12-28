#include "pch.h"
#include "Condition.h"
#include "Minty/Data/Scope.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Tool/Util.h"
#include "Minty/Core/Evaluate.h"

using namespace Minty;

Bool Minty::Condition::evaluate(Scope const& scope) const
{
	// get the variable value from the scope
	Int value = scope.get_value(m_variableId);

	// check the conditional
	return Minty::evaluate_conditional(value, m_conditional, m_value);
}

void Minty::ItemSerializer<Condition>::serialize_item(Writer &writer, StringView const name, Condition const &value)
{
	// get scope from user data
	FSM const* fsm = static_cast<FSM const*>(writer.get_user_data());
	MINTY_ASSERT(fsm != nullptr, ErrorCode::InvalidUserData);
	Scope const& scope = fsm->get_scope();
	
    // get the variable name
	String const& variableName = scope.get_name(value.m_variableId);

	// compile into a string
	String conditionString = F("{} {} {}", variableName, Minty::to_string(value.m_conditional), value.m_value);

	// write the condition string
	writer.write(name, conditionString);
}

void Minty::ItemSerializer<Condition>::deserialize_item(Reader &reader, Size const index, Condition &value)
{
	 // read the condition string
	String conditionString;
	Bool const readResult = reader.read(index, conditionString);
	MINTY_ASSERT(readResult, ErrorCode::Serialization_ReadValue);

	// split the condition string into parts
	Vector<String> parts = Util::split(conditionString);
	// "Condition string must have 3 parts, split by spaces."
	MINTY_ASSERT(parts.get_size() == 3, ErrorCode::Serialization_InvalidFormat);

	// get the scope
	FSM* fsm = static_cast<FSM*>(reader.get_user_data());
	MINTY_ASSERT(fsm != nullptr, ErrorCode::InvalidUserData);
	Scope& scope = fsm->get_scope();

	// get the values
	value.m_variableId = scope.find(parts[0]);
	MINTY_ASSERT_F(value.m_variableId != UUID(), ErrorCode::Serialization_InvalidData, parts[0]);
	value.m_conditional = parse_to_conditional(parts[1]);
	value.m_value = Math::evaluate<Int>(parts[2]);
}