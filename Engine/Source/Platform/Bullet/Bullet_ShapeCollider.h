#pragma once
#include "Minty/Library/Bullet.h"
#include "Platform/Bullet/Bullet_Collider.h"

namespace Minty
{
	class Bullet_ShapeCollider
		: public Bullet_Collider
	{
#pragma region Constructors

	public:
		Bullet_ShapeCollider(ColliderInfo const& info);

		~Bullet_ShapeCollider() override
		{
		}

#pragma endregion
	};
}