#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Context/Manager.h"
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
	class Image;
	class Material;
	class MaterialTemplate;
	class Mesh;
	struct RenderAttachment;
	class RenderPass;
	class Scene;
	class Shader;
	class ShaderModule;
	class Sprite;
	class Texture;
	class Viewport;

	class AssetManager;
	using AssetJob = Function<void(AssetManager&, UUID const)>;

	/// <summary>
	/// Arguments for creates an AssetManager.
	/// </summary>
	struct AssetManagerBuilder
	{
		/// <summary>
		/// A list of Wrap files to load on initialization.
		/// </summary>
		List<Path> wraps = {};

#ifdef MINTY_DEBUG
		/// <summary>
		/// If true, the AssetManager will save the paths of the Assets.
		/// </summary>
		Bool savePaths = true;
#else
		/// <summary>
		/// If true, the AssetManager will save the paths of the Assets.
		/// </summary>
		Bool savePaths = false;
#endif
	};

	/// <summary>
	/// Handles loading and unloading of Assets.
	/// </summary>
	class AssetManager
		: public Manager
	{
#pragma region Classes

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
			Owner<Asset> asset = nullptr;
			Path path = "";
		};

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

#pragma region Constructors

	public:
		AssetManager(AssetManagerBuilder const& builder);

		~AssetManager()
		{
			MINTY_ASSERT_ERROR(!is_initialized(), "AssetManager is not disposed before destruction.");
		}

#pragma endregion

#pragma region Methods

	private:
		// determines where the file is located at the given path
		Location get_location(Path const& path) const;

		// read the ID from the corresponding meta file for the given path to an Asset
		ID read_id(Path const& path) const;

		// opens a file at the given path
		File* open(Path const& path) const;

		// closes an opened file
		void close(File* file) const;

		// creates a new asset with the given path and args (from a load_xxx function)
		template<typename T, typename... Args>
		Ref<T> create_from_loaded(Path const& path, Args&& ...args)
		{
			// create new asset
			Owner<T> asset = T::create(std::forward<Args>(args)...);

			// add to asset manager
			add(path, asset);

			return asset.create_ref();
		}

	public:
		/// <summary>
		/// Shuts down the AssetManager.
		/// </summary>
		void dispose() override;

		/// <summary>
		/// Called every frame.
		/// </summary>
		void update(Time const& time);

		/// <summary>
		/// If any Assets are being loaded or unloaded, wait until they are finished.
		/// </summary>
		void sync() override;

		/// <summary>
		/// Checks if any Assets are being loaded or unloaded.
		/// </summary>
		Bool is_syncing() const;

		/// <summary>
		/// Loads the Wrap at the given location into this AssetManager.
		/// </summary>
		/// <param name="path">The path to the Wrap file.</param>
		/// <returns>True if successfully loaded.</returns>
		Bool load_wrap(Path const& path);

		/// <summary>
		/// Checks if an Asset with the given Path exists.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>True, if the file is found.</returns>
		Bool exists(Path const& path) const;

		/// <summary>
		/// Opens a Reader to the Asset at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset to read.</param>
		/// <param name="reader">The Reader to use.</param>
		/// <returns>True, if successfully found and opened.</returns>
		Bool open_reader(Path const& path, Reader*& reader) const;

		/// <summary>
		/// Closes the given Reader.
		/// </summary>
		/// <param name="reader">The Reader that was opened previously.</param>
		void close_reader(Reader*& reader) const;

		/// <summary>
		/// Opens a Writer to the Asset at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset to writer to.</param>
		/// <param name="writer">The Writer to use.</param>
		/// <returns>True, if successfully opened.</returns>
		Bool open_writer(Path const& path, Writer*& writer) const;

		/// <summary>
		/// Closes the given Writer.
		/// </summary>
		/// <param name="writer">The Writer that was opened previously.</param>
		void close_writer(Writer*& writer) const;

		/// <summary>
		/// Queues the Asset at the given Path to be loaded.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <param name="onCompletion">The function to call when the Asset is loaded.</param>
		/// <returns>The UUID of the Asset to be loaded.</returns>
		UUID schedule_load(Path const& path, AssetJob const& onCompletion = [](AssetManager& assetManager, UUID const id) {});

		/// <summary>
		/// Loads the Asset at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>A reference to the loaded Asset.</returns>
		Ref<Asset> load_asset(Path const& path);

		/// <summary>
		/// Loads the Asset of the given type at the given Path.
		/// </summary>
		/// <typeparam name="T">The type of Asset.</typeparam>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>A reference to the loaded Asset.</returns>
		template<typename T>
		Ref<T> load(Path const& path)
		{
			return static_cast<Ref<T>>(load_asset(path));
		}

		/// <summary>
		/// Loads the Asset specifically as a Animation at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Animation Asset.</param>
		/// <returns>A reference to the loaded Animation Asset.</returns>
		template<>
		Ref<Animation> load<Animation>(Path const& path)
		{
			return load_animation(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a Animator at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Animator Asset.</param>
		/// <returns>A reference to the loaded Animator Asset.</returns>
		template<>
		Ref<Animator> load<Animator>(Path const& path)
		{
			return load_animator(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a AudioClip at the given Path.
		/// </summary>
		/// <param name="path">The Path to the AudioClip Asset.</param>
		/// <returns>A reference to the loaded AudioClip Asset.</returns>
		template<>
		Ref<AudioClip> load<AudioClip>(Path const& path)
		{
			return load_audio_clip(path);
		}

		/// <summary>
		/// Loads the Asset specifically as an Image at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Image Asset.</param>
		/// <returns>A reference to the loaded Image Asset.</returns>
		template<>
		Ref<Image> load<Image>(Path const& path)
		{
			return load_image(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a Material at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Material Asset.</param>
		/// <returns>A reference to the loaded Material Asset.</returns>
		template<>
		Ref<Material> load<Material>(Path const& path)
		{
			return load_material(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a MaterialTemplate at the given Path.
		/// </summary>
		/// <param name="path">The Path to the MaterialTemplate Asset.</param>
		/// <returns>A reference to the loaded MaterialTemplate Asset.</returns>
		template<>
		Ref<MaterialTemplate> load<MaterialTemplate>(Path const& path)
		{
			return load_material_template(path);
		}
		
		/// <summary>
		/// Loads the Asset specifically as a Mesh at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Mesh Asset.</param>
		/// <returns>A reference to the loaded Mesh Asset.</returns>
		template<>
		Ref<Mesh> load<Mesh>(Path const& path)
		{
			return load_mesh(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a RenderPass at the given Path.
		/// </summary>
		/// <param name="path">The Path to the RenderPass Asset.</param>
		/// <returns>A reference to the loaded RenderPass Asset.</returns>
		template<>
		Ref<RenderPass> load<RenderPass>(Path const& path)
		{
			return load_render_pass(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a Scene at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Scene Asset.</param>
		/// <returns>A reference to the loaded Scene Asset.</returns>
		template<>
		Ref<Scene> load<Scene>(Path const& path)
		{
			return load_scene(path);
		}
		
		/// <summary>
		/// Loads the Asset specifically as a Shader at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Shader Asset.</param>
		/// <returns>A reference to the loaded Shader Asset.</returns>
		template<>
		Ref<Shader> load<Shader>(Path const& path)
		{
			return load_shader(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a ShaderModule at the given Path.
		/// </summary>
		/// <param name="path">The Path to the ShaderModule Asset.</param>
		/// <returns>A reference to the loaded ShaderModule Asset.</returns>
		template<>
		Ref<ShaderModule> load<ShaderModule>(Path const& path)
		{
			return load_shader_module(path);
		}

		/// <summary>
		/// Loads the Asset specifically as a Texture at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Texture Asset.</param>
		/// <returns>A reference to the loaded Texture Asset.</returns>
		template<>
		Ref<Texture> load<Texture>(Path const& path)
		{
			return load_texture(path);
		}

		/// <summary>
		/// Marks the Asset with the given ID for unloading.
		/// </summary>
		/// <param name="id">The ID of the Asset to unload.</param>
		/// <param name="onCompletion">The function to call when the Asset is unloaded.</param>
		void schedule_unload(UUID const id, AssetJob const& onCompletion = [](AssetManager& assetManager, UUID const id) {});

		/// <summary>
		/// Unloads the Asset with the given ID immediately.
		/// </summary>
		/// <param name="id">The ID of the Asset to unload.</param>
		void unload(UUID const id);

		/// <summary>
		/// Unloads all Assets stored within this AssetManager.
		/// </summary>
		void unload_all();

		/// <summary>
		/// Creates a new Asset of the given type.
		/// </summary>
		/// <typeparam name="T">The type of Asset to create.</typeparam>
		/// <typeparam name="...Args">The argument types to create the Asset.</typeparam>
		/// <param name="...args">The arguments to create the Asset.</param>
		/// <returns>A reference to the newly created Asset.</returns>
		template<typename T, typename... Args>
		Ref<T> create(Args&&... args)
		{
			// create new asset
			Owner<T> asset = T::create(std::forward<Args>(args)...);

			// add to asset manager
			add(asset);

			return asset.create_ref();
		}

		/// <summary>
		/// Adds the given Asset to this AssetManager.
		/// </summary>
		/// <param name="path">The Path to the </param>
		/// <param name="asset">The Asset to add.</param>
		void add(Path const& path, Owner<Asset> const& asset);

		/// <summary>
		/// Adds the given Asset to this AssetManager.
		/// </summary>
		/// <param name="asset">The Asset to add.</param>
		void add(Owner<Asset> const& asset)
		{
			add(Path(), asset);
		}

		/// <summary>
		/// Checks if there is an Asset with the given ID within this AssetManager.
		/// </summary>
		/// <param name="id">The ID to check.</param>
		/// <returns>True, if it belongs to a loaded Asset.</returns>
		Bool contains(UUID const id) const;

		/// <summary>
		/// Gets the Asset with the given ID.
		/// </summary>
		/// <param name="id">The ID of the loaded Asset to get.</param>
		/// <returns>A reference to the loaded Asset with the given ID, or a null Asset if not found.</returns>
		Ref<Asset> get_asset(UUID const id) const;

		/// <summary>
		/// Gets the Asset with the given ID.
		/// </summary>
		/// <typeparam name="T">The Type of Asset.</typeparam>
		/// <param name="id">The ID of the loaded Asset to get.</param>
		/// <returns>A reference to the loaded Asset with the given ID, or a null Asset if not found.</returns>
		template<typename T>
		Ref<T> get(UUID const id) const
		{
			return get_asset(id).cast_to<T>();
		}

		/// <summary>
		/// Gets the Asset with the given ID.
		/// </summary>
		/// <param name="id">The ID of the loaded Asset to get.</param>
		/// <returns>A reference to the loaded Asset with the given ID.</returns>
		Ref<Asset> at_asset(UUID const id) const;

		/// <summary>
		/// Gets the Asset with the given ID.
		/// </summary>
		/// <typeparam name="T">The type of Asset.</typeparam>
		/// <param name="id">The ID of the loaded Asset to get.</param>
		/// <returns>A reference to the loaded Asset with the given ID.</returns>
		template<typename T>
		Ref<T> at(UUID const id) const
		{
			return static_cast<Ref<T>>(at_asset(id));
		}

		/// <summary>
		/// Gets all of the loaded Assets with the given type.
		/// </summary>
		/// <typeparam name="T">The type of asset to get.</typeparam>
		/// <returns>A Vector containing all of the relevant Assets.</returns>
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

		/// <summary>
		/// Gets the Path to the Asset with the given ID.
		/// </summary>
		/// <param name="id">The ID of the loaded Asset.</param>
		/// <returns>The Path, if paths are being saved.</returns>
		Path get_asset_path(UUID const id) const;

		/// <summary>
		/// Gets the name of the Asset with the given ID.
		/// </summary>
		/// <param name="id">The ID of the loaded Asset.</param>
		/// <returns>The name, if paths are being saved.</returns>
		String get_asset_name(UUID const id) const;

		/// <summary>
		/// Removes the Asset with the given ID from this AssetManager.
		/// </summary>
		/// <param name="id">The ID of the Asset to remove.</param>
		/// <returns>The Asset that was removed.</returns>
		Owner<Asset> remove(UUID const id);

		/// <summary>
		/// Clones the loaded Asset with the given ID.
		/// </summary>
		/// <typeparam name="T">The Type of Asset to clone.</typeparam>
		/// <param name="id">The ID of the loaded Asset to clone.</param>
		/// <returns>A reference to the newly cloned Asset.</returns>
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
			Owner<T> newAsset = T::create();

			// copy data
			*newAsset.get() = *asset.get();
			newAsset.get()->m_uuid = newId;

			// add to asset manager
			add(newAsset);

			// return cloned asset
			return newAsset.create_ref();
		}

		/// <summary>
		/// Gets a list of all the Assets that depend on the Asset with the given ID.
		/// </summary>
		/// <param name="id">The ID to the loaded Asset.</param>
		/// <returns>A list of all loaded Assets that rely on the Asset with the given ID.</returns>
		Vector<Ref<Asset>> get_dependents(UUID const id) const;

		/// <summary>
		/// Reads all of the bytes from the File at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>A list of bytes from the File.</returns>
		Vector<Byte> read_bytes(Path const& path) const;

		/// <summary>
		/// Reads the text from the file at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>The text of the File, as a String.</returns>
		String read_text(Path const& path) const;

		/// <summary>
		/// Reads the lines from the file at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>A list of lines of text within the File.</returns>
		Vector<String> read_lines(Path const& path) const;

#pragma region Load

#pragma region Helper

	private:
		/// <summary>
		/// Checks for a dependency, and gets a ref to it if able.
		/// </summary>
		/// <typeparam name="T">The type of Asset to find.</typeparam>
		/// <param name="path">The path to the file that is being worked on.</param>
		/// <param name="reader">The reader to the file that is being worked on.</param>
		/// <param name="name">The name of the data to load from the Reader.</param>
		/// <param name="asset">A reference to the Asset to load the data into.</param>
		/// <param name="required">If true, an error is raised if no valid value with the given name is found.</param>
		/// <returns>True if found and stored into asset.</returns>
		template<typename T>
		Int find_dependency(Path const& path, Reader& reader, String const& name, Ref<T>& asset, bool required) const
		{
			UUID id{};

			// if nothing read, set to null
			if (!reader.read(name, id))
			{
				if (required)
				{
					Debug::write_error(F("Cannot load \"{}\". Missing \"{}\".", path, name));
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
		Ref<GenericAsset> load_generic(Path const& path);

		Owner<Image> create_image(Path const& path, UUID const id);

		Ref<Animation> load_animation(Path const& path);

		Ref<Animator> load_animator(Path const& path);

		Ref<AudioClip> load_audio_clip(Path const& path);

		Ref<Image> load_image(Path const& path);

		Ref<Material> load_material(Path const& path);

		Ref<MaterialTemplate> load_material_template(Path const& path);

		Ref<Mesh> load_mesh_obj(Path const& path);

		Ref<Mesh> load_mesh(Path const& path);

		Ref<RenderPass> load_render_pass(Path const& path);

		Ref<Scene> load_scene(Path const& path);

		Ref<Shader> load_shader(Path const& path);

		Ref<ShaderModule> load_shader_module(Path const& path);

		//Ref<Sprite> load_sprite(Path const& path);

		Ref<Texture> load_texture(Path const& path);

#pragma endregion

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new AssetManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A AssetManager Owner.</returns>
		static Owner<AssetManager> create(AssetManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the active Context's AssetManager.
		/// </summary>
		/// <returns>The AssetManager.</returns>
		static AssetManager& get_singleton();

#pragma endregion
	};
}