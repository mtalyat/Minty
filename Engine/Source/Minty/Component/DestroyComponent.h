#pragma once
#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// Marks an Entity for destruction.
	/// </summary>
	struct DestroyComponent
		: public Component
	{
	};
}