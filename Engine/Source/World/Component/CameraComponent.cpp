#include "pch.hpp"
#include "CameraComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"

using namespace Minty;

void Minty::Serializer<CameraComponent>::serialize(Writer &writer, CameraComponent const &value)
{
	// Serialize the CameraComponent's camera if it exists
	if (value.camera)
	{
		writer.write("Camera", *value.camera);
	}
}

Bool Minty::Serializer<CameraComponent>::deserialize(Reader &reader, CameraComponent &value)
{
	// Create a new Camera if it doesn't exist
	if (!value.camera)
	{
		value.camera = Unique<Camera>::create();
	}

	// Read the Camera data from the reader into the CameraComponent's camera
	return reader.read("Camera", *value.camera);
}