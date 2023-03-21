#include "pch.h"
#include "M_S_TargetSystem.h"

#include "M_C_Target.h"
#include "M_C_Follow.h"
#include "M_C_Position.h"

#include "M_Math.h"
#include "M_Time.h"

void minty::TargetSystem::update()
{
	float deltaTime = Time::deltaTime();

	Position* targetPosition;
	float offsetX, offsetY;
	float l;

	// follows
	for (auto [entity, target, follow, position] : mp_registry->group<Target>(entt::get<Follow, Position>).each())
	{
		// if target exists and has a position, lerp to it
		targetPosition = mp_registry->try_get<Position>(target.target);

		// if no target position, do nothing
		if (!targetPosition)
		{
			continue;
		}

		l = follow.lerp * deltaTime;

		// get offsets
		offsetX = (targetPosition->x - follow.x) * l;
		offsetY = (targetPosition->y - follow.y) * l;

		// apply offsets to follow
		follow.x += offsetX;
		follow.y += offsetY;

		// move position
		position.x = (follow.x - targetPosition->x) * follow.lead + targetPosition->x;
		position.y = (follow.y - targetPosition->y) * follow.lead + targetPosition->y;
	}
}
