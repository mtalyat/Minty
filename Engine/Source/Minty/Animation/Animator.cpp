#include "pch.h"
#include "Animator.h"
#include "Minty/Animation/Animation.h"
#if defined(MINTY_DEBUG)
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#endif // MINTY_DEBUG

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

UUID Minty::Animator::update(Ref<Animation> const& currentAnimation, Float const currentTime)
{
	// Perform update if:
	// 1. Force is true
	// 2. No current animation
	// 3. Animator is idling
	// 4. Animation has completed
	if (m_force || currentAnimation == nullptr || currentTime < 0.0f || currentTime >= currentAnimation->get_duration())
	{
		Bool result;

#if defined(MINTY_DEBUG)
		// if in debug, check for infinite loops
		Set<State const*> visitedStates;
		Vector<State const*> visitedStatesInOrder;
#endif // MINTY_DEBUG

		// if forcing, keep evaluating until no more transitions are possible
		do {
			result = m_fsm.evaluate();
#if defined(MINTY_DEBUG)
			if (result && m_fsm.has_current_state())
			{
				State const* const state = &m_fsm.get_current_state();
				if (visitedStates.contains(state))
				{
					String statesString = "";
					for (State const* const visitedState : visitedStatesInOrder)
					{
						statesString += F("{} -> ", visitedState->get_value().get<UUID>());
					}
					MINTY_ERROR(F("Infinite loop detected in Animator FSM. State ID: {}, States: {}", state->get_value().get<UUID>(), statesString));
					break; // break out of the loop to prevent infinite recursion
				}
				visitedStates.add(state);
				visitedStatesInOrder.add(state);
			}
#endif // MINTY_DEBUG
		} while (m_force && result);	
	}

	// if no current state, return invalid ID
	if (!m_fsm.has_current_state())
	{
		return INVALID_ID;
	}

	// get ID from the current state
	return m_fsm.get_current_state().get_value().get<UUID>();
}

Owner<Animator> Minty::Animator::create(AnimatorInfo const& info)
{
	return Owner<Animator>(info);
}
