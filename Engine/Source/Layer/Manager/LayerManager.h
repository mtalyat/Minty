#pragma once

#include "Core/Data/Map.h"
#include "Core/Data/Array.h"
#include "Layer/LayerMask/LayerMask.h"

namespace Minty
{
    struct LayerManagerInfo;

    class LayerManager
    {
#pragma region Constructor

    public:
        LayerManager(LayerManagerInfo const& info);
        ~LayerManager();

        LayerManager(LayerManager const& other) = delete;
        LayerManager(LayerManager&& other) = delete;

#pragma endregion

#pragma region Operators

    public:
        LayerManager& operator=(LayerManager const& other) = delete;
        LayerManager& operator=(LayerManager&& other) = delete;

#pragma endregion

#pragma region Accessor

    public:
        Layer get_layer(String const& name) const;
        String get_layer_name(Layer const layer) const;
        LayerMask get_layer_mask(Layer const layer) const;
        Bool is_valid(Layer const layer) const;
        Bool is_valid(String const& name) const;

#pragma region Method

    public:

        Layer create_layer(String const& name, LayerMask const mask);
        void create_layer(String const& name, LayerMask const mask, Layer const layer);
        void destroy_layer(Layer const layer);

        static LayerManager& get_singleton();

#pragma endregion

#pragma region Variables

    private:
        Map<StringView, Layer> m_nameToLayer;
        Array<String, LAYER_COUNT> m_layerToName;
        Array<LayerMask, LAYER_COUNT> m_collisionMasks;

        static LayerManager* sp_singleton;

#pragma endregion
    };
}