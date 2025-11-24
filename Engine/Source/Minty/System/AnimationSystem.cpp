#include "pch.h"
#include "AnimationSystem.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/AnimatorComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Entity/EntityManager.h"

using namespace Minty;

void Minty::AnimationSystem::on_frame_update(Timestep const& time)
{
	MINTY_TRACE_SCOPE();

	Float deltaTime = time.get_elapsed();

	// get managers
	EntityManager& entityManager = m_scene->get_entity_manager();
	AssetManager& assetManager = AssetManager::get_singleton();

	// update all entities with an animator
	for (auto&& [entity, animatorComp, enabledComp] : entityManager.view<AnimatorComponent, EnabledComponent const>().each())
	{
		// update the animator
		Ref<Animation>& animation = animatorComp.animation;
		UUID currentId = animation == nullptr ? UUID(INVALID_ID) : animation->get_id();
		UUID newId = animatorComp.animator->update(animation, animatorComp.time);

		// if ID changed, reset animation data
		if (currentId != newId)
		{
			// reset animation
			if (animation != nullptr)
			{
				animation->reset(entity, entityManager);
			}

			// reset animator component
			animatorComp.animation = assetManager.get<Animation>(newId);
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
		// OR if the animation ID is INVALID_ID, do nothing
		if (animatorComp.time < 0.0f || !animatorComp.animation)
		{
			continue;
		}

		// animate with it
		animatorComp.animation->animate(animatorComp.time, deltaTime, entity, entityManager);

		// assuming something has changed that needs updating, so dirty the entity
		entityManager.dirty(entity);
	}
}
