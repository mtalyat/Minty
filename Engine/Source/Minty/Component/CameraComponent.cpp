#include "pch.h"
#include "CameraComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<CameraComponent>::serialize(Writer &writer, CameraComponent const &value)
{
	if (value.camera == nullptr)
	{
		writer.write("Camera", UUID());
		return;
	}

	writer.write("Camera", value.camera->get_id());
}

void Minty::Serializer<CameraComponent>::deserialize(Reader &reader, CameraComponent &value)
{
	if(!reader.read_default<UUID>(value.cameraId))
	{
		reader.read("Camera", value.cameraId);
	}
}