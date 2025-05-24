#include "pch.h"
#include "CameraComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::CameraComponent::serialize(Writer& writer) const
{
	if (camera == nullptr)
	{
		writer.write("Camera", INVALID_ID);
		return;
	}

	writer.write("Camera", camera->get_id());
}

Bool Minty::CameraComponent::deserialize(Reader& reader)
{
	reader.read("Camera", camera);
	return true;
}
