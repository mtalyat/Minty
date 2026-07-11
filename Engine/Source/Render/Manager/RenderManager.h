#pragma once

/**
 * @file RenderManager.h
 * @brief RenderManager class definition.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Data/Unique.h"
#include "Resource/Type/Handle.h"
#include "Render/Type/Handle.h"
#include "Core/Data/Map.h"

namespace Minty
{
    struct RenderManagerInfo;
    struct BufferInfo;
    struct ImageInfo;
    struct MaterialInfo;
    struct PipelineInfo;
    struct RenderPassInfo;
    struct RenderTargetInfo;
    struct RenderViewInfo;
    struct ShaderInfo;
    struct SurfaceInfo;
    struct TextureInfo;
    struct ViewportInfo;
    struct Camera;

    class RenderManager
    {
#pragma region Type

    public:
        struct Impl;

    private:
        enum class State
        {
            // Not doing anything
            Idle,

            // Rendering a frame
            Frame,

            // Rendering a render pass
            Pass
        };

#pragma endregion

#pragma region Constructor

    public:
        RenderManager(RenderManagerInfo const &info);

        RenderManager(RenderManager const &) = delete;
        RenderManager(RenderManager &&) = delete;

        ~RenderManager();

#pragma endregion

#pragma region Operator

    public:
        RenderManager &operator=(RenderManager const &) = delete;
        RenderManager &operator=(RenderManager &&) = delete;

#pragma endregion

#pragma region Methods

    public:
        TextureHandle create(TextureInfo const &info);
        TextureHandle create(TextureResourceHandle const resourceHandle);
        void destroy(TextureHandle const handle);
        Bool is_valid(TextureHandle const handle) const;

        SurfaceHandle create(SurfaceInfo const &surfaceInfo);
        void destroy(SurfaceHandle const handle);
        Bool is_valid(SurfaceHandle const handle) const;

        ViewportHandle create(ViewportInfo const &viewportInfo);
        ViewportHandle create(ViewportResourceHandle const resourceHandle);
        void destroy(ViewportHandle const handle);
        Bool is_valid(ViewportHandle const handle) const;

        ShaderHandle create(ShaderInfo const &shaderInfo);
        ShaderHandle create(ShaderResourceHandle const resourceHandle);
        void destroy(ShaderHandle const handle);
        Bool is_valid(ShaderHandle const handle) const;

        RenderPassHandle create(RenderPassInfo const &renderPassInfo);
        RenderPassHandle create(RenderPassResourceHandle const resourceHandle);
        void destroy(RenderPassHandle const handle);
        Bool is_valid(RenderPassHandle const handle) const;

        PipelineHandle create(PipelineInfo const &pipelineInfo);
        PipelineHandle create(PipelineResourceHandle const resourceHandle);
        void destroy(PipelineHandle const handle);
        Bool is_valid(PipelineHandle const handle) const;

        MaterialHandle create(MaterialInfo const &materialInfo);
        MaterialHandle create(MaterialResourceHandle const resourceHandle);
        void destroy(MaterialHandle const handle);
        Bool is_valid(MaterialHandle const handle) const;

        RenderTargetHandle create(RenderTargetInfo const &renderTargetInfo);
        RenderTargetHandle create(RenderTargetResourceHandle const resourceHandle);
        void destroy(RenderTargetHandle const handle);
        Bool is_valid(RenderTargetHandle const handle) const;

        RenderViewHandle create(RenderViewInfo const &renderViewInfo, Camera const& camera);
        void destroy(RenderViewHandle const handle);
        Bool is_valid(RenderViewHandle const handle) const;
        void update_view(RenderViewHandle const handle, Float3 const &position, Float3 const &direction);
        void set_view(RenderViewHandle const handle);
        void set_view(RenderViewHandle const handle, Float3 const &position, Float3 const &direction);

        void begin_frame();
        void end_frame();

        void begin_pass(RenderPassHandle const handle);
        void end_pass();

        /**
         * @brief Gets the singleton instance of the RenderManager.
         * @return The RenderManager instance.
         */
        static RenderManager &get_instance();

    private:
        template<typename ResourceHandle, typename Handle>
        Map<ResourceHandle, Handle> &get_cache()
        {
            if constexpr (std::is_same_v<ResourceHandle, MaterialResourceHandle> && std::is_same_v<Handle, MaterialHandle>)
            {
                return m_materialCache;
            } 
            else if constexpr (std::is_same_v<ResourceHandle, TextureResourceHandle> && std::is_same_v<Handle, TextureHandle>)
            {
                return m_textureCache;
            }
            else if constexpr (std::is_same_v<ResourceHandle, ShaderResourceHandle> && std::is_same_v<Handle, ShaderHandle>)
            {
                return m_shaderCache;
            }
            else if constexpr (std::is_same_v<ResourceHandle, RenderPassResourceHandle> && std::is_same_v<Handle, RenderPassHandle>)
            {
                return m_renderPassCache;
            }
            else if constexpr (std::is_same_v<ResourceHandle, RenderTargetResourceHandle> && std::is_same_v<Handle, RenderTargetHandle>)
            {
                return m_renderTargetCache;
            }
            else if constexpr (std::is_same_v<ResourceHandle, PipelineResourceHandle> && std::is_same_v<Handle, PipelineHandle>)
            {
                return m_pipelineCache;
            }
            else if constexpr (std::is_same_v<ResourceHandle, ViewportResourceHandle> && std::is_same_v<Handle, ViewportHandle>)
            {
                return m_viewportCache;
            }
            else
            {
                MINTY_ABORT(ErrorCodeEnum::NotSupported);
                static Map<ResourceHandle, Handle> dummyCache;
                return dummyCache;
            }
        }

        template<typename ResourceHandle, typename Handle>
        void cache_handle(ResourceHandle const resourceHandle, Handle const handle)
        {
            Map<ResourceHandle, Handle> &cache = get_cache<ResourceHandle, Handle>();
            cache.add(resourceHandle, handle);
        }

        template<typename ResourceHandle, typename Handle>
        Handle get_cached_handle(ResourceHandle const resourceHandle)
        {
            Map<ResourceHandle, Handle> &cache = get_cache<ResourceHandle, Handle>();
            
            // Find existing handle in the cache
            auto it = cache.find(resourceHandle);
            if (it == cache.end())
            {
                return INVALID_HANDLE;
            }
            
            // If found, check that it is still valid and return it
            Handle const handle = it->get_second();
            if (!is_valid(handle))
            {
                // No longer valid, so remove it from the cache and return invalid
                cache.remove(resourceHandle);
                return INVALID_HANDLE;
            }

            // Valid handle found, return it
            return handle;
        }

#pragma endregion

#pragma region Variables

    private:
        Impl *mp_impl;

        Map<MaterialResourceHandle, MaterialHandle> m_materialCache;
        Map<TextureResourceHandle, TextureHandle> m_textureCache;
        Map<ShaderResourceHandle, ShaderHandle> m_shaderCache;
        Map<RenderPassResourceHandle, RenderPassHandle> m_renderPassCache;
        Map<RenderTargetResourceHandle, RenderTargetHandle> m_renderTargetCache;
        Map<PipelineResourceHandle, PipelineHandle> m_pipelineCache;
        Map<ViewportResourceHandle, ViewportHandle> m_viewportCache;

        State m_state;

        static RenderManager *s_instance;

#pragma endregion
    };
}