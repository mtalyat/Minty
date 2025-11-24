#pragma once

#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// A component that holds a mask value.
	/// </summary>
	struct MaskComponent
		: public Component
	{
		UInt value = 0;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}