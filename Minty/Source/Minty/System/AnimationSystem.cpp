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
		// update the animator
		UUID newId = animatorComp.animator->update();
		Ref<Animation> newAnim = assetManager.get<Animation>(newId);

		// if ID changed, reset animation data
		if (animatorComp.animation != newAnim)
		{
			// reset animation
			if (animatorComp.animation != nullptr)
			{
				animatorComp.animation->reset(entity, entityManager);
			}

			// reset animator component
			animatorComp.animation = newAnim;
			animatorComp.time = 0.0f;
			animatorComp.index = 0;
		}

		// if the animator time is below zero, then the animator has paused, so do nothing
		// OR if the animation ID is ERROR_ID, do nothing
		if (animatorComp.time < 0.0f || !animatorComp.animation)
		{
			continue;
		}

		// animate with it
		if (animatorComp.animation->animate(animatorComp.time, deltaTime, animatorComp.index, entity, entityManager))
		{
			// animation has completed, loop if supposed to
			if (animatorComp.animation->is_looping())
			{
				// reset
				animatorComp.index = 0;
				animatorComp.time = 0.0f;
			}
			else
			{
				// not looping

				// set time to -1 to indicate that it has stopped, until a new animation ID is given
				animatorComp.time = -1.0f;
			}
		}

		// assuming something has changed that needs updating, so dirty the entity
		entityManager.dirty(entity);
	}
}
