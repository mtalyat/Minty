#include "pch.h"
#include "M_S_AnimationSystem.h"

#include "M_Debug.h"

#include "M_C_Animator.h"
#include "M_C_SpriteRenderer.h"

namespace minty
{
	bool AnimationSystem::emplace(entt::entity const entity)
	{
		Animator* animator = mp_registry->try_get<Animator>(entity);

		if (!animator)
		{
			return false;
		}

		return System::emplace(entity);
	}

	void AnimationSystem::update()
	{
		for (auto [entity, renderer, animator] : mp_registry->view<SpriteRenderer, Animator>().each())
		{
			renderer.sprite = animator.update();
		}
	}
}
