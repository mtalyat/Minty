#include "pch.hpp"
#include "MeshComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Render/Manager/RenderManager.hpp"

using namespace Minty;

void Minty::Serializer<MeshComponent>::serialize(Writer &writer, MeshComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<MeshComponent>::deserialize(Reader &reader, MeshComponent &value)
{
	// Get the resource manager
	ResourceManager& resourceManager = ResourceManager::get_instance();

	// Get the handle for the mesh
	MeshResourceHandle meshResourceHandle = INVALID_HANDLE;
	resourceManager.deserialize(reader, "Mesh", meshResourceHandle);

	// Get the handle for the material
	MaterialResourceHandle materialResourceHandle = INVALID_HANDLE;
	resourceManager.deserialize(reader, "Material", materialResourceHandle);

	// If one of the handles is invalid, both must be invalid
	if((meshResourceHandle == INVALID_HANDLE) != (materialResourceHandle == INVALID_HANDLE))
	{
		MINTY_ERROR(ErrorCodeEnum::Resource_LoadFailed);
		return false;
	}

	// If both are invalid, return early
	if(meshResourceHandle == INVALID_HANDLE)
	{
		return true;
	}

	// Get the runtime objects for the mesh and material
	RenderManager& renderManager = RenderManager::get_instance();
	GeometryHandle const geometryHandle = renderManager.create(meshResourceHandle);
	MaterialHandle const materialHandle = renderManager.create(materialResourceHandle);

	// Update the MeshComponent with the handles
	value.mesh = geometryHandle;
	value.material = materialHandle;

	return true;
}
