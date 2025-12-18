#include "pch.h"
#include "LayerManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Core/Format.h"
#include "Minty/Layer/LayerManagerInfo.h"
#ifdef MINTY_DEBUG
#include "Minty/Data/Set.h"
#endif // MINTY_DEBUG

using namespace Minty;

Minty::LayerManager::LayerManager(LayerManagerInfo const& info)
	: Manager()
	, m_names()
	, m_matrix()
{
	// set names to empty, matrix to empty
	for (Size i = 0; i < LAYER_COUNT; ++i)
	{
		m_names[i] = String();
		m_matrix[i] = LAYER_NONE;
	}

#ifdef MINTY_DEBUG
	Set<Layer> usedLayers;
#endif // MINTY_DEBUG

	// build the matrix and names using the provided layer collisions
	for (auto const& layerCollision : info.layerCollisions)
	{
		String const& name = layerCollision.get_first();
		MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
		Layer const layer = layerCollision.get_second();
#ifdef MINTY_DEBUG
		if (!usedLayers.add(layer))
		{
			MINTY_ABORT_F(ErrorCode::Argument_KeyAlreadyExists, layer);
		}
#endif // MINTY_DEBUG
		Layer const mask = layerCollision.get_third();
		m_names[layer] = name;
		m_matrix[layer] = mask;
	}

	// for each layer, ensure that the collisions are symmetric
	for (Layer layer = 0; layer < LAYER_COUNT; ++layer)
	{
		// skip if empty layer
		if(m_names[layer].is_empty())
		{
			continue;
		}

		Layer const mask = m_matrix[layer];
		Layer const bit = (1 << layer);
		for (Layer otherLayer = 0; otherLayer < LAYER_COUNT; ++otherLayer)
		{
			// skip self
			if (otherLayer == layer)
			{
				continue;
			}

			// skip if other layer is empty
			if (m_names[otherLayer].is_empty())
			{
				continue;
			}

			// if this layer collides with the other layer, ensure the other layer collides with this layer
			// print warning if not symmetric
			Layer const otherBit = (1 << otherLayer);
			if (((mask & otherBit) != 0) && !(m_matrix[otherLayer] & bit))
			{
				MINTY_LOG_WARNING(F("Layer collision between '{}' and '{}' is not symmetric. Making it symmetric.", m_names[layer], m_names[otherLayer]));
				m_matrix[otherLayer] |= bit;
			}
		}
	}
}

Layer Minty::LayerManager::get_layer(String const& name) const
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	for (Layer i = 0; i < LAYER_COUNT; i++)
	{
		if (m_names[i] == name)
		{
			return i;
		}
	}
	// not found
	return LAYER_NONE;
}

Bool Minty::LayerManager::check_for_collision(Layer const layerA, Layer const layerB) const
{
	// get the mask for layer A
	Layer const maskA = get_mask(layerA);

	// check if layer B is in the mask for layer A
	Layer const bitB = layer_to_bit(layerB);
	return (maskA & bitB) != 0;
}

Unique<LayerManager> Minty::LayerManager::create(LayerManagerInfo const& info)
{
	return Unique<LayerManager>::create(info);
}

Unique<LayerManager> Minty::LayerManager::create()
{
	LayerManagerInfo info{};
	return create(info);
}

Unique<LayerManager> const& Minty::LayerManager::get_instance()
{
	return Application::get_singleton().get_layer_manager();
}

LayerManager& Minty::LayerManager::get_singleton()
{
	Unique<LayerManager> const& instance = Application::get_singleton().get_layer_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_LayerManagerNotInitialized);
	return *instance;
}
