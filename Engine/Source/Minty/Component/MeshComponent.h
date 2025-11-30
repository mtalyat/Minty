#ifndef MINTY_COMPONENT_MESHCOMPONENT_H
#define MINTY_COMPONENT_MESHCOMPONENT_H

/**
 * @file MeshComponent.h
 * @brief Header file defining the MeshComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Render/MeshType.h"

namespace Minty
{
	class Material;
	class Mesh;

	/**
	 * @brief Holds the Mesh and Material of an Entity.
	 */
	struct MeshComponent
		: public Component
	{
		MeshType type = MeshType::Empty;

		Ref<Mesh> mesh = nullptr;

		Ref<Material> material = nullptr;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_MESHCOMPONENT_H