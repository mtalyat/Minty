#include "pch.h"
#include "LayerManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Core/Format.h"
#ifdef MINTY_DEBUG
#include "Minty/Data/Set.h"
#endif // MINTY_DEBUG

using namespace Minty;

Minty::LayerManager::LayerManager(LayerManagerBuilder const& builder)
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
	for (auto const& layerCollision : builder.layerCollisions)
	{
		String const& name = layerCollision.get_first();
		MINTY_ASSERT(!name.is_empty(), "Layer name cannot be empty.");
		Layer const layer = layerCollision.get_second();
#ifdef MINTY_DEBUG
		if (!usedLayers.add(layer))
		{
			MINTY_ABORT(F("Layer {} is already used.", layer));
		}
#endif // MINTY_DEBUG
		Layer const mask = layerCollision.get_third();
		m_names[layer] = name;
		m_matrix[layer] = mask;
	}
}

Layer Minty::LayerManager::get_layer(String const& name) const
{
	MINTY_ASSERT(!name.is_empty(), "Layer name cannot be empty.");
	for (Size i = 0; i < LAYER_COUNT; i++)
	{
		if (m_names[i] == name)
		{
			return static_cast<Layer>(i);
		}
	}
	// not found
	return LAYER_NONE;
}

Owner<LayerManager> Minty::LayerManager::create(LayerManagerBuilder const& builder)
{
	return Owner<LayerManager>(builder);
}

LayerManager& Minty::LayerManager::get_singleton()
{
	Context& context = Context::get_singleton();
	return context.get_layer_manager();
}
