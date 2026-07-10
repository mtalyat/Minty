#include "pch.h"
#include "LayerManager.h"

using namespace Minty;

Minty::LayerManager::LayerManager(LayerManagerInfo const &info)
: m_nameToLayer(),
  m_layerToName()
{
    MINTY_ASSERT(!sp_singleton, ErrorCodeEnum::Singleton_AlreadyExists);
    sp_singleton = this;
}

Minty::LayerManager::~LayerManager()
{
    MINTY_ASSERT(sp_singleton == this, ErrorCodeEnum::Singleton_DifferentObject);
    sp_singleton = nullptr;
}

Layer Minty::LayerManager::get_layer(String const &name) const
{
    MINTY_ASSERT(m_nameToLayer.contains(name), ErrorCodeEnum::Layer_NotFound, name);
    return m_nameToLayer[name];
}

String Minty::LayerManager::get_layer_name(Layer const layer) const
{
    MINTY_ASSERT(is_valid(layer), ErrorCodeEnum::Layer_NotFound, layer);
    return m_layerToName[layer.value];
}

LayerMask Minty::LayerManager::get_layer_mask(Layer const layer) const
{
    MINTY_ASSERT(is_valid(layer), ErrorCodeEnum::Layer_NotFound, layer);
    return m_collisionMasks[layer.value];
}

Bool Minty::LayerManager::is_valid(Layer const layer) const
{
    if (layer.value >= LAYER_COUNT)
    {
        return false;
    }
    return !m_layerToName[layer.value].is_empty();
}

Bool Minty::LayerManager::is_valid(String const &name) const
{
    return m_nameToLayer.contains(name);
}

Layer Minty::LayerManager::create_layer(String const &name, LayerMask const mask)
{
    MINTY_ASSERT(!name.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);

    // iterate and find an empty layer
    for (LayerType i = 0; i < LAYER_COUNT; ++i)
    {
        if (m_layerToName[i].is_empty())
        {
            Layer layer(i);
            create_layer(name, mask, layer);
            return layer;
        }
    }

    MINTY_ABORT(ErrorCodeEnum::Layer_MaxLayersReached);
    return LAYER_DEFAULT;
}

void Minty::LayerManager::create_layer(String const &name, LayerMask const mask, Layer const layer)
{
    MINTY_ASSERT(!name.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);
    MINTY_ASSERT(!is_valid(layer), ErrorCodeEnum::Layer_AlreadyExists);

    // add the layer data
    m_nameToLayer[name] = layer;
    m_layerToName[layer.value] = name;
    m_collisionMasks[layer.value] = mask;

    // add the layer to all masks that have it
    LayerMask const layerMask = layer.to_mask();
    for (LayerType i = 0; i < LAYER_COUNT; ++i)
    {
        if (mask.has_layer(i) || i == layer)
        {
            m_collisionMasks[i] |= layerMask;
        }
    }
}

void Minty::LayerManager::destroy_layer(Layer const layer)
{
    MINTY_ASSERT(layer != LAYER_DEFAULT, ErrorCodeEnum::Layer_Protected);
    MINTY_ASSERT(is_valid(layer), ErrorCodeEnum::Layer_NotFound, layer);

    // remove the layer from all masks
    LayerMask invertedLayerMask = ~layer.to_mask();
    for (LayerType i = 0; i < LAYER_COUNT; ++i)
    {
        m_collisionMasks[i] &= invertedLayerMask;
    }

    // remove layer data
    String const& name = m_layerToName[layer.value];
    m_nameToLayer.remove(name);
    m_layerToName[layer.value] = String();
    m_collisionMasks[layer.value] = LayerMask();
}

LayerManager &Minty::LayerManager::get_singleton()
{
    MINTY_ASSERT(sp_singleton, ErrorCodeEnum::Singleton_DoesNotExist);
    return *sp_singleton;
}
