#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	/// <summary>
	/// Holds the ID of the Prefab that the Entity was instantiated from.
	/// </summary>
	struct PrefabComponent
		: public Component
	{
		UUID id;
	};
}