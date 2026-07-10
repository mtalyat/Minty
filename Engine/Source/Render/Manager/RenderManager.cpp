#include "pch.h"
#include "RenderManager.h"
#include "RenderManagerInfo.h"
#include "Resource/Manager/ResourceManager.h"
#include "Render/Texture/TextureInfo.h"
#include "Render/Shader/ShaderInfo.h"
#include "Render/RenderPass/RenderPassInfo.h"
#include "Render/Pipeline/PipelineInfo.h"
#include "Render/Material/MaterialInfo.h"

using namespace Minty;

RenderManager* RenderManager::s_instance = nullptr;

#ifdef MINTY_VULKAN
#include "Independence/Vulkan/Vulkan_RenderManager.h"
struct RenderManager::Impl
{
    Vulkan_RenderManager renderManager;
};
#else
#   error "No render manager implementation defined for the current platform."
#endif

Minty::RenderManager::RenderManager(RenderManagerInfo const& info)
    : mp_impl(nullptr), m_state(State::Idle)
{
    mp_impl = new Impl(info);

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
    return mp_impl->renderManager.create(info);
}

TextureHandle Minty::RenderManager::create(TextureResourceHandle const resourceHandle)
{
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
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(TextureHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

SurfaceHandle Minty::RenderManager::create(SurfaceInfo const &surfaceInfo)
{
    return mp_impl->renderManager.create(surfaceInfo);
}

void Minty::RenderManager::destroy(SurfaceHandle const handle)
{
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(SurfaceHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

ViewportHandle Minty::RenderManager::create(ViewportInfo const &viewportInfo)
{
    return mp_impl->renderManager.create(viewportInfo);
}

void Minty::RenderManager::destroy(ViewportHandle const handle)
{
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(ViewportHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

ShaderHandle Minty::RenderManager::create(ShaderInfo const &shaderInfo)
{
    return mp_impl->renderManager.create(shaderInfo);
}

ShaderHandle Minty::RenderManager::create(ShaderResourceHandle const resourceHandle)
{
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
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(ShaderHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

RenderPassHandle Minty::RenderManager::create(RenderPassInfo const &renderPassInfo)
{
    return mp_impl->renderManager.create(renderPassInfo);
}

RenderPassHandle Minty::RenderManager::create(RenderPassResourceHandle const resourceHandle)
{
    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    RenderPassResource const &renderPassResource = resourceManager.at<RenderPassResource>(resourceHandle);

    // Create info from it
    RenderPassInfo renderPassInfo{};
    renderPassInfo.attachments = renderPassResource.attachments;

    // Create the render pass
    RenderPassHandle const handle = create(renderPassInfo);
    cache_handle<RenderPassResourceHandle, RenderPassHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(RenderPassHandle const handle)
{
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(RenderPassHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

PipelineHandle Minty::RenderManager::create(PipelineInfo const &pipelineInfo)
{
    return mp_impl->renderManager.create(pipelineInfo);
}

PipelineHandle Minty::RenderManager::create(PipelineResourceHandle const resourceHandle)
{
    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    PipelineResource const &pipelineResource = resourceManager.at<PipelineResource>(resourceHandle);
    RenderPassResource const &renderPassResource = resourceManager.at<RenderPassResource>(pipelineResource.renderPass);
    ShaderResource const &vertexShaderResource = resourceManager.at<ShaderResource>(pipelineResource.vertexShader);
    ShaderResource const &fragmentShaderResource = resourceManager.at<ShaderResource>(pipelineResource.fragmentShader);

    // Create info from it
    PipelineInfo pipelineInfo{};
    pipelineInfo.renderPass = get_cached_handle<RenderPassResourceHandle, RenderPassHandle>(pipelineResource.renderPass);
    pipelineInfo.vertexShader = get_cached_handle<ShaderResourceHandle, ShaderHandle>(pipelineResource.vertexShader);
    pipelineInfo.fragmentShader = get_cached_handle<ShaderResourceHandle, ShaderHandle>(pipelineResource.fragmentShader);
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
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(PipelineHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

MaterialHandle Minty::RenderManager::create(MaterialInfo const &materialInfo)
{
    return mp_impl->renderManager.create(materialInfo);
}

MaterialHandle Minty::RenderManager::create(MaterialResourceHandle const resourceHandle)
{
    // Get resource data
    ResourceManager &resourceManager = ResourceManager::get_instance();
    MaterialResource const &materialResource = resourceManager.at<MaterialResource>(resourceHandle);
    PipelineResource const &pipelineResource = resourceManager.at<PipelineResource>(materialResource.pipeline);

    // Create info from it
    MaterialInfo materialInfo{};
    materialInfo.pipeline = get_cached_handle<PipelineResourceHandle, PipelineHandle>(materialResource.pipeline);
    materialInfo.values = materialResource.cargo;
    materialInfo.stencil = materialResource.stencil;

    // Create the material
    MaterialHandle const handle = create(materialInfo);
    cache_handle<MaterialResourceHandle, MaterialHandle>(resourceHandle, handle);
    return handle;
}

void Minty::RenderManager::destroy(MaterialHandle const handle)
{
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(MaterialHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

RenderTargetHandle Minty::RenderManager::create(RenderTargetInfo const &renderTargetInfo)
{
    return mp_impl->renderManager.create(renderTargetInfo);
}

void Minty::RenderManager::destroy(RenderTargetHandle const handle)
{
    mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(RenderTargetHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

RenderViewHandle Minty::RenderManager::create(RenderViewInfo const &renderViewInfo, Camera const& camera)
{
    return mp_impl->renderManager.create(renderViewInfo, camera);
}

void Minty::RenderManager::destroy(RenderViewHandle const handle)
{
    return mp_impl->renderManager.destroy(handle);
}

Bool Minty::RenderManager::is_valid(RenderViewHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

void Minty::RenderManager::update_view(RenderViewHandle const handle, Float3 const &position, Float3 const &direction)
{
    mp_impl->renderManager.update_view(handle, position, direction);
}

void Minty::RenderManager::set_view(RenderViewHandle const handle)
{
    mp_impl->renderManager.set_view(handle);
}

void Minty::RenderManager::set_view(RenderViewHandle const handle, Float3 const &position, Float3 const &direction)
{
    mp_impl->renderManager.update_view(handle, position, direction);
    mp_impl->renderManager.set_view(handle);
}

RenderManager &Minty::RenderManager::get_instance()
{
    MINTY_ASSERT(s_instance != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *s_instance;
}