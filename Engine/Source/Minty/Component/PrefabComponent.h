#ifndef MINTY_COMPONENT_PREFABCOMPONENT_H
#define MINTY_COMPONENT_PREFABCOMPONENT_H

/**
 * @file PrefabComponent.h
 * @brief Header file defining the PrefabComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Entity/Prefab.h"

namespace Minty
{
	/**
	 * @brief Holds the ID of the Prefab that the Entity was instantiated from.
	 */
	struct PrefabComponent
		: public Component
	{
		Ref<Prefab> prefab = nullptr;
	};

	template<>
	struct Serializer<PrefabComponent>
	{
		static void serialize(Writer& writer, PrefabComponent const& value);
		static void deserialize(Reader& reader, PrefabComponent& value);
	};
}

#endif // MINTY_COMPONENT_PREFABCOMPONENT_H