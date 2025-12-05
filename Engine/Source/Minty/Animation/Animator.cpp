#include "pch.h"
#include "Animator.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/AnimatorInfo.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Debug/Assert.h"
#if defined(MINTY_DEBUG)
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#endif // MINTY_DEBUG

using namespace Minty;

Minty::Animator::Animator(AnimatorInfo const &info)
	: Asset(info.id), mp_fsm(nullptr), m_force(info.force)
{
	if (info.fsm)
	{
		mp_fsm = new FSM(*info.fsm);
	}
}

Minty::Animator::~Animator()
{
	delete mp_fsm;
}

void Minty::Animator::set_variable(String const &name, Int const value)
{
	UUID variableId = mp_fsm->find_variable(name);
	MINTY_ASSERT_F(variableId.is_valid(), ErrorCode::Argument_KeyNotFound, name);
	mp_fsm->set_variable(variableId, value);
}

Int Minty::Animator::get_variable(String const &name) const
{
	UUID variableId = mp_fsm->find_variable(name);
	MINTY_ASSERT_F(variableId.is_valid(), ErrorCode::Argument_KeyNotFound, name);
	return mp_fsm->get_variable(variableId);
}

UUID Minty::Animator::get_current_animation() const
{
	if (mp_fsm->has_current_state())
	{
		// yes animation
		return mp_fsm->get_current_state().get_value().get<UUID>();
	}

	// no animation
	return UUID();
}

UUID Minty::Animator::update(Ref<Animation> const &currentAnimation, Float const currentTime)
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
		Set<State const *> visitedStates;
		Vector<State const *> visitedStatesInOrder;
#endif // MINTY_DEBUG

		// if forcing, keep evaluating until no more transitions are possible
		do
		{
			result = mp_fsm->evaluate();
#if defined(MINTY_DEBUG)
			if (result && mp_fsm->has_current_state())
			{
				State const *const state = &mp_fsm->get_current_state();
				if (visitedStates.contains(state))
				{
					StringBuilder statesBuilder;
					for (State const *const visitedState : visitedStatesInOrder)
					{
						statesBuilder.append(visitedState->get_value().get<UUID>());
						statesBuilder.append(" -> ");
					}
					MINTY_ERROR_F(ErrorCode::InfiniteLoop, state->get_value().get<UUID>(), "->", statesBuilder.to_string());
					break; // break out of the loop to prevent infinite recursion
				}
				visitedStates.add(state);
				visitedStatesInOrder.add(state);
			}
#endif // MINTY_DEBUG
		} while (m_force && result);
	}

	// if no current state, return invalid ID
	if (!mp_fsm->has_current_state())
	{
		return UUID();
	}

	// get ID from the current state
	return mp_fsm->get_current_state().get_value().get<UUID>();
}

Shared<Animator> Minty::Animator::create(AnimatorInfo const &info)
{
	return Shared<Animator>::create(info);
}

Shared<Animator> Minty::Animator::create()
{
	AnimatorInfo info{};
	return create(info);
}
