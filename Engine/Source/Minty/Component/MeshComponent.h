#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/Mesh.h"

namespace Minty
{
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