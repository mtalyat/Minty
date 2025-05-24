#include "pch.h"
#include "Animator.h"

using namespace Minty;

void Minty::Animator::set_variable(String const& name, Int const value)
{
	UUID variableId = m_fsm.find_variable(name);
	MINTY_ASSERT(variableId.is_valid(), F("Variable {} not found in Animator FSM.", name));
	m_fsm.set_variable(variableId, value);
}

Int Minty::Animator::get_variable(String const& name) const
{
	UUID variableId = m_fsm.find_variable(name);
	MINTY_ASSERT(variableId.is_valid(), F("Variable {} not found in Animator FSM.", name));
	return m_fsm.get_variable(variableId);
}

UUID Minty::Animator::get_current_animation() const
{
	if (m_fsm.has_current_state())
	{
		// yes animation
		return m_fsm.get_current_state().get_value().get<UUID>();
	}

	// no animation
	return INVALID_ID;
}

UUID Minty::Animator::update()
{
	m_fsm.evaluate();

	if (!m_fsm.has_current_state())
	{
		// no current state
		return INVALID_ID;
	}

	// get ID from the current state
	return m_fsm.get_current_state().get_value().get<UUID>();
}

Owner<Animator> Minty::Animator::create(AnimatorBuilder const& builder)
{
	return Owner<Animator>(builder);
}
