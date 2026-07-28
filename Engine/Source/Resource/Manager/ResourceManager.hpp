#pragma once

/**
 * @file ResourceManager.hpp
 * @brief Header file defining the ResourceManager class for managing assets.
 * @author Mitchell Talyat
 */

#include "Core/Data/Shared.hpp"
#include "Core/Data/Unique.hpp"
#include "Core/Data/UUID.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Core/Data/Path.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Wrap/Wrapper.hpp"
#include "Core/Type/Function.hpp"
#include "Core/Data/HandlePool.hpp"
#include "Core/Data/Any.hpp"
#include "Core/File/FileFlags.hpp"
#include "Resource/Data/ResourcePool.hpp"

#include "Resource/Clip/ClipResource.hpp"
#include "Resource/Mesh/MeshResource.hpp"
#include "Resource/Generic/GenericResource.hpp"
#include "Resource/Image/ImageResource.hpp"
#include "Resource/Material/MaterialResource.hpp"
#include "Resource/Pipeline/PipelineResource.hpp"
#include "Resource/Prefab/PrefabResource.hpp"
#include "Resource/RenderPass/RenderPassResource.hpp"
#include "Resource/RenderTarget/RenderTargetResource.hpp"
#include "Resource/Shader/ShaderResource.hpp"
#include "Resource/Texture/TextureResource.hpp"
#include "Resource/Viewport/ViewportResource.hpp"

namespace Minty
{
    struct ResourceManagerInfo;
    class Reader;
    class ResourceManager;

    /**
     * @brief The ResourceManager class is responsible for managing the loading, storage, and retrieval of assets in the engine.
     */
    class ResourceManager
    {
#pragma region Types

    public:
        using ResourceLoadFunction = Function<Any(Reader &)>;

    private:
        enum class Location
        {
            // file DNE
            Undefined,
            // file is in the file system
            FileSystem,
            // file is in a Wrap file
            Wrapper
        };

        struct ResourceData
        {
            Path path;
            UUID id;
            Any asset;
        };

#pragma endregion

#pragma region Constructors

    public:
        /**
         * @brief Creates an ResourceManager with the given arguments.
         * @param info The arguments for the ResourceManager.
         */
        ResourceManager(ResourceManagerInfo const &info);

        ~ResourceManager();

#pragma endregion

#pragma region Methods

    public:
        Bool load_wrap(Path const &path);

        inline Bool exists(Path const &path) const
        {
            return find_location(path) != Location::Undefined;
        }
        Unique<File> open_file(Path const &path, FileFlags const flags = FileFlagsEnum::Read | FileFlagsEnum::Binary) const;

        Unique<Stream> open_stream(Path const &path, FileFlags const flags = FileFlagsEnum::Read | FileFlagsEnum::Binary) const;

        Unique<Reader> open_reader(Path const &path) const;

        Unique<Writer> open_writer(Path const &path) const;

        Vector<Byte> read_file(Path const &path) const;

        template <typename T>
        Handle<T> read(Reader &reader, StringView const name)
        {
            // Read the UUID
            UUID id;
            if (!reader.read(name, id))
            {
                return INVALID_HANDLE;
            }

            // Get the handle for the UUID
            ResourcePool<T> const &pool = get_pool<T>();
            Handle<T> const handle = pool.find_handle(id);
            return handle;
        }

        template <typename T>
        Bool contains(UUID const &id) const
        {
            ResourcePool<T> const &pool = get_pool<T>();
            return pool.contains(id);
        }

        template <typename T>
        Bool contains(Handle<T> const handle) const
        {
            ResourcePool<T> const &pool = get_pool<T>();
            return pool.contains(handle);
        }

        template <typename T>
        Handle<T> add(T &&asset, UUID const &id)
        {
            ResourcePool<T> &pool = get_pool<T>();
            Handle<T> handle = pool.add(std::forward<T>(asset), id);
            return handle;
        }

        template <typename T>
            requires Serializable<T>
        Handle<T> load(Path const &path)
        {
            // Open the reader
            Unique<Reader> const reader = open_reader(path);
            if (!reader)
            {
                MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, path.get_string().get_data());
                return INVALID_HANDLE;
            }

            // Read the UUID from the beginning of the file
            UUID const id = load_id(reader);

            // The second line will have the start of the actual data, so we can load the asset from there onwards

            // Create a temporary T to deserialize into, then add it to the manager
            T resource{};
            if (!Serializer<T>::deserialize(*reader, resource))
            {
                MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, path.get_string().get_data());
                return INVALID_HANDLE;
            }

            // Add the asset to the manager and return its handle
            return add(std::move(resource), id);
        }

        template <typename T>
        void unload(UUID const &id)
        {
            ResourcePool<T> &pool = get_pool<T>();
            Handle<T> const handle = pool.find_handle(id);
            MINTY_ASSERT(handle != INVALID_HANDLE, ErrorCodeEnum::Argument_KeyNotFound);
            pool.remove(handle);
        }

        template <typename T>
        void unload(Handle<T> const handle)
        {
            ResourcePool<T> &pool = get_pool<T>();
            pool.remove(handle);
        }

        template <typename T, typename... Args>
        Handle<T> create(Args &&...args)
        {
            // Create the resource and add it to the manager with a new UUID, then return the handle
            T resource(std::forward<Args>(args)...);
            UUID id = UUID::generate();
            return add(std::move(resource), id);
        }

        template <typename T>
        Handle<T> find_handle(UUID const &id) const
        {
            ResourcePool<T> const &pool = get_pool<T>();
            return pool.find_handle(id);
        }

        template <typename T>
        UUID const &find_id(Handle<T> const handle) const
        {
            ResourcePool<T> const &pool = get_pool<T>();
            return pool.find_uuid(handle);
        }

        template <typename T>
        T &at(Handle<T> const &handle)
        {
            ResourcePool<T> &pool = get_pool<T>();
            return pool.at(handle);
        }

        template <typename T>
        T const &at(Handle<T> const &handle) const
        {
            ResourcePool<T> const &pool = get_pool<T>();
            return pool.at(handle);
        }

        template <typename T>
        T *get(Handle<T> const &handle)
        {
            ResourcePool<T> &pool = get_pool<T>();
            return pool.get(handle);
        }

        template <typename T>
        T const *get(Handle<T> const &handle) const
        {
            ResourcePool<T> const &pool = get_pool<T>();
            return pool.get(handle);
        }

        template <typename T>
        Bool deserialize(Reader& reader, StringView const name, Handle<T>& handle) const
        {
            // Read the UUID
            UUID id;
            if (!reader.read(name, id))
            {
                return false;
            }

            // Get the handle for the UUID
            ResourcePool<T> const &pool = get_pool<T>();
            handle = pool.find_handle(id);
            return handle != INVALID_HANDLE;
        }

        static ResourceManager &get_instance();

    private:
        Location find_location(Path const &path) const;

        static UUID load_id(Unique<Reader> const &metaReader);

        static Path get_meta_path(Path const &path);

        template <typename T>
        ResourcePool<T> const &get_pool() const
        {
            if constexpr (std::is_same_v<T, ClipResource>)
            {
                return m_assets_clips;
            }
            else if constexpr (std::is_same_v<T, MeshResource>)
            {
                return m_assets_geometry;
            }
            else if constexpr (std::is_same_v<T, GenericResource>)
            {
                return m_assets_generic;
            }
            else if constexpr (std::is_same_v<T, ImageResource>)
            {
                return m_assets_images;
            }
            else if constexpr (std::is_same_v<T, MaterialResource>)
            {
                return m_assets_materials;
            }
            else if constexpr (std::is_same_v<T, PipelineResource>)
            {
                return m_assets_pipelines;
            }
            else if constexpr (std::is_same_v<T, PrefabResource>)
            {
                return m_assets_prefabs;
            }
            else if constexpr (std::is_same_v<T, RenderPassResource>)
            {
                return m_assets_renderPasses;
            }
            else if constexpr (std::is_same_v<T, RenderTargetResource>)
            {
                return m_assets_renderTargets;
            }
            else if constexpr (std::is_same_v<T, ShaderResource>)
            {
                return m_assets_shaders;
            }
            else if constexpr (std::is_same_v<T, TextureResource>)
            {
                return m_assets_textures;
            }
            else if constexpr (std::is_same_v<T, ViewportResource>)
            {
                return m_assets_viewports;
            }
            else
            {
                // TODO: create way to have a custom type Map<TypeID, ResourcePool<Any>> for custom types
                MINTY_ABORT_A(ErrorCodeEnum::NotSupported, typeid(T).name());
                static ResourcePool<T> dummyPool;
                return dummyPool;
            }
        }

        template <typename T>
        ResourcePool<T> &get_pool()
        {
            return const_cast<ResourcePool<T> &>(static_cast<ResourceManager const *>(this)->get_pool<T>());
        }

#pragma endregion

#pragma region Variables

    public:
        Wrapper m_wrapper;
        ResourcePool<ClipResource> m_assets_clips;
        ResourcePool<MeshResource> m_assets_geometry;
        ResourcePool<GenericResource> m_assets_generic;
        ResourcePool<ImageResource> m_assets_images;
        ResourcePool<MaterialResource> m_assets_materials;
        ResourcePool<PipelineResource> m_assets_pipelines;
        ResourcePool<PrefabResource> m_assets_prefabs;
        ResourcePool<RenderPassResource> m_assets_renderPasses;
        ResourcePool<RenderTargetResource> m_assets_renderTargets;
        ResourcePool<ShaderResource> m_assets_shaders;
        ResourcePool<TextureResource> m_assets_textures;
        ResourcePool<ViewportResource> m_assets_viewports;

        static ResourceManager *s_instance;

#pragma endregion
    };
}