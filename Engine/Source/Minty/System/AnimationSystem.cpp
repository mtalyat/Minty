#include "pch.h"
#include "AnimationSystem.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/AnimatorComponent.h"
#include "Minty/Component/EnabledTag.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/FSM/FSM.h"

using namespace Minty;

void Minty::AnimationSystem::on_frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	Float const deltaTime = time.get_elapsed();
	EntityManager &entityManager = m_scene->get_entity_manager();

	// update all entities with an animator
	for (auto &&[entity, animatorComp] : entityManager.view<AnimatorComponent, EnabledTag const>().each())
	{
		animatorComp.animator->flush(animatorComp, deltaTime, entity, entityManager);
	}
}
