#pragma once
#include "Minty/Component/Component.h"
#include "Minty/UI/Canvas.h"

namespace Minty
{
	/// <summary>
	/// Holds the Canvas data for an Enitity.
	/// </summary>
	struct CanvasComponent
		: public Component
	{
		/// <summary>
		/// The Canvas data.
		/// </summary>
		Canvas canvas;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}