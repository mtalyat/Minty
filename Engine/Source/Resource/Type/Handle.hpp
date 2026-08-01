#pragma once

/**
 * @file Handle.hpp
 * @brief Header file defining handle types for the resource layer.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Handle.hpp"

namespace Minty
{
    struct GenericResource;
    using GenericHandle = Handle<GenericResource>;

    struct ClipResource;
    using ClipResourceHandle = Handle<ClipResource>;

    struct FontResource;
    using FontResourceHandle = Handle<FontResource>;

    struct FontVariantResource;
    using FontVariantResourceHandle = Handle<FontVariantResource>;

    struct MeshResource;
    using MeshResourceHandle = Handle<MeshResource>;

    struct ImageResource;
    using ImageResourceHandle = Handle<ImageResource>;

    struct MaterialResource;
    using MaterialResourceHandle = Handle<MaterialResource>;

    struct PipelineResource;
    using PipelineResourceHandle = Handle<PipelineResource>;

    struct PrefabResource;
    using PrefabResourceHandle = Handle<PrefabResource>;

    struct RenderPassResource;
    using RenderPassResourceHandle = Handle<RenderPassResource>;

    struct RenderTargetResource;
    using RenderTargetResourceHandle = Handle<RenderTargetResource>;

    struct ShaderResource;
    using ShaderResourceHandle = Handle<ShaderResource>;

    struct SpriteResource;
    using SpriteResourceHandle = Handle<SpriteResource>;

    struct TextureResource;
    using TextureResourceHandle = Handle<TextureResource>;

    struct ViewportResource;
    using ViewportResourceHandle = Handle<ViewportResource>;
}