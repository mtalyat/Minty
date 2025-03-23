#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/List.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#include "Minty/Wrap/Wrapper.h"
#include <mutex>

#include "Minty/Asset/Text.h"

namespace Minty
{
	/// <summary>
	/// Arguments for creates an AssetManager.
	/// </summary>
	struct AssetManagerBuilder
	{
		/// <summary>
		/// A list of Wrap files to load on initialization.
		/// </summary>
		List<Path> wraps = { "Game.wrap" };

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

	class AssetManager
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
		mutable std::mutex m_assetsMutex;

		Wrapper m_wrapper;

#pragma endregion

#pragma region Constructors

	public:
		AssetManager(AssetManagerBuilder const& builder);

		~AssetManager();

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
		/// <returns>The UUID of the Asset to be loaded.</returns>
		UUID schedule_load(Path const& path);

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
		/// Marks the Asset with the given ID for unloading.
		/// </summary>
		/// <param name="id">The ID of the Asset to unload.</param>
		void schedule_unload(UUID const id);

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
		/// If any Assets are being loaded or unloaded, wait until they are finished.
		/// </summary>
		void sync();

		/// <summary>
		/// Checks if any Assets are being loaded or unloaded.
		/// </summary>
		Bool is_syncing() const;

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
			return static_cast<Ref<T>>(get_asset(id));
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

			Vector<Ref<T>> assets(found->second.get_size());
			for (UUID const id : found->second)
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

		/// <summary>
		/// Reads all of the bytes from the File at the given Path.
		/// </summary>
		/// <param name="path">The Path to the Asset.</param>
		/// <returns>A list of bytes from the File.</returns>
		Vector<Byte> read_bytes(Path const& path) const;

#pragma region Load

	private:
		Ref<Text> load_text(Path const& path);

#pragma endregion

#pragma endregion

	};
}