#pragma once

/**
 * @file PrefabComponent.h
 * @brief Header file defining the PrefabComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Pointer.h"
#include "Minty/Entity/Prefab.h"

namespace Minty
{
	/**
	 * @brief Holds the ID of the Prefab that the Entity was instantiated from.
	 */
	struct PrefabComponent	
	{
		Ref<Prefab> prefab = nullptr;
	};

	template<>
	struct Serializer<PrefabComponent>
	{
		static Bool serialize(Writer& writer, PrefabComponent const& value);
		static Bool deserialize(Reader& reader, PrefabComponent& value);
	};
}
