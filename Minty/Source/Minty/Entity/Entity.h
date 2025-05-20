#pragma once
#include "Minty/Library/EnTT.h"

namespace Minty
{
	/// <summary>
	/// An entity is a unique identifier for an object in the world.
	/// </summary>
	using Entity = entt::entity;

	/// <summary>
	/// An invalid entity.
	/// </summary>
	constexpr Entity INVALID_ENTITY = entt::null;
}