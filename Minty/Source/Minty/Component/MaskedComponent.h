#pragma once

#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// A component that is masked by another component.
	/// </summary>
	struct MaskedComponent
		: public Component
	{
		UInt value = 0;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}