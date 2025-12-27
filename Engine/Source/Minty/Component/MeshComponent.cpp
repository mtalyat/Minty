#include "pch.h"
#include "MeshComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<MeshComponent>::serialize(Writer &writer, MeshComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

void Minty::Serializer<MeshComponent>::deserialize(Reader &reader, MeshComponent &value)
{
	// read type
	if (!reader.read_default(value.type))
	{
		reader.read("Type", value.type, MeshType::Custom);
	}

	// read mesh ID
	if (value.type == MeshType::Custom)
	{
		UUID id = UUID();
		if (!reader.read("Mesh", id))
		{
			value.mesh = nullptr;
		}
		AssetManager &assetManager = AssetManager::get_singleton();
		value.mesh = assetManager.get_ref<Mesh>(id);
	}
	else
	{
		// get default mesh
		RenderManager &renderManager = RenderManager::get_singleton();
		value.mesh = renderManager.get_default_mesh(value.type).to_ref();
	}

	// read material ID
	UUID id = UUID();
	if (reader.read("Material", id))
	{
		value.material = AssetManager::get_singleton().get_ref<Material>(id);
	}
	else
	{
		value.material = nullptr;
	}

	MINTY_CHECK_F(value.mesh != nullptr, ErrorCode::Serialization_MissingRequired, "Mesh");
	MINTY_CHECK_F(value.material != nullptr, ErrorCode::Serialization_MissingRequired, "Material");
}
