#include "pch.h"
#include "M_S_TargetSystem.h"

#include "M_C_Target.h"
#include "M_C_Position.h"

#include "M_Math.h"

void minty::TargetSystem::update()
{
	auto group = mp_registry->group<Target>(entt::get<Position>);

	Position* targetPosition;

	for (auto [entity, target, position] : group.each())
	{
		// if target exists and has a position, lerp to it
		targetPosition = mp_registry->try_get<Position>(target.target);

		if (!targetPosition)
		{
			continue;
		}

		// lerp
		position.x = math_lerp(position.x, targetPosition->x, target.lerp);
		position.y = math_lerp(position.y, targetPosition->y, target.lerp);
	}
}
