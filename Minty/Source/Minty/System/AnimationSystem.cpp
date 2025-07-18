#include "pch.h"
#include "AnimationSystem.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/AnimatorComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Entity/EntityManager.h"

using namespace Minty;

void Minty::AnimationSystem::on_update(Time const& time)
{
	Float deltaTime = time.get_elapsed();

	// get managers
	EntityManager& entityManager = m_scene->get_entity_manager();
	AssetManager& assetManager = AssetManager::get_singleton();

	// update all entities with an animator
	for (auto&& [entity, animatorComp, enabledComp] : entityManager.view<AnimatorComponent, EnabledComponent const>().each())
	{
		// if the animator is forcing, or the animation is not running/done, then update the animator
		Animator& animator = *animatorComp.animator;
		Ref<Animation> const& animation = animatorComp.animation;
		Bool const updateAnimator = animator.get_force() || animatorComp.time < 0.0f || animation == nullptr || animatorComp.time >= animation->get_duration();

		// update the animator
		UUID newId;
		if (updateAnimator)
		{
			newId = animatorComp.animator->update();
		}
		else if (animation != nullptr)
		{
			newId = animation->get_id();
		}

		// if ID changed, reset animation data
		if (animatorComp.animation->get_id() != newId)
		{
			// reset animation
			if (animatorComp.animation != nullptr)
			{
				animatorComp.animation->reset(entity, entityManager);
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
		// OR if the animation ID is ERROR_ID, do nothing
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
