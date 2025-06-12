#include "pch.h"
#include "MeshComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::MeshComponent::serialize(Writer& writer) const
{
	writer.write("Type", type);

	// if type is custom, print the mesh ID
	if (type == MeshType::Custom)
	{
		if (mesh != nullptr)
		{
			writer.write("Mesh", mesh->get_id());
		}
		else
		{
			writer.write("Mesh", INVALID_ID);
		}
	}

	if (material != nullptr)
	{
		writer.write("Material", material->get_id());
	}
	else
	{
		writer.write("Material", INVALID_ID);
	}
}

Bool Minty::MeshComponent::deserialize(Reader& reader)
{
	// read type
	reader.read_default(type);
	reader.read("Type", type, MeshType::Custom);

	// read mesh ID
	if (type == MeshType::Custom)
	{
		UUID id = INVALID_ID;
		if (!reader.read("Mesh", id))
		{
			mesh = nullptr;
		}
		AssetManager& assetManager = AssetManager::get_singleton();
		mesh = assetManager.get<Mesh>(id);
	}
	else
	{
		// get default mesh
		RenderManager& renderManager = RenderManager::get_singleton();
		mesh = renderManager.get_default_mesh(type);
	}

	// read material ID
	UUID id = INVALID_ID;
	if (reader.read("Material", id))
	{
		material = AssetManager::get_singleton().get<Material>(id);
	}
	else
	{
		material = nullptr;
	}
	return true;
}
