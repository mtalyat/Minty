#ifndef MINTY_COMPONENT_NAMECOMPONENT_H
#define MINTY_COMPONENT_NAMECOMPONENT_H

/**
 * @file NameComponent.h
 * @brief Header file defining the NameComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/String.h"

namespace Minty
{
	/**
	 * @brief Holds the name of an Entity.
	 */
	struct NameComponent
		: public Component
	{
		String name = "";

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_NAMECOMPONENT_H