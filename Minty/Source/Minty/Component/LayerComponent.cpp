#include "pch.h"
#include "LayerComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Layer/LayerManager.h"

using namespace Minty;

void Minty::LayerComponent::serialize(Writer& writer) const
{
	LayerManager& layerManager = LayerManager::get_singleton();

	// get layer's name
	writer.write("Layer", layerManager.get_name(layer));
}

Bool Minty::LayerComponent::deserialize(Reader& reader)
{
	// read the name of the layer
	String layerName;
	if (reader.read("Layer", layerName))
	{
		// get the layer from the name
		LayerManager& layerManager = LayerManager::get_singleton();
		layer = layerManager.get_layer(layerName);

		if (layer == LAYER_NONE)
		{
			MINTY_ERROR(F("Failed to find layer \"{}\".", layerName));
			return false;
		}

		return true;
	}

	return false;
}
