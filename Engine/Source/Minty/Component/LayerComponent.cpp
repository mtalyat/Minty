#include "pch.h"
#include "LayerComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Layer/LayerManager.h"

using namespace Minty;

void Minty::Serializer<LayerComponent>::serialize(Writer &writer, LayerComponent const &value)
{
	LayerManager& layerManager = LayerManager::get_singleton();

	// get layer's name
	writer.write("Layer", layerManager.get_name(value.layer));
}

void Minty::Serializer<LayerComponent>::deserialize(Reader &reader, LayerComponent &value)
{
	// read the name of the layer
	String layerName;
	if (reader.read("Layer", layerName))
	{
		// get the layer from the name
		LayerManager& layerManager = LayerManager::get_singleton();
		value.layer = layerManager.get_layer(layerName);

		MINTY_ASSERT_F(value.layer != LAYER_NONE, ErrorCode::Layer_NotFound, layerName);
	}
}
	