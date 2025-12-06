#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/List.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Queue.h"
#include "Minty/Data/Vector.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Wrap/Wrapper.h"
#include <mutex>

#include "Minty/Asset/GenericAsset.h"

namespace Minty
{
	class Animation;
	class Animator;
	class AudioClip;
	class Camera;
	class Font;
	class FontVariant;
	class Image;
	class Material;
	class MaterialTemplate;
	class Mesh;
	class Prefab;
	class RenderPass;
	class RenderTarget;
	class Scene;
	class Shader;
	class ShaderModule;
	class Sprite;
	class SpriteAtlas;
	class Texture;
	class Viewport;
	struct AssetManagerInfo;
	struct RenderAttachment;

	class AssetManager;
	using AssetJob = Function<void(AssetManager&, UUID const)>;

	/**
	 * @class AssetManager
	 * @brief Handles loading and unloading of Assets.
	 */
	class AssetManager
		: public Manager
	{
#pragma region Types

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

		struct AssetData
		{
			Shared<Asset> asset = nullptr;
			Path path = "";
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an AssetManager with the given arguments.
		 * @param info The arguments for the AssetManager.
		 */
		AssetManager(AssetManagerInfo const& info);

		~AssetManager() override;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * Reads the UUID from the corresponding meta file for the given path to an Asset.
		 * @param path The path to the Asset.
		 * @return The UUID stored within the Asset's meta file.
		 */
		UUID read_id(Path const& path) const;

		/**
		 * @brief Called every frame.
		 * @param time The timestep for the frame update.
		 */
		void frame_update(Timestep const& time) override;

		/**
		 * @brief Waits for all asset loading/unloading operations to finish.
		 */
		void sync() override;

		/**
		 * @brief Checks if any assets are currently being loaded or unloaded.
		 * @return True if syncing is in progress.
		 */
		Bool is_syncing() const;

		/**
		 * @brief Loads the Wrap file at the given path into this AssetManager.
		 * @param path The path to the Wrap file.
		 * @return True if successfully loaded.
		 */
		Bool load_wrap(Path const& path);

		/**
		 * @brief Checks if an Asset with the given Path exists.
		 * @param path The Path to the Asset.
		 * @return True if the file is found.
		 */
		Bool exists(Path const& path) const;

		/**
		 * @brief Opens a Reader to the Asset at the given Path.
		 * @param path The Path to the Asset to read.
		 * @param reader The Reader to use.
		 * @return True if successfully found and opened.
		 */
		Bool open_reader(Path const& path, Reader*& reader) const;

		/**
		 * @brief Closes the given Reader.
		 * @param reader The Reader that was opened previously.
		 */
		void close_reader(Reader*& reader) const;

		/**
		 * @brief Opens a Writer to the Asset at the given Path.
		 * @param path The Path to the Asset to write to.
		 * @param writer The Writer to use.
		 * @return True if successfully opened.
		 */
		Bool open_writer(Path const& path, Writer*& writer) const;

		/**
		 * @brief Closes the given Writer.
		 * @param writer The Writer that was opened previously.
		 */
		void close_writer(Writer*& writer) const;

		/**
		 * @brief Queues the Asset at the given Path to be loaded.
		 * @param path The Path to the Asset.
		 * @param onCompletion The function to call when the Asset is loaded.
		 * @return The UUID of the Asset to be loaded.
		 */
		UUID schedule_load(Path const& path, AssetJob const& onCompletion = [](AssetManager& assetManager, UUID const id) {});

		/**
		 * @brief Loads the Asset at the given Path.
		 * @param path The Path to the Asset.
		 * @return A reference to the loaded Asset.
		 */
		Ref<Asset> load_asset(Path const& path);

		/**
		 * @brief Loads the Asset of the given type at the given Path.
		 * @tparam T The type of Asset.
		 * @param path The Path to the Asset.
		 * @return A reference to the loaded Asset.
		 */
		template<typename T>
		Ref<T> load(Path const& path)
		{
			return static_cast<Ref<T>>(load_asset(path));
		}

		/**
		 * @brief Loads the Asset specifically as an Animation at the given Path.
		 * @param path The Path to the Animation Asset.
		 * @return A reference to the loaded Animation Asset.
		 */
		template<>
		inline Ref<Animation> load<Animation>(Path const& path)
		{
			return load_animation(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as an Animator at the given Path.
		 * @param path The Path to the Animator Asset.
		 * @return A reference to the loaded Animator Asset.
		 */
		template<>
		inline Ref<Animator> load<Animator>(Path const& path)
		{
			return load_animator(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as an AudioClip at the given Path.
		 * @param path The Path to the AudioClip Asset.
		 * @return A reference to the loaded AudioClip Asset.
		 */
		template<>
		inline Ref<AudioClip> load<AudioClip>(Path const& path)
		{
			return load_audio_clip(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a Camera at the given Path.
		 * @param path The Path to the Camera Asset.
		 * @return A reference to the loaded Camera Asset.
		 */
		template<>
		inline Ref<Camera> load<Camera>(Path const& path)
		{
			return load_camera(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a Font at the given Path.
		 * @param path The Path to the Font Asset.
		 * @return A reference to the loaded Font Asset.
		 */
		template<>
		inline Ref<Font> load<Font>(Path const& path)
		{
			return load_font(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a FontVariant at the given Path.
		 * @param path The Path to the FontVariant Asset.
		 * @return A reference to the loaded FontVariant Asset.
		 */
		template<>
		inline Ref<FontVariant> load<FontVariant>(Path const& path)
		{
			return load_font_variant(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as an Image at the given Path.
		 * @param path The Path to the Image Asset.
		 * @return A reference to the loaded Image Asset.
		 */
		template<>
		inline Ref<Image> load<Image>(Path const& path)
		{
			return load_image(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a Material at the given Path.
		 * @param path The Path to the Material Asset.
		 * @return A reference to the loaded Material Asset.
		 */
		template<>
		inline Ref<Material> load<Material>(Path const& path)
		{
			return load_material(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a MaterialTemplate at the given Path.
		 * @param path The Path to the MaterialTemplate Asset.
		 * @return A reference to the loaded MaterialTemplate Asset.
		 */
		template<>
		inline Ref<MaterialTemplate> load<MaterialTemplate>(Path const& path)
		{
			return load_material_template(path, read_id(path));
		}
		
		/**
		 * @brief Loads the Asset specifically as a Mesh at the given Path.
		 * @param path The Path to the Mesh Asset.
		 * @return A reference to the loaded Mesh Asset.
		 */
		template<>
		inline Ref<Mesh> load<Mesh>(Path const& path)
		{
			return load_mesh(path, read_id(path));
		}
		
		/**
		 * @brief Loads the Asset specifically as a Prefab at the given Path.
		 * @param path The Path to the Prefab Asset.
		 * @return A reference to the loaded Prefab Asset.
		 */
		template<>
		inline Ref<Prefab> load<Prefab>(Path const& path)
		{
			return load_prefab(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a RenderPass at the given Path.
		 * @param path The Path to the RenderPass Asset.
		 * @return A reference to the loaded RenderPass Asset.
		 */
		template<>
		inline Ref<RenderPass> load<RenderPass>(Path const& path)
		{
			return load_render_pass(path, read_id(path));
		}
		
		/**
		 * @brief Loads the Asset specifically as a Shader at the given Path.
		 * @param path The Path to the Shader Asset.
		 * @return A reference to the loaded Shader Asset.
		 */
		template<>
		inline Ref<Shader> load<Shader>(Path const& path)
		{
			return load_shader(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a ShaderModule at the given Path.
		 * @param path The Path to the ShaderModule Asset.
		 * @return A reference to the loaded ShaderModule Asset.
		 */
		template<>
		inline Ref<ShaderModule> load<ShaderModule>(Path const& path)
		{
			return load_shader_module(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a Sprite at the given Path.
		 * @param path The Path to the Sprite Asset.
		 * @return A reference to the loaded Sprite Asset.
		 */
		template<>
		inline Ref<Sprite> load<Sprite>(Path const& path)
		{
			return load_sprite(path, read_id(path));
		}

		/**
		 * @brief Loads the Asset specifically as a Texture at the given Path.
		 * @param path The Path to the Texture Asset.
		 * @return A reference to the loaded Texture Asset.
		 */
		template<>
		inline Ref<Texture> load<Texture>(Path const& path)
		{
			return load_texture(path, read_id(path));
		}

		/**
		 * @brief Marks the Asset with the given ID for unloading.
		 * @param id The ID of the Asset to unload.
		 * @param onCompletion The function to call when the Asset is unloaded.
		 */
		void schedule_unload(UUID const id, AssetJob const& onCompletion = [](AssetManager& assetManager, UUID const id) {});

		/**
		 * @brief Unloads the Asset with the given ID immediately.
		 * @param id The ID of the Asset to unload.
		 */
		void unload(UUID const id);

		/**
		 * @brief Reloads the Asset with the given ID.
		 * @param id The ID of the Asset.
		 */
		void reload(UUID const id);

		/**
		 * @brief Unloads all Assets stored within this AssetManager.
		 */
		void unload_all();

		/**
		 * @brief Creates a new Asset of the given type.
		 * @tparam T The type of Asset to create.
		 * @tparam Args The argument types to create the Asset.
		 * @param args The arguments to create the Asset.
		 * @return A reference to the newly created Asset.
		 */
		template<typename T, typename... Args>
		Ref<T> create(Args&&... args)
		{
			// create new asset
			Shared<T> asset = T::create(std::forward<Args>(args)...);

			// add to asset manager
			add(asset);

			return asset.to_ref();
		}

		/**
		 * @brief Adds the given Asset to this AssetManager.
		 * @param path The Path to the Asset.
		 * @param asset The Asset to add.
		 */
		void add(Path const& path, Shared<Asset> const& asset);

		/**
		 * @brief Adds the given Asset to this AssetManager.
		 * @param asset The Asset to add.
		 */
		void add(Shared<Asset> const& asset)
		{
			add(Path(), asset);
		}

		/**
		 * @brief Checks if there is an Asset with the given ID within this AssetManager.
		 * @param id The ID to check.
		 * @return True if it belongs to a loaded Asset.
		 */
		Bool contains(UUID const id) const;

		/**
		 * @brief Gets the Asset with the given ID.
		 * @param id The ID of the loaded Asset to get.
		 * @return A reference to the loaded Asset with the given ID, or a null Asset if not found.
		 */
		Ref<Asset> get_asset(UUID const id) const;

		/**
		 * @brief Gets the Asset with the given ID.
		 * @tparam T The Type of Asset.
		 * @param id The ID of the loaded Asset to get.
		 * @return A reference to the loaded Asset with the given ID, or a null Asset if not found.
		 */
		template<typename T>
		Ref<T> get(UUID const id) const
		{
			return get_asset(id).cast<T>();
		}

		/**
		 * @brief Gets the Asset with the given ID.
		 * @param id The ID of the loaded Asset to get.
		 * @return A reference to the loaded Asset with the given ID.
		 */
		Ref<Asset> at_asset(UUID const id) const;

		/**
		 * @brief Gets the Asset with the given ID.
		 * @tparam T The type of Asset.
		 * @param id The ID of the loaded Asset to get.
		 * @return A reference to the loaded Asset with the given ID.
		 */
		template<typename T>
		Ref<T> at(UUID const id) const
		{
			return static_cast<Ref<T>>(at_asset(id));
		}

		/**
		 * @brief Gets all of the loaded Assets with the given type.
		 * @tparam T The type of asset to get.
		 * @return A Vector containing all of the relevant Assets.
		 */
		template<typename T>
		Vector<Ref<T>> get_by_type() const
		{
			TypeID typeId = typeid(T);
			AssetType assetType = Asset::get_asset_type(typeId);

			auto found = m_assetTypes.find(assetType);
			if (found == m_assetTypes.end())
			{
				return Vector<Ref<T>>();
			}

			Vector<Ref<T>> assets(found->get_second().get_size());
			for (UUID const id : found->get_second())
			{
				assets.add(at<T>(id));
			}

			return assets;
		}

		/**
		 * @brief Gets the Path to the Asset with the given ID.
		 * @param id The ID of the loaded Asset.
		 * @return The Path, if paths are being saved.
		 */
		Path get_asset_path(UUID const id) const;

		/**
		 * @brief Gets the name of the Asset with the given ID.
		 * @param id The ID of the loaded Asset.
		 * @return The name, if paths are being saved.
		 */
		String get_asset_name(UUID const id) const;

		/**
		 * @brief Removes the Asset with the given ID from this AssetManager.
		 * @param id The ID of the Asset to remove.
		 * @return The Asset that was removed.
		 */
		Shared<Asset> remove(UUID const id);

		/**
		 * @brief Clones the loaded Asset with the given ID.
		 * @tparam T The Type of Asset to clone.
		 * @param id The ID of the loaded Asset to clone.
		 * @return A reference to the newly cloned Asset.
		 */
		template<typename T>
		Ref<T> clone(UUID const id)
		{
			// get asset to clone
			Ref<T> asset = get<T>(id);

			// do nothing if null
			if (asset == nullptr)
			{
				return Ref<T>();
			}

			// create new asset of same type
			UUID newId = UUID::create();
			Shared<T> newAsset = T::create();

			// copy data
			*newAsset.get() = *asset.get();
			newAsset.get()->m_uuid = newId;

			// add to asset manager
			add(newAsset);

			// return cloned asset
			return newAsset.to_ref();
		}

		/**
		 * @brief Gets a list of all the Assets that depend on the Asset with the given ID.
		 * @param id The ID to the loaded Asset.
		 * @return A list of all loaded Assets that rely on the Asset with the given ID.
		 */
		Vector<Ref<Asset>> get_dependents(UUID const id) const;

		/**
		 * @brief Reads all of the bytes from the File at the given Path.
		 * @param path The Path to the Asset.
		 * @return A list of bytes from the File.
		 */
		Vector<Byte> read_bytes(Path const& path) const;

		/**
		 * @brief Reads the text from the file at the given Path.
		 * @param path The Path to the Asset.
		 * @return The text of the File, as a String.
		 */
		String read_text(Path const& path) const;

		/**
		 * @brief Reads the lines from the file at the given Path.
		 * @param path The Path to the Asset.
		 * @return A list of lines of text within the File.
		 */
		Vector<String> read_lines(Path const& path) const;

	private:
		// determines where the file is located at the given path
		Location get_location(Path const& path) const;

		// opens a file at the given path
		File* open(Path const& path) const;

		// closes an opened file
		void close(File* file) const;

		// creates a new asset with the given path and args (from a load_xxx function)
		template<typename T, typename... Args>
		Ref<T> create_from_loaded(Path const& path, Args&& ...args)
		{
			// create new asset
			Shared<T> asset = T::create(std::forward<Args>(args)...);

			// trigger load
			asset->on_load();

			// add to asset manager
			add(path, asset);

			return asset.to_ref();
		}

		void run_completion_jobs();

		// loads the Asset at the given Path, using the AssetType to determine how to load it
		inline Ref<Asset> load_asset(Path const& path, AssetType const type)
		{
			return load_asset(path, type, read_id(path));
		}

		// loads the Asset at the given Path, using the AssetType to determine how to load it and the given ID
		Ref<Asset> load_asset(Path const& path, AssetType const type, UUID const id);

#pragma region Load

#pragma region Helper

	private:
		template<typename T>
		Int find_dependency(Path const& path, Reader& reader, String const& name, Ref<T>& asset, bool required) const
		{
			UUID id{};

			// if nothing read, set to null
			if (!reader.read(name, id))
			{
				if (required)
				{
					MINTY_ERROR_F(ErrorCode::Asset_MissingDependency, path, name);
				}

				asset.release();
				return 1;
			}

			// something read
			if (Int result = check_dependency(id, path, name, required))
			{
				asset.release();
				return result;
			}

			// load asset
			asset = get<T>(id);
			return 0;
		}

		Int check_dependency(UUID const id, Path const& path, String const& name, Bool const required) const;

		Int read_attachment(Path const& path, Reader& reader, String const& name, RenderAttachment& attachment, Bool const required) const;

#pragma endregion

	private:
		Ref<GenericAsset> load_generic(Path const& path, UUID const id);

		Shared<Image> create_image(Path const& path, UUID const id);

		Ref<Animation> load_animation(Path const& path, UUID const id);

		Ref<Animator> load_animator(Path const& path, UUID const id);

		Ref<AudioClip> load_audio_clip(Path const& path, UUID const id);

		Ref<Camera> load_camera(Path const& path, UUID const id);

		Ref<Font> load_font(Path const& path, UUID const id);

		Ref<FontVariant> load_font_variant(Path const& path, UUID const id);

		Ref<Image> load_image(Path const& path, UUID const id);

		Ref<Material> load_material(Path const& path, UUID const id);

		Ref<MaterialTemplate> load_material_template(Path const& path, UUID const id);

		Ref<Mesh> load_mesh_obj(Path const& path, UUID const id);

		Ref<Mesh> load_mesh(Path const& path, UUID const id);

		Ref<Prefab> load_prefab(Path const& path, UUID const id);

		Ref<RenderPass> load_render_pass(Path const& path, UUID const id);

		Ref<RenderTarget> load_render_target(Path const& path, UUID const id);

		Ref<Shader> load_shader(Path const& path, UUID const id);

		Ref<ShaderModule> load_shader_module(Path const& path, UUID const id);

		Ref<Sprite> load_sprite(Path const& path, UUID const id);

		Ref<SpriteAtlas> load_sprite_atlas(Path const& path, UUID const id);

		Ref<Texture> load_texture(Path const& path, UUID const id);

#pragma endregion

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Creates a new AssetManager.
		 * @param info The arguments.
		 * @return A AssetManager Owner.
		 */
		static Unique<AssetManager> create(AssetManagerInfo const& info);

		/**
		 * @brief Creates a new AssetManager with default settings.
		 * @return A AssetManager Owner.
		 */
		static Unique<AssetManager> create();

		/**
		 * @brief Gets the active Context's AssetManager.
		 * @return The AssetManager.
		 */
		static Unique<AssetManager> const& get_instance();

		/**
		 * @brief Gets the active Context's AssetManager.
		 * @return A reference to the AssetManager.
		 */
		static AssetManager& get_singleton();

#pragma endregion

#pragma region Variables

	private:
		Bool m_savePaths;
		Map<UUID, AssetData> m_assets;
		Map<AssetType, Set<UUID>> m_assetTypes;
		Map<UUID, Handle> m_handles;
		Queue<Tuple<UUID, AssetJob>> m_onCompletions;
		mutable std::mutex m_assetsMutex;
		mutable std::mutex m_handlesMutex;
		mutable std::mutex m_onCompletionsMutex;

		Wrapper m_wrapper;

#pragma endregion
	};
}