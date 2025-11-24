#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	/// <summary>
	/// Represents a Raycast hit.
	/// </summary>
	struct RaycastHit
	{
		/// <summary>
		/// The position of the hit.
		/// </summary>
		Float3 point = Math::ZERO;

		/// <summary>
		/// The normal of the surface hit.
		/// </summary>
		Float3 normal = Math::UP;
		
		/// <summary>
		/// The distance from the ray's origin to the hit point.
		/// </summary>
		Float distance = 0.0f;
		
		/// <summary>
		/// The Entity that was hit.
		/// </summary>
		Entity entity = INVALID_ENTITY;
	};
}