#pragma once
#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// If an Entity has this component, it is dirty.
	/// </summary>
	struct DirtyComponent
		: public Component
	{
	};
}