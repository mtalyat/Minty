#pragma once

/**
 * @file RenderManager.hpp
 * @brief RenderManager class definition.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Unique.hpp"
#include "Resource/Type/Handle.hpp"
#include "Render/Type/Handle.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/HandlePool.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Data/Variable.hpp"
#include "Core/Data/Object.hpp"

namespace Minty
{
    struct RenderManagerInfo;
    struct BufferInfo;
    struct ImageInfo;
    struct GeometryInfo;
    struct MaterialInfo;
    struct PipelineInfo;
    struct RenderPassInfo;
    struct RenderTargetInfo;
    struct RenderViewInfo;
    struct ShaderInfo;
    struct SpriteInfo;
    struct SurfaceInfo;
    struct TextureInfo;
    struct ViewportInfo;
    struct Camera;
    class Transform;

    class RenderManager
    {
#pragma region Type

    public:
        class Impl;

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
        UInt2 get_size(TextureHandle const handle) const;

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
        inline Vector<RenderPassHandle> const &get_passes() const { return m_passes; }

        PipelineHandle create(PipelineInfo const &pipelineInfo);
        PipelineHandle create(PipelineResourceHandle const resourceHandle);
        void destroy(PipelineHandle const handle);
        Bool is_valid(PipelineHandle const handle) const;
        void update(PipelineHandle const handle, StringView const name, Variable const &value);
        void bind(PipelineHandle const handle);

        MaterialHandle create(MaterialInfo const &materialInfo);
        MaterialHandle create(MaterialResourceHandle const resourceHandle);
        void destroy(MaterialHandle const handle);
        Bool is_valid(MaterialHandle const handle) const;
        void update(MaterialHandle const handle, StringView const name, Variable const &value);
        void bind(MaterialHandle const handle);
        PipelineHandle get_pipeline(MaterialHandle const handle) const;

        RenderTargetHandle create(RenderTargetInfo const &renderTargetInfo);
        RenderTargetHandle create(RenderTargetResourceHandle const resourceHandle);
        void destroy(RenderTargetHandle const handle);
        Bool is_valid(RenderTargetHandle const handle) const;

        RenderViewHandle create(RenderViewInfo const &renderViewInfo, Camera const& camera);
        void destroy(RenderViewHandle const handle);
        Bool is_valid(RenderViewHandle const handle) const;
        void update(RenderViewHandle const handle, Float3 const &position, Float3 const &direction);
        void bind(RenderViewHandle const handle);
        void bind(RenderViewHandle const handle, Float3 const &position, Float3 const &direction);

        GeometryHandle create(GeometryInfo const &geometryInfo);
        GeometryHandle create(MeshResourceHandle const resourceHandle);
        void destroy(GeometryHandle const handle);
        Bool is_valid(GeometryHandle const handle) const;
        void bind(GeometryHandle const handle);

        SpriteHandle create(SpriteInfo const &spriteInfo);
        SpriteHandle create(SpriteResourceHandle const resourceHandle);
        void destroy(SpriteHandle const handle);
        Bool is_valid(SpriteHandle const handle) const;
        Sprite const& get(SpriteHandle const handle) const;

        Bool begin_frame();
        void end_frame();

        Bool begin_pass(RenderPassHandle const handle);
        void end_pass();

        // draw the bound objects (geometry, material, pipeline, render view)
        void draw();
        void draw(Object const &objectValues);
        void draw(Transform const &transform);
        void draw(Transform const &transform, Object const &objectValues);

        void draw_batch(Size const count, View const data);

        /**
         * @brief Notifies the render manager that the framebuffer size changed.
         * The expensive refresh is deferred and coalesced to the next frame.
         */
        void notify_framebuffer_resized(Int2 const size);

        /**
         * @brief Refreshes the render manager and recreates swapchain resources if needed.
         */
        void refresh();

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
            else if constexpr (std::is_same_v<ResourceHandle, SpriteResourceHandle> && std::is_same_v<Handle, SpriteHandle>)
            {
                return m_spriteCache;
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
            else if constexpr (std::is_same_v<ResourceHandle, MeshResourceHandle> && std::is_same_v<Handle, GeometryHandle>)
            {
                return m_geometryCache;
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
        Bool try_get_cached_handle(ResourceHandle const resourceHandle, Handle &outHandle)
        {
            Map<ResourceHandle, Handle> &cache = get_cache<ResourceHandle, Handle>();
            
            // Find existing handle in the cache
            auto it = cache.find(resourceHandle);
            if (it == cache.end())
            {
                return false;
            }
            
            // If found, check that it is still valid and return it
            Handle const handle = it->get_second();
            if (!is_valid(handle))
            {
                // No longer valid, so remove it from the cache and return false
                cache.remove(resourceHandle);
                return false;
            }

            // Valid handle found, set outHandle and return true
            outHandle = handle;
            return true;
        }

        template<typename ResourceHandle, typename Handle>
        Handle get_cached_handle(ResourceHandle const resourceHandle)
        {
            Map<ResourceHandle, Handle> &cache = get_cache<ResourceHandle, Handle>();
            
            // Find existing handle in the cache
            auto it = cache.find(resourceHandle);
            MINTY_ASSERT(it != cache.end(), ErrorCodeEnum::Argument_KeyNotFound);
            
            // If found, check that it is still valid and return it
            Handle const handle = it->get_second();
            MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);

            return handle;
        }

        template<typename ResourceHandle, typename Handle>
        void remove_cached_handle(Handle const handle)
        {
            Map<ResourceHandle, Handle> &cache = get_cache<ResourceHandle, Handle>();
            
            // Find the resource handle corresponding to the given handle
            for (auto it = cache.begin(); it != cache.end(); ++it)
            {
                if (it->get_second() == handle)
                {
                    cache.remove(it->get_first());
                    return;
                }
            }
        }

        template<typename ResourceHandle, typename Handle>
        Handle get_or_create_cached_handle(ResourceHandle const resourceHandle)
        {
            Handle cachedHandle;
            if (try_get_cached_handle<ResourceHandle, Handle>(resourceHandle, cachedHandle))
            {
                return cachedHandle;
            }
            
            // Create a new handle for the resource
            Handle newHandle = create(resourceHandle);
            return newHandle;
        }

#pragma endregion

#pragma region Variables

    private:
        Impl *mp_impl;

        // List if passes for rendering
        Vector<RenderPassHandle> m_passes;

        // Resources
        HandlePool<Sprite> m_spritePool;

        // Caches
        Map<MaterialResourceHandle, MaterialHandle> m_materialCache;
        Map<TextureResourceHandle, TextureHandle> m_textureCache;
        Map<ShaderResourceHandle, ShaderHandle> m_shaderCache;
        Map<RenderPassResourceHandle, RenderPassHandle> m_renderPassCache;
        Map<RenderTargetResourceHandle, RenderTargetHandle> m_renderTargetCache;
        Map<PipelineResourceHandle, PipelineHandle> m_pipelineCache;
        Map<ViewportResourceHandle, ViewportHandle> m_viewportCache;
        Map<MeshResourceHandle, GeometryHandle> m_geometryCache;
        Map<SpriteResourceHandle, SpriteHandle> m_spriteCache;

        Bool m_refreshPending = false;
        Int2 m_pendingFramebufferSize = Int2(0, 0);
        Int2 m_lastRefreshedFramebufferSize = Int2(0, 0);

        State m_state;

        static RenderManager *s_instance;

#pragma endregion
    };
}