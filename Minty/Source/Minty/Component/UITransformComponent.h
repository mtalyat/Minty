#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/UITransform.h"

namespace Minty
{
	/// <summary>
	/// A component that holds the UI transform data.
	/// </summary>
	struct UITransformComponent
		: public Component
	{
		/// <summary>
		/// The Entity with a Canvas component that this UITransformComponent belongs to.
		/// </summary>
		Entity canvas;

		/// <summary>
		/// The UITransform data.
		/// </summary>
		UITransform transform;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}