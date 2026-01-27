#include "pch.h"
#include "LayerComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Layer/LayerManager.h"

using namespace Minty;

void Minty::Serializer<LayerComponent>::serialize(Writer &writer, LayerComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<LayerComponent>::deserialize(Reader &reader, LayerComponent &value)
{
	// read the name of the layer
	String layerName;
	if (reader.read_primary("Layer", layerName))
	{
		// get the layer from the name
		LayerManager& layerManager = LayerManager::get_singleton();
		value.layer = layerManager.get_layer(layerName);

		MINTY_ASSERT_F(value.layer != LAYER_NONE, ErrorCode::Layer_NotFound, layerName);
	}
	return true;
}
	