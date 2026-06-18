#include "pch.h"
#include "MaterialResource.h"
#include "Resource/Manager/ResourceManager.h"

using namespace Minty;

Bool Minty::Serializer<MaterialResource>::serialize(Writer &writer, MaterialResource const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<MaterialResource>::deserialize(Reader &reader, MaterialResource &value)
{
	// Data to load
	PipelineResourceHandle pipeline = value.pipeline;
	Cargo cargo = {};
	UInt stencil = value.stencil;

	// Load pipeline
	ResourceManager &resourceManager = ResourceManager::get_instance();
	pipeline = resourceManager.read<PipelineResource>(reader, "Pipeline");
	if (pipeline == INVALID_HANDLE)
	{
		MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, "Pipeline");
		return false;
	}

	// Load the other data
	reader.read("Data", cargo);
	reader.read("Stencil", stencil);

	// Set the loaded data to the resource
	value.pipeline = pipeline;
	value.cargo = std::move(cargo);
	value.stencil = stencil;
	return true;
}
