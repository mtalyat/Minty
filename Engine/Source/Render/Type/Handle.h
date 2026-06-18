#pragma once

/**
 * @file Handle.h
 * @brief Header file defining handle types for the resource layer.
 * @author Mitchell Talyat
 */

#include "Core/Type/Handle.h"

namespace Minty
{
    class Buffer;
    using BufferHandle = Handle<Buffer>;

    class Camera;
    using CameraHandle = Handle<Camera>;

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

    class Shader;
    using ShaderHandle = Handle<Shader>;

    class Surface;
    using SurfaceHandle = Handle<Surface>;

    class Texture;
    using TextureHandle = Handle<Texture>;

    class Viewport;
    using ViewportHandle = Handle<Viewport>;
}