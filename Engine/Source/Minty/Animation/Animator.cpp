#include "pch.h"
#include "Animator.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/AnimatorInfo.h"
#include "Minty/FSM/FSM.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Component/AnimatorComponent.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Asset/AssetManager.h"
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

Minty::Animator::Animator(Animator const &other)
	: Asset(other.get_id()), mp_fsm(new FSM(*other.mp_fsm)), m_force(other.m_force)
{
}

Minty::Animator::~Animator()
{
	delete mp_fsm;
}

Animator &Minty::Animator::operator=(Animator const &other)
{
	if (this != &other)
	{
		// remove old FSM
		delete mp_fsm;
		// copy new FSM
		mp_fsm = new FSM(*other.mp_fsm);
		m_force = other.m_force;
	}
	return *this;
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
		State& currentState = mp_fsm->get_current_state();
		Variable const& value = currentState.get_value();
		UUID const animationId = value.get<UUID>();
		return animationId;
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
						UUID const& id = visitedState->get_value().get<UUID>();
						statesBuilder.append(Parser<UUID>::to_string(id));
						statesBuilder.append(" -> ");
					}
					UUID const& id = state->get_value().get<UUID>();
					MINTY_ERROR_F(ErrorCode::InfiniteLoop, id, "->", statesBuilder.get_string());
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

void Minty::Animator::flush(AnimatorComponent &animatorComp, Float const deltaTime, Entity const thisEntity, EntityManager &entityManager)
{
	// update the animator
	Ref<Animation> &animation = animatorComp.animation;
	UUID currentId = animation == nullptr ? UUID(UUID()) : animation->get_id();
	UUID newId = animatorComp.animator->update(animation, animatorComp.time);

	// if ID changed, reset animation data
	if (currentId != newId)
	{
		// reset animation
		if (animation != nullptr)
		{
			animation->reset(thisEntity, entityManager);
		}

		// reset animator component
		AssetManager &assetManager = AssetManager::get_singleton();
		animatorComp.animation = assetManager.get_ref<Animation>(newId);
		animatorComp.time = 0.0f;
	}
	else if (animation != nullptr && animatorComp.time >= animation->get_duration())
	{
		// if tried to change, and no change, and looping...
		if (animatorComp.animation->is_looping())
		{
			// reset the time to zero to start the animation over
			animatorComp.time = 0.0f;
		}
		else
		{
			// set to idle
			animatorComp.time = -1.0f;
		}
	}

	// if the animator time is below zero, then the animator has paused, so do nothing
	// OR if the animation null, do nothing
	if (animatorComp.time < 0.0f || !animatorComp.animation)
	{
		return;
	}

	// animate with it
	animatorComp.animation->animate(animatorComp.time, deltaTime, thisEntity, entityManager);

	// assuming something has changed that needs updating, so dirty the entity
	entityManager.dirty(thisEntity);
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
