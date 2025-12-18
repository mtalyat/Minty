#include "pch.h"
#include "MeshComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/Mesh.h"
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
			writer.write("Mesh", UUID());
		}
	}

	if (material != nullptr)
	{
		writer.write("Material", material->get_id());
	}
	else
	{
		writer.write("Material", UUID());
	}
}

Bool Minty::MeshComponent::deserialize(Reader& reader)
{
	// read type
	if (!reader.read_default(type))
	{
		reader.read("Type", type, MeshType::Custom);
	}

	// read mesh ID
	if (type == MeshType::Custom)
	{
		UUID id = UUID();
		if (!reader.read("Mesh", id))
		{
			mesh = nullptr;
		}
		AssetManager& assetManager = AssetManager::get_singleton();
		mesh = assetManager.get_ref<Mesh>(id);
	}
	else
	{
		// get default mesh
		RenderManager& renderManager = RenderManager::get_singleton();
		mesh = renderManager.get_default_mesh(type).to_ref();
	}

	// read material ID
	UUID id = UUID();
	if (reader.read("Material", id))
	{
		material = AssetManager::get_singleton().get_ref<Material>(id);
	}
	else
	{
		material = nullptr;
	}
	if(mesh == nullptr)
	{
		MINTY_ERROR_F(ErrorCode::Serialization_MissingRequired, "Mesh");
		return false;
	}
	if(material == nullptr)
	{
		MINTY_ERROR_F(ErrorCode::Serialization_MissingRequired, "Material");
		return false;
	}
	return true;
}
