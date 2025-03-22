#pragma once
#include "Minty/Asset/AssetType.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	/// <summary>
	/// The base class for all Asset types.
	/// </summary>
	class Asset
	{
		//friend class AssetManager;

#pragma region Variables

	private:
		UUID m_uuid;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an Asset with the given UUID.
		/// </summary>
		/// <param name="id">The Asset UUID.</param>
		Asset(UUID const id)
			: m_uuid(id)
		{
		}

		virtual ~Asset() = default;

#pragma endregion

#pragma region Get Set

		/// <summary>
		/// Gets the UUID of this Asset.
		/// </summary>
		/// <returns>The UUID.</returns>
		UUID get_id() const { return m_uuid; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Asset is loaded into the AssetManager.
		/// </summary>
		virtual void on_load() {}

		/// <summary>
		/// Called when the Asset is unloaded from the AssetManager.
		/// </summary>
		virtual void on_unload() {}

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>The AssetType.</returns>
		virtual constexpr AssetType get_asset_type() const = 0;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Given the Path, uses the extension to determine the AssetType.
		/// </summary>
		/// <param name="path">The Path to the Asset file.</param>
		/// <returns>The type of Asset.</returns>
		static AssetType get_asset_type(Path const& path);

		/// <summary>
		/// Given the TypeID, gets the AssetType.
		/// </summary>
		/// <param name="typeId">The Type.</param>
		/// <returns>The corresponding AssetType.</returns>
		static AssetType get_asset_type(TypeID const& typeId);

		/// <summary>
		/// Given the Path, gets the Path to the meta file.
		/// </summary>
		/// <param name="path">The Path to the Asset file.</param>
		/// <returns>The Path to the corresponding meta file.</returns>
		static Path get_meta_path(Path const& path);

#pragma endregion
	};
}