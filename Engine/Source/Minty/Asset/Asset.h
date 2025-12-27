#pragma once
#include "Minty/Asset/AssetType.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include <type_traits>

namespace Minty
{
	class Asset;
	// Helper to remove const, volatile, and reference qualifiers
	template<typename T>
	using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

	// Primary template: false by default
	template<typename T, typename = void>
	struct is_asset : std::false_type {};

	// Specialization for Ref<T> where T derives from Asset
	template<typename T>
	struct is_asset<Ref<T>, std::enable_if_t<std::is_base_of_v<Asset, T>>> : std::true_type {};

	// Specialization for Shared<T> where T derives from Asset
	template<typename T>
	struct is_asset<Shared<T>, std::enable_if_t<std::is_base_of_v<Asset, T>>> : std::true_type {};

	//// Specialization for Shared<T> where T derives from Asset
	//template<typename T>
	//struct is_asset<Shared<T>, std::enable_if_t<std::is_base_of_v<Asset, T>>> : std::true_type {};

	// Forwarding specialization to handle cv/ref-qualified types
	template<typename T>
	struct is_asset<T, std::enable_if_t<!std::is_same_v<T, remove_cvref_t<T>>>> : is_asset<remove_cvref_t<T>> {};

	/**
	 * @brief Base class for all Assets in the Minty engine.
	 */
	class Asset
	{
		friend class AssetManager;

#pragma region Variables

	private:
		UUID m_uuid;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an Asset with the given UUID.
		 * @param id The UUID of the Asset.
		 */
		Asset(UUID const id)
			: m_uuid(id)
		{
		}

		virtual ~Asset()
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the UUID of this Asset.
		 * @return The UUID.
		 */
		UUID get_id() const { return m_uuid; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Asset is loaded.
		 */
		virtual void on_load() {}

		/**
		 * @brief Called when the Asset is unloaded.
		 */
		virtual void on_unload() {}

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return The AssetType.
		 */
		virtual AssetType get_asset_type() const = 0;

		virtual void serialize(Writer& writer) const override { MINTY_NOT_IMPLEMENTED(); }
		virtual Bool deserialize(Reader& reader) override { MINTY_NOT_IMPLEMENTED(); return false; }

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Given the Path, gets the AssetType.
		 * @param path The Path to the Asset file.
		 * @returns The corresponding AssetType.
		 */
		static AssetType get_asset_type(Path const& path);

		/**
		 * @brief Given the TypeID, gets the AssetType.
		 * @param typeId The TypeID of the Asset class.
		 * @returns The corresponding AssetType.
		 */
		static AssetType get_asset_type(TypeID const& typeId);

		/**
		 * @brief Given the Path to an asset, gets the corresponding meta file Path.
		 * @param path The Path to the Asset file.
		 * @returns The Path to the corresponding meta file.
		 */
		static Path get_meta_path(Path const& path);

#pragma endregion
	};
}