#include "pch.hpp"
#include "LayerComponent.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Layer/Manager/LayerManager.hpp"

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
	