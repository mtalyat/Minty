#include "pch.h"
#include "MeshComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::MeshComponent::serialize(Writer& writer) const
{
	writer.write("type", type);

	// if type is custom, print the mesh ID
	if (type == MeshType::Custom)
	{
		if (mesh != nullptr)
		{
			writer.write("mesh", mesh->get_id());
		}
		else
		{
			writer.write("mesh", INVALID_ID);
		}
	}

	if (material != nullptr)
	{
		writer.write("material", material->get_id());
	}
	else
	{
		writer.write("material", INVALID_ID);
	}
}

Bool Minty::MeshComponent::deserialize(Reader& reader)
{
	// read type
	if (!reader.read("type", type))
	{
		return false;
	}

	

	// read mesh ID
	if (type == MeshType::Custom)
	{
		UUID id = INVALID_ID;
		if (!reader.read("mesh", id))
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
	if (!reader.read("material", id))
	{
		material = nullptr;
	}
	material = AssetManager::get_singleton().get<Material>(id);
	return true;
}
