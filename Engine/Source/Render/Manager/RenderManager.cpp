#include "pch.hpp"
#include "RenderManager.hpp"
#include "RenderManagerInfo.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Render/RenderTarget/RenderTargetInfo.hpp"
#include "Render/Texture/TextureInfo.hpp"
#include "Render/Viewport/ViewportInfo.hpp"
#include "Render/Shader/ShaderInfo.hpp"
#include "Render/RenderPass/RenderPassInfo.hpp"
#include "Render/Pipeline/PipelineInfo.hpp"
#include "Render/Material/MaterialInfo.hpp"
#include "Render/Geometry/GeometryInfo.hpp"
#include "Render/Sprite/SpriteInfo.hpp"
#include "Render/Sprite/Sprite.hpp"
#include "Core/Data/Transform.hpp"
#include "Window/Window/Window.hpp"

using namespace Minty;

RenderManager *RenderManager::s_instance = nullptr;

#ifdef MINTY_VULKAN
#include "Independence/Vulkan/Vulkan_RenderManager.hpp"
#endif

Minty::RenderManager::RenderManager(RenderManagerInfo const &info)
    : mp_impl(nullptr), m_state(State::Idle)
{
    mp_impl = new Impl(info);

    m_pendingFramebufferSize = Window::get_main().get_framebuffer_size();
    m_lastRefreshedFramebufferSize = m_pendingFramebufferSize;

    MINTY_ASSERT(s_instance == nullptr, ErrorCodeEnum::Singleton_AlreadyExists);
    s_instance = this;
}

Minty::RenderManager::~RenderManager()
{
    delete mp_impl;

    MINTY_ASSERT(s_instance == this, ErrorCodeEnum::Singleton_DifferentObject);
    s_instance = nullptr;
}

TextureHandle Minty::RenderManager::create(TextureInfo const &info)
{
    return mp_impl->create(info);
}

TextureHandle Minty::RenderManager::create(TextureResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    TextureHandle cachedHandle;
    if (try_get_cached_handle<TextureResourceHandle, TextureHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    TextureResource const &textureResource = resourceManager.at<TextureResource>(resourceHandle);
    ImageResource const &imageResource = resourceManager.at<ImageResource>(textureResource.imageHandle);

    // Create info from it
    TextureInfo textureInfo{};
    textureInfo.addressMode = textureResource.addressMode;
    textureInfo.aspect = textureResource.aspect;
    textureInfo.data = imageResource.data;
    textureInfo.filter = textureResource.filter;
    textureInfo.format = imageResource.format;
    textureInfo.immutable = imageResource.immutable;
    textureInfo.mipLevels = textureResource.mipLevels;
    textureInfo.normalizeCoordinates = textureResource.normalizeCoordinates;
    textureInfo.size = imageResource.size;
    textureInfo.tiling = imageResource.tiling;
    textureInfo.type = imageResource.type;
    textureInfo.usage = imageResource.usage;

    // Create the texture
    TextureHandle const handle = create(textureInfo);
    cache_handle<TextureResourceHandle, TextureHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(TextureHandle const handle)
{
    // Destroy the texture and remove it from the cache
    remove_cached_handle<TextureResourceHandle, TextureHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(TextureHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

UInt2 Minty::RenderManager::get_size(TextureHandle const handle) const
{
    return mp_impl->get_size(handle);
}

SurfaceHandle Minty::RenderManager::create(SurfaceInfo const &surfaceInfo)
{
    return mp_impl->create(surfaceInfo);
}

void Minty::RenderManager::destroy(SurfaceHandle const handle)
{
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(SurfaceHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

ViewportHandle Minty::RenderManager::create(ViewportInfo const &viewportInfo)
{
    return mp_impl->create(viewportInfo);
}

ViewportHandle Minty::RenderManager::create(ViewportResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    ViewportHandle cachedHandle;
    if (try_get_cached_handle<ViewportResourceHandle, ViewportHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    ViewportResource const &viewportResource = resourceManager.at<ViewportResource>(resourceHandle);

    // Create info from it
    ViewportInfo viewportInfo{};
    viewportInfo.dynamic = viewportResource.dynamic;
    viewportInfo.viewPosition = viewportResource.viewPosition;
    viewportInfo.viewSize = viewportResource.viewSize;
    viewportInfo.minDepth = viewportResource.minDepth;
    viewportInfo.maxDepth = viewportResource.maxDepth;
    viewportInfo.scissorPosition = viewportResource.scissorPosition;
    viewportInfo.scissorSize = viewportResource.scissorSize;

    // Create the viewport, cache the handle, and return it
    ViewportHandle const handle = create(viewportInfo);
    cache_handle<ViewportResourceHandle, ViewportHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(ViewportHandle const handle)
{
    // Destroy the viewport and remove it from the cache
    remove_cached_handle<ViewportResourceHandle, ViewportHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(ViewportHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

ShaderHandle Minty::RenderManager::create(ShaderInfo const &shaderInfo)
{
    return mp_impl->create(shaderInfo);
}

ShaderHandle Minty::RenderManager::create(ShaderResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    ShaderHandle cachedHandle;
    if (try_get_cached_handle<ShaderResourceHandle, ShaderHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    ShaderResource const &shaderResource = resourceManager.at<ShaderResource>(resourceHandle);

    // Create info from it
    ShaderInfo shaderInfo{};
    shaderInfo.data = shaderResource.data;
    shaderInfo.entryPoint = shaderResource.entryPoint;
    shaderInfo.stage = shaderResource.stage;

    // Create the shader
    ShaderHandle const handle = create(shaderInfo);
    cache_handle<ShaderResourceHandle, ShaderHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(ShaderHandle const handle)
{
    // Destroy the shader and remove it from the cache
    remove_cached_handle<ShaderResourceHandle, ShaderHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(ShaderHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

RenderPassHandle Minty::RenderManager::create(RenderPassInfo const &renderPassInfo)
{
    RenderPassHandle const handle = mp_impl->create(renderPassInfo);
    m_passes.add(handle);
    return handle;
}

RenderPassHandle Minty::RenderManager::create(RenderPassResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    RenderPassHandle cachedHandle;
    if (try_get_cached_handle<RenderPassResourceHandle, RenderPassHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    RenderPassResource const &renderPassResource = resourceManager.at<RenderPassResource>(resourceHandle);

    // Create info from it
    RenderPassInfo renderPassInfo{};
    renderPassInfo.attachments = renderPassResource.attachments;
    renderPassInfo.clearColor = renderPassResource.clearColor;
    renderPassInfo.clearDepth = renderPassResource.clearDepth;
    renderPassInfo.clearStencil = renderPassResource.clearStencil;
    renderPassInfo.renderTarget = renderPassResource.renderTarget == INVALID_HANDLE
                                      ? INVALID_HANDLE
                                      : get_or_create_cached_handle<RenderTargetResourceHandle, RenderTargetHandle>(renderPassResource.renderTarget);
    renderPassInfo.viewport = renderPassResource.viewport == INVALID_HANDLE
                                  ? INVALID_HANDLE
                                  : get_or_create_cached_handle<ViewportResourceHandle, ViewportHandle>(renderPassResource.viewport);

    // Create the render pass
    RenderPassHandle const handle = create(renderPassInfo);
    cache_handle<RenderPassResourceHandle, RenderPassHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(RenderPassHandle const handle)
{
    // Remove the render pass from the list of passes
    for (Size i = 0; i < m_passes.get_size(); ++i)
    {
        if (m_passes[i] == handle)
        {
            m_passes.remove(i);
            break;
        }
    }

    // Destroy the render pass and remove it from the cache
    remove_cached_handle<RenderPassResourceHandle, RenderPassHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(RenderPassHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

PipelineHandle Minty::RenderManager::create(PipelineInfo const &pipelineInfo)
{
    return mp_impl->create(pipelineInfo);
}

PipelineHandle Minty::RenderManager::create(PipelineResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    PipelineHandle cachedHandle;
    if (try_get_cached_handle<PipelineResourceHandle, PipelineHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    PipelineResource const &pipelineResource = resourceManager.at<PipelineResource>(resourceHandle);

    // Create info from it
    PipelineInfo pipelineInfo{};
    pipelineInfo.renderPass = get_or_create_cached_handle<RenderPassResourceHandle, RenderPassHandle>(pipelineResource.renderPass);
    pipelineInfo.vertexShader = get_or_create_cached_handle<ShaderResourceHandle, ShaderHandle>(pipelineResource.vertexShader);
    pipelineInfo.fragmentShader = get_or_create_cached_handle<ShaderResourceHandle, ShaderHandle>(pipelineResource.fragmentShader);
    pipelineInfo.viewport = INVALID_HANDLE; // TODO: viewport
    pipelineInfo.primitiveTopology = pipelineResource.primitiveTopology;
    pipelineInfo.polygonMode = pipelineResource.polygonMode;
    pipelineInfo.cullMode = pipelineResource.cullMode;
    pipelineInfo.frontFace = pipelineResource.frontFace;
    pipelineInfo.lineWidth = pipelineResource.lineWidth;
    pipelineInfo.transparency = pipelineResource.transparency;
    pipelineInfo.depthMode = pipelineResource.depthMode;
    pipelineInfo.depthTestOperation = pipelineResource.depthTestOperation;
    pipelineInfo.stencilMode = pipelineResource.stencilMode;
    pipelineInfo.stencilTestOperation = pipelineResource.stencilTestOperation;
    pipelineInfo.attributes = pipelineResource.attributes;
    pipelineInfo.inputs = pipelineResource.inputs;

    // Create the pipeline
    PipelineHandle const handle = create(pipelineInfo);
    cache_handle<PipelineResourceHandle, PipelineHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(PipelineHandle const handle)
{
    // Destroy the pipeline and remove it from the cache
    remove_cached_handle<PipelineResourceHandle, PipelineHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(PipelineHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

void Minty::RenderManager::bind(PipelineHandle const handle)
{
    MINTY_ASSERT(m_state >= State::Pass, ErrorCodeEnum::Render_NotRenderingPass);
    mp_impl->bind(handle);
}

MaterialHandle Minty::RenderManager::create(MaterialInfo const &materialInfo)
{
    return mp_impl->create(materialInfo);
}

MaterialHandle Minty::RenderManager::create(MaterialResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    MaterialHandle cachedHandle;
    if (try_get_cached_handle<MaterialResourceHandle, MaterialHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    MaterialResource const &materialResource = resourceManager.at<MaterialResource>(resourceHandle);

    // Create info from it
    MaterialInfo materialInfo{};
    materialInfo.pipeline = get_or_create_cached_handle<PipelineResourceHandle, PipelineHandle>(materialResource.pipeline);
    materialInfo.values = materialResource.cargo;
    materialInfo.stencil = materialResource.stencil;

    // Create the material
    MaterialHandle const handle = create(materialInfo);
    cache_handle<MaterialResourceHandle, MaterialHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(MaterialHandle const handle)
{
    // Destroy the material and remove it from the cache
    remove_cached_handle<MaterialResourceHandle, MaterialHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(MaterialHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

void Minty::RenderManager::update(PipelineHandle const handle, StringView const name, Variable const &value)
{
    mp_impl->update(handle, name, value);
}

void Minty::RenderManager::update(MaterialHandle const handle, StringView const name, Variable const &value)
{
    mp_impl->update(handle, name, value);
}

void Minty::RenderManager::bind(MaterialHandle const handle)
{
    MINTY_ASSERT(m_state >= State::Pass, ErrorCodeEnum::Render_NotRenderingPass);
    mp_impl->bind(handle);
}

PipelineHandle Minty::RenderManager::get_pipeline(MaterialHandle const handle) const
{
    return mp_impl->get_pipeline(handle);
}

RenderTargetHandle Minty::RenderManager::create(RenderTargetInfo const &renderTargetInfo)
{
    return mp_impl->create(renderTargetInfo);
}

RenderTargetHandle Minty::RenderManager::create(RenderTargetResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    RenderTargetHandle cachedHandle;
    if (try_get_cached_handle<RenderTargetResourceHandle, RenderTargetHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    ResourceManager &resourceManager = ResourceManager::get_instance();
    RenderTargetResource const &renderTargetResource = resourceManager.at<RenderTargetResource>(resourceHandle);

    RenderTargetInfo renderTargetInfo{};
    for (TextureResourceHandle const &textureResourceHandle : renderTargetResource.images)
    {
        TextureHandle const textureHandle = get_or_create_cached_handle<TextureResourceHandle, TextureHandle>(textureResourceHandle);
        renderTargetInfo.images.add(textureHandle);
    }

    RenderTargetHandle const handle = create(renderTargetInfo);
    cache_handle<RenderTargetResourceHandle, RenderTargetHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(RenderTargetHandle const handle)
{
    // Destroy the render target and remove it from the cache
    remove_cached_handle<RenderTargetResourceHandle, RenderTargetHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(RenderTargetHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

RenderViewHandle Minty::RenderManager::create(RenderViewInfo const &renderViewInfo, Camera const &camera)
{
    return mp_impl->create(renderViewInfo, camera);
}

void Minty::RenderManager::destroy(RenderViewHandle const handle)
{
    return mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(RenderViewHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

void Minty::RenderManager::update(RenderViewHandle const handle, Float3 const &position, Float3 const &direction)
{
    mp_impl->update(handle, position, direction);
}

void Minty::RenderManager::bind(RenderViewHandle const handle)
{
    mp_impl->bind(handle);
}

void Minty::RenderManager::bind(RenderViewHandle const handle, Float3 const &position, Float3 const &direction)
{
    mp_impl->update(handle, position, direction);
    mp_impl->bind(handle);
}

GeometryHandle Minty::RenderManager::create(GeometryInfo const &geometryInfo)
{
    return mp_impl->create(geometryInfo);
}

GeometryHandle Minty::RenderManager::create(MeshResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    GeometryHandle cachedHandle;
    if (try_get_cached_handle<MeshResourceHandle, GeometryHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    MeshResource const &meshResource = resourceManager.at<MeshResource>(resourceHandle);

    GeometryInfo geometryInfo{};
    geometryInfo.vertexData = View(meshResource.vertexContainer.get_data(), meshResource.vertexContainer.get_size());
    geometryInfo.vertexStride = meshResource.vertexContainer.get_stride();
    geometryInfo.indexData = View(meshResource.indexContainer.get_data(), meshResource.indexContainer.get_size());
    geometryInfo.indexType = GeometryIndexType::from_size(meshResource.indexContainer.get_stride());

    GeometryHandle const handle = create(geometryInfo);
    cache_handle<MeshResourceHandle, GeometryHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(GeometryHandle const handle)
{
    // Destroy the geometry and remove it from the cache
    remove_cached_handle<MeshResourceHandle, GeometryHandle>(handle);
    mp_impl->destroy(handle);
}

Bool Minty::RenderManager::is_valid(GeometryHandle const handle) const
{
    return mp_impl->is_valid(handle);
}

void Minty::RenderManager::bind(GeometryHandle const handle)
{
    mp_impl->bind(handle);
}

SpriteHandle Minty::RenderManager::create(SpriteInfo const &spriteInfo)
{
    // Create the sprite
    Sprite sprite(spriteInfo);

    // Add it to the pool and return the handle
    SpriteHandle const handle = m_spritePool.add(std::move(sprite));
    return handle;
}

SpriteHandle Minty::RenderManager::create(SpriteResourceHandle const resourceHandle)
{
    // Check if the handle is already cached
    SpriteHandle cachedHandle;
    if (try_get_cached_handle<SpriteResourceHandle, SpriteHandle>(resourceHandle, cachedHandle))
    {
        return cachedHandle;
    }

    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    SpriteResource const &spriteResource = resourceManager.at<SpriteResource>(resourceHandle);

    // Create info from the resource
    SpriteInfo spriteInfo{};
    spriteInfo.textureHandle = get_or_create_cached_handle<TextureResourceHandle, TextureHandle>(spriteResource.textureResourceHandle);
    spriteInfo.pixelsPerUnit = spriteResource.pixelsPerUnit;

    // Use the layout to determine how to set the offset, size, and pivot of the sprite
    switch (spriteResource.layout.coordinateMode)
    {
    case CoordinateModeEnum::Normalized:
    {
        UInt2 const textureSize = get_size(spriteInfo.textureHandle);
        spriteInfo.offset = Int2(
            static_cast<Int>(spriteResource.layout.offset.x * textureSize.x),
            static_cast<Int>(spriteResource.layout.offset.y * textureSize.y));
        spriteInfo.size = Int2(
            static_cast<Int>(spriteResource.layout.size.x * textureSize.x),
            static_cast<Int>(spriteResource.layout.size.y * textureSize.y));
        spriteInfo.pivot = Int2(
            static_cast<Int>(spriteResource.layout.pivot.x * textureSize.x),
            static_cast<Int>(spriteResource.layout.pivot.y * textureSize.y));
    }
    break;
    case CoordinateModeEnum::Pixel:
    {
        spriteInfo.offset = Int2(
            static_cast<Int>(spriteResource.layout.offset.x),
            static_cast<Int>(spriteResource.layout.offset.y));
        spriteInfo.size = Int2(
            static_cast<Int>(spriteResource.layout.size.x),
            static_cast<Int>(spriteResource.layout.size.y));
        spriteInfo.pivot = Int2(
            static_cast<Int>(spriteResource.layout.pivot.x),
            static_cast<Int>(spriteResource.layout.pivot.y));
    }
    break;
    default:
        MINTY_ERROR(ErrorCodeEnum::NotSupported);
        break;
    }

    // Create the sprite
    SpriteHandle const handle = create(spriteInfo);
    cache_handle<SpriteResourceHandle, SpriteHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(SpriteHandle const handle)
{
    // Remove the handle from the cache if it exists
    remove_cached_handle<SpriteResourceHandle, SpriteHandle>(handle);

    // Remove the sprite from the pool
    m_spritePool.remove(handle);
}

Bool Minty::RenderManager::is_valid(SpriteHandle const handle) const
{
    return m_spritePool.contains(handle);
}

Sprite const &Minty::RenderManager::get(SpriteHandle const handle) const
{
    MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);
    return m_spritePool.at(handle);
}

Bool Minty::RenderManager::begin_frame()
{
    if (m_refreshPending &&
        m_pendingFramebufferSize.x > 0 &&
        m_pendingFramebufferSize.y > 0 &&
        m_pendingFramebufferSize != m_lastRefreshedFramebufferSize)
    {
        // Coalesce resize events and refresh at most once before rendering the next frame.
        refresh();
        m_lastRefreshedFramebufferSize = m_pendingFramebufferSize;
    }
    m_refreshPending = false;

    // validate state
    MINTY_ASSERT(m_state < State::Frame, ErrorCodeEnum::Render_AlreadyRenderingFrame);
    MINTY_ASSERT(m_state < State::Pass, ErrorCodeEnum::Render_AlreadyRenderingPass);

    if (mp_impl->begin_frame())
    {
        m_state = State::Frame;
        return true;
    }
    else
    {
        m_state = State::Idle;
        return false;
    }
}

void Minty::RenderManager::end_frame()
{
    if (m_state == State::Idle)
    {
        return;
    }

    // validate state
    MINTY_ASSERT(m_state < State::Pass, ErrorCodeEnum::Render_AlreadyRenderingPass);
    MINTY_ASSERT(m_state >= State::Frame, ErrorCodeEnum::Render_NotRenderingFrame);

    mp_impl->end_frame();

    m_state = State::Idle;
}

Bool Minty::RenderManager::begin_pass(RenderPassHandle const handle)
{
    if (m_state == State::Idle)
    {
        return false;
    }

    // validate state
    MINTY_ASSERT(m_state < State::Pass, ErrorCodeEnum::Render_AlreadyRenderingPass);
    MINTY_ASSERT(m_state >= State::Frame, ErrorCodeEnum::Render_NotRenderingFrame);

    m_state = State::Pass;

    return mp_impl->begin_pass(handle);
}

void Minty::RenderManager::end_pass()
{
    if (m_state == State::Idle)
    {
        return;
    }

    // validate state
    MINTY_ASSERT(m_state >= State::Pass, ErrorCodeEnum::Render_NotRenderingPass);
    MINTY_ASSERT(m_state >= State::Frame, ErrorCodeEnum::Render_NotRenderingFrame);

    mp_impl->end_pass();

    m_state = State::Frame;
}

void Minty::RenderManager::draw()
{
    mp_impl->draw(View(), Object());
}

void Minty::RenderManager::draw(Object const &objectValues)
{
    mp_impl->draw(View(), objectValues);
}

void Minty::RenderManager::draw(Transform const &transform)
{
    mp_impl->draw(View(&transform.get_global_matrix(), sizeof(Matrix4)), Object());
}

void Minty::RenderManager::draw(Transform const &transform, Object const &objectValues)
{
    mp_impl->draw(View(&transform.get_global_matrix(), sizeof(Matrix4)), objectValues);
}

void Minty::RenderManager::draw_batch(Size const count, View const data)
{
    mp_impl->draw_instanced(data, count);
}

void Minty::RenderManager::notify_framebuffer_resized(Int2 const size)
{
    if (size.x <= 0 || size.y <= 0)
    {
        return;
    }

    m_pendingFramebufferSize = size;
    m_refreshPending = true;
}

void Minty::RenderManager::refresh()
{
    mp_impl->refresh();
}

RenderManager &Minty::RenderManager::get_instance()
{
    MINTY_ASSERT(s_instance != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *s_instance;
}