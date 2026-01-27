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

Bool Minty::Serializer<MeshComponent>::deserialize(Reader &reader, MeshComponent &value)
{
	// read type
	reader.read_primary("Type", value.type);

	// read mesh
	UUID meshId;
	if (reader.read("Mesh", meshId))
	{
		value.type = MeshType::Custom;

		AssetManager &assetManager = AssetManager::get_singleton();
		value.mesh = assetManager.get_ref<Mesh>(meshId);
	}
	else
	{
		// get default mesh
		RenderManager &renderManager = RenderManager::get_singleton();
		value.mesh = renderManager.get_default_mesh(value.type).to_ref();
	}

	// read material ID
	UUID materialId;
	if (reader.read("Material", materialId))
	{
		value.material = AssetManager::get_singleton().get_ref<Material>(materialId);
	}
	else
	{
		value.material = nullptr;
	}

	// MeshComponent requires both Mesh and Material to be set, or both to be null
	MINTY_CHECK((value.mesh != nullptr && value.material != nullptr) || (value.mesh == nullptr && value.material == nullptr), ErrorCode::Serialization_InvalidData);
	
	return true;
}
