#pragma once
#include "Minty/Library/Bullet.h"
#include "Platform/Bullet/Bullet_Collider.h"

namespace Minty
{
	class Bullet_MeshCollider
		: public Bullet_Collider
	{
#pragma region Constructors

	public:
		Bullet_MeshCollider(ColliderInfo const& info);

		~Bullet_MeshCollider() override
		{
		}

#pragma endregion
	};
}