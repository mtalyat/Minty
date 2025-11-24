#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/Transform.h"

namespace Minty
{
	/// <summary>
	/// Holds the transform of an Entity.
	/// </summary>
	struct TransformComponent
		: public Component
	{
		Transform transform;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}