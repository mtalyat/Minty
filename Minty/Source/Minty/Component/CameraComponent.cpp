#include "pch.h"
#include "CameraComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::CameraComponent::serialize(Writer& writer) const
{
	camera.serialize(writer);
}

Bool Minty::CameraComponent::deserialize(Reader& reader)
{
	return camera.deserialize(reader);
}
