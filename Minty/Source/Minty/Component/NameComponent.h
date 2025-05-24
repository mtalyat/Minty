#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Data/String.h"

namespace Minty
{
	/// <summary>
	/// Holds a name for an Entity.
	/// </summary>
	struct NameComponent
		: public Component
	{
		String name = "";

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}