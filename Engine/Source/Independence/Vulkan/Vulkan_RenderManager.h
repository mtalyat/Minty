#pragma once

/**
 * @file Vulkan_RenderManager.h
 * @brief Vulkan_RenderManager class definition.
 * @author Mitchell Talyat
 */

#include "Vulkan_Buffer.h"
#include "Vulkan_Frame.h"
#include "Vulkan_Geometry.h"
#include "Vulkan_Material.h"
#include "Vulkan_Pipeline.h"
#include "Vulkan_RenderTarget.h"
#include "Vulkan_RenderPass.h"
#include "Vulkan_RenderView.h"
#include "Vulkan_Shader.h"
#include "Vulkan_Surface.h"
#include "Vulkan_Texture.h"
#include "Vulkan_Viewport.h"
#include "Core/Data/Array.h"
#include "Core/Data/HandlePool.h"
#include "Core/Data/IndexPool.h"
#include "Core/Data/View.h"
#include "Render/Constant/Render.h"
#include "Render/Type/Handle.h"
#include "Resource/Image/ImageLayout.h"

namespace Minty
{
    struct RenderManagerInfo;
    struct BufferInfo;
    struct CameraInfo;
    struct GeometryInfo;
    struct MaterialInfo;
    struct PipelineInfo;
    struct ShaderInfo;
    struct SurfaceInfo;
    struct TextureInfo;
    struct ViewportInfo;
    struct RenderAttachment;
    struct RenderPassInfo;
    struct RenderTargetInfo;
    struct RenderViewInfo;
    struct Camera;

    using Vulkan_PipelineLayoutHandle = Handle<Vulkan_PipelineLayoutData>;

    class Vulkan_RenderManager
    {
#pragma region Constructor

    public:
        Vulkan_RenderManager(RenderManagerInfo const &info);
        ~Vulkan_RenderManager();

#pragma endregion

#pragma region Methods

    public:
        TextureHandle create(TextureInfo const &info);
        void destroy(TextureHandle const handle);
        Bool is_valid(TextureHandle const handle) const;
        void set_data(TextureHandle const handle, View const data);

        SurfaceHandle create(SurfaceInfo const &surfaceInfo);
        void destroy(SurfaceHandle const handle);
        Bool is_valid(SurfaceHandle const handle) const;

        ViewportHandle create(ViewportInfo const &viewportInfo);
        void destroy(ViewportHandle const handle);
        Bool is_valid(ViewportHandle const handle) const;

        BufferHandle create(BufferInfo const &bufferInfo);
        void destroy(BufferHandle const handle);
        Bool is_valid(BufferHandle const handle) const;
        void set_data(BufferHandle const handle, View const data);

        ShaderHandle create(ShaderInfo const &shaderInfo);
        void destroy(ShaderHandle const handle);
        Bool is_valid(ShaderHandle const handle) const;

        PipelineHandle create(PipelineInfo const &pipelineInfo);
        void destroy(PipelineHandle const handle);
        Bool is_valid(PipelineHandle const handle) const;

        RenderPassHandle create(RenderPassInfo const &renderPassInfo);
        void destroy(RenderPassHandle const handle);
        Bool is_valid(RenderPassHandle const handle) const;

        MaterialHandle create(MaterialInfo const &materialInfo);
        void destroy(MaterialHandle const handle);
        Bool is_valid(MaterialHandle const handle) const;

        RenderTargetHandle create(RenderTargetInfo const &renderTargetInfo);
        void destroy(RenderTargetHandle const handle);
        Bool is_valid(RenderTargetHandle const handle) const;

        RenderViewHandle create(RenderViewInfo const &renderViewInfo, Camera const& camera);
        void destroy(RenderViewHandle const handle);
        Bool is_valid(RenderViewHandle const handle) const;
        void update_view(RenderViewHandle const handle, Float3 const &position, Float3 const &direction);
        void set_view(RenderViewHandle const handle);

        GeometryHandle create(GeometryInfo const &geometryInfo);
        void destroy(GeometryHandle const handle);
        Bool is_valid(GeometryHandle const handle) const;

        Bool begin_frame();
        void end_frame();

        Bool begin_pass(RenderPassHandle const handle);
        void end_pass();

        // sync the GPU with the CPU, waiting for all commands to finish executing
        void sync();

        // refresh the render manager, recreating any resources that need to be recreated
        void refresh();
        
    private:
        void create_depth_resources();
        void destroy_depth_resources();
        void recreate_depth_resources();

        void create_swapchain(Vulkan_SurfaceData &surfaceData);
        void destroy_swapchain(Vulkan_SurfaceData &surfaceData);
        void recreate_swapchain(Vulkan_SurfaceData &surfaceData);

        void create_frame(Vulkan_Frame &frame);
        void destroy_frame(Vulkan_Frame &frame);
        inline Vulkan_Frame &get_current_frame() { return m_frames.at(m_currentFrameIndex); }
        void abort_frame();

        void create_render_pass_framebuffers(Vulkan_RenderPassData &renderPassData, RenderTargetHandle const renderTargetHandle);
        void destroy_render_pass_framebuffers(Vulkan_RenderPassData &renderPassData);

        void create_attachment_description(RenderAttachment const &attachment, VkAttachmentDescription &description);
        
        void transition_layout(VkCommandBuffer const commandBuffer, TextureHandle const handle, VkImageLayout const layout);

#pragma endregion

#pragma region Variables

    private:
        // vulkan instance data:
        VkInstance m_instance;
#ifdef MINTY_DEBUG
        VkDebugUtilsMessengerEXT m_debugMessenger;
#endif
        VkFormat m_targetSurfaceFormat;
        VkPhysicalDevice m_physicalDevice;
        VkDevice m_device;
        VkQueue m_graphicsQueue;
        VkQueue m_presentQueue;
        VkCommandPool m_commandPool;

        // frame data:
        Array<Vulkan_Frame, FRAMES_PER_FLIGHT> m_frames;
        Size m_currentFrameIndex = 0;
        Bool m_renderedToMainSurfaceThisFrame = false;

        // external pools
        HandlePool<Vulkan_BufferData, Buffer> m_bufferDataPool;
        HandlePool<Vulkan_GeometryData, Geometry> m_geometryDataPool;
        HandlePool<Vulkan_MaterialData, Material> m_materialDataPool;
        HandlePool<Vulkan_PipelineData, Pipeline> m_pipelineDataPool;
        HandlePool<Vulkan_RenderPassData, RenderPass> m_renderPassDataPool;
        HandlePool<Vulkan_RenderTargetData, RenderTarget> m_renderTargetDataPool;
        HandlePool<Vulkan_RenderViewData, RenderView> m_renderViewDataPool;
        HandlePool<Vulkan_ShaderData, Shader> m_shaderDataPool;
        HandlePool<Vulkan_SurfaceData, Surface> m_surfaceDataPool;
        HandlePool<Vulkan_TextureData, Texture> m_textureDataPool;
        HandlePool<Vulkan_ViewportData, Viewport> m_viewportDataPool;

        // internal pools
        HandlePool<Vulkan_PipelineLayoutData> m_pipelineLayoutDataPool;

        // global resources
        SurfaceHandle m_surface;
        TextureHandle m_depthStencilImage;
        RenderTargetHandle m_defaultRenderTarget;
        ViewportHandle m_defaultViewport;

        // active objects
        RenderViewHandle m_activeRenderView;
        
#pragma endregion
    };
}
