#include "pch.hpp"
#include "MaterialResource.hpp"
#include "Resource/Manager/ResourceManager.hpp"

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
	if (!resourceManager.read<PipelineResource>(reader, "Pipeline", pipeline))
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
