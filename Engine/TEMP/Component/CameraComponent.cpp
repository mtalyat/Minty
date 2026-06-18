#include "pch.h"
#include "CameraComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<CameraComponent>::serialize(Writer &writer, CameraComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<CameraComponent>::deserialize(Reader &reader, CameraComponent &value)
{
	UUID id;
	if(reader.read_primary("Camera", id))
	{
		AssetManager& assetManager = AssetManager::get_singleton();
		value.camera = assetManager.get_ref<Camera>(id);
		MINTY_ASSERT_F(value.camera != nullptr, ErrorCodeEnum::Asset_MissingDependency, id);
	}
	return true;
}