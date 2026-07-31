#include "pch.hpp"
#include "CameraComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Render/RenderView/RenderViewInfo.hpp"
#include "Render/Manager/RenderManager.hpp"

using namespace Minty;

void Minty::Serializer<CameraComponent>::serialize(Writer &writer, CameraComponent const &value)
{
	// Render view has runtime-only information currently, so ignore it
	writer.write("Camera", value.camera);
}

Bool Minty::Serializer<CameraComponent>::deserialize(Reader &reader, CameraComponent &value)
{
	// Read the Camera data from the reader into the CameraComponent's camera
	if (reader.read("Camera", value.camera))
	{
		// Create a render view for the camera
		RenderViewInfo renderViewInfo{};
		value.renderViewHandle = RenderManager::get_instance().create(renderViewInfo, value.camera);
	}
	return true;
}