#pragma once

/**
 * @file Handle.hpp
 * @brief Header file defining handle types for the resource layer.
 * @author Mitchell Talyat
 */

#include "Core/Type/Handle.hpp"

namespace Minty
{
    class Buffer;
    using BufferHandle = Handle<Buffer>;

    class Geometry;
    using GeometryHandle = Handle<Geometry>;

    class Material;
    using MaterialHandle = Handle<Material>;

    class Mesh;
    using MeshHandle = Handle<Mesh>;

    class Pipeline;
    using PipelineHandle = Handle<Pipeline>;

    class RenderPass;
    using RenderPassHandle = Handle<RenderPass>;

    class RenderTarget;
    using RenderTargetHandle = Handle<RenderTarget>;

    class RenderView;
    using RenderViewHandle = Handle<RenderView>;

    class Shader;
    using ShaderHandle = Handle<Shader>;

    class Sprite;
    using SpriteHandle = Handle<Sprite>;

    class Surface;
    using SurfaceHandle = Handle<Surface>;

    class Texture;
    using TextureHandle = Handle<Texture>;

    class Viewport;
    using ViewportHandle = Handle<Viewport>;
}