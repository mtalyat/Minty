#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Core/Types.h"
#include "Minty/Core/Constant.h"

namespace Minty
{
	/// <summary>
	/// Holds the layer of an Entity.
	/// </summary>
	struct LayerComponent
		: public Component
	{
		Layer layer = LAYER_DEFAULT;
	};
}