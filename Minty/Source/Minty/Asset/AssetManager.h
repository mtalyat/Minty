#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/List.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#include "Minty/Wrap/Wrapper.h"

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
		Map<AssetType, Set<Ref<Asset>>> m_assetTypes;
		Vector<UUID> m_destructionQueue;

		Wrapper m_wrapper;

#pragma endregion

#pragma region Constructors

	public:
		AssetManager(AssetManagerBuilder const& builder)
			: m_savePaths(false)
			, m_assets()
			, m_assetTypes()
			, m_destructionQueue()
			, m_wrapper()
		{
			for (Path const& path : builder.wraps)
			{
				load_wrap(path);
			}
		}

		~AssetManager()
		{
		}

#pragma endregion

#pragma region Operators

	public:

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Loads the Wrap at the given location into this AssetManager.
		/// </summary>
		/// <param name="path">The path to the Wrap file.</param>
		/// <returns>True if successfully loaded.</returns>
		Bool load_wrap(Path const& path);

#pragma endregion

	};
}