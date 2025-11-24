#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	/// <summary>
	/// Holds an ID value for an Entity.
	/// </summary>
	struct UUIDComponent
		: public Component
	{
		UUID id = INVALID_ID;
	};
}