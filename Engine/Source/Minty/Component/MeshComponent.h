#ifndef MINTY_COMPONENT_MESHCOMPONENT_H
#define MINTY_COMPONENT_MESHCOMPONENT_H

/**
 * @file MeshComponent.h
 * @brief Header file defining the MeshComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/MeshType.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/Material.h"

namespace Minty
{
	/**
	 * @brief Holds the Mesh and Material of an Entity.
	 */
	struct MeshComponent
		: public Component
	{
		/**
		 * @brief The type of mesh.
		 */
		MeshType type = MeshType::Empty;

		/**
		 * @brief The mesh of the entity.
		 */
		Ref<Mesh> mesh = nullptr;

		/**
		 * @brief The material of the entity.
		 */
		Ref<Material> material = nullptr;
	};

	template<>
	struct Serializer<MeshComponent>
	{
		static void serialize(Writer& writer, MeshComponent const& value);
		static void deserialize(Reader& reader, MeshComponent& value);
	};
}

#endif // MINTY_COMPONENT_MESHCOMPONENT_H