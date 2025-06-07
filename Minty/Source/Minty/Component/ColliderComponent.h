#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Physics/Collider.h"

namespace Minty
{
	/// <summary>
	/// Holds a Collider for an Entity.
	/// </summary>
	struct ColliderComponent
		: public Component
	{
		Owner<Collider> collider;
	};
}