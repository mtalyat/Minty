#include "pch.h"
#include "LayerComponent.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"
#include "Layer/Manager/LayerManager.h"

using namespace Minty;

Bool Minty::Serializer<LayerComponent>::serialize(Writer &writer, LayerComponent const &value)
{
	writer.write("Layer", value);
	return true;
}

Bool Minty::Serializer<LayerComponent>::deserialize(Reader &reader, LayerComponent &value)
{
	// read the name of the layer
	String layerName;
	if (reader.read_primary("Layer", layerName))
	{
		// get the layer from the name
		LayerManager& layerManager = LayerManager::get_singleton();
		if (layerManager.is_valid(layerName))
		{
			value.layer = layerManager.get_layer(layerName);
		} else
		{
			MINTY_ERROR(ErrorCodeEnum::Serialization_InvalidValue, layerName);
			value.layer = LAYER_DEFAULT;
		}
	}
	return true;
}
	