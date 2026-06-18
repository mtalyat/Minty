#pragma once

/**
 * @file Handle.h
 * @brief Header file defining handle types for the resource layer.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Type/Handle.h"

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

    struct GeometryResource;
    using GeometryResourceHandle = Handle<GeometryResource>;

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

    struct ShaderResource;
    using ShaderResourceHandle = Handle<ShaderResource>;

    struct TextureResource;
    using TextureResourceHandle = Handle<TextureResource>;
}