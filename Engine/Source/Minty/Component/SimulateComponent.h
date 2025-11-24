#pragma once
#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// Used to tag objects that should be controlled by the physics simulation.
	/// </summary>
	struct SimulateComponent
		: public Component
	{
	};
}