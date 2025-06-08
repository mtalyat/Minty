#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Physics/Collider.h"

namespace Minty
{
	/// <summary>
	/// Holds a Collider for an Entity.
	/// </summary>
	struct ColliderComponent
		: public Component
	{
		/// <summary>
		/// The Collider.
		/// </summary>
		Owner<Collider> collider;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}