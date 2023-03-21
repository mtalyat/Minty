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
	PointF targetPos;
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

		targetPos = targetPosition->toPointF();

		l = follow.lerp * deltaTime;

		// get offsets
		offsetX = (targetPos.x - follow.x) * l;
		offsetY = (targetPos.y - follow.y) * l;

		// apply offsets to follow
		follow.x += offsetX;
		follow.y += offsetY;

		// move position
		position.x = (follow.x - targetPos.x) * follow.lead + targetPos.x;
		position.y = (follow.y - targetPos.y) * follow.lead + targetPos.y;
	}
}
