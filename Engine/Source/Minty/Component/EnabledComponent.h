#pragma once
#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// If an Entity has this component, it is enabled.
	/// </summary>
	struct EnabledComponent
		: public Component
	{
	};
}