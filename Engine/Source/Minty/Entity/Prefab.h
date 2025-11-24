#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"
#include "Minty/Component/Component.h"
#include "Minty/Serialization/Node.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a prefab.
	/// </summary>
	struct PrefabBuilder
	{
		/// <summary>
		/// The ID of this Prefab.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The data for each Entity in this Prefab.
		/// </summary>
		Node source;
	};

	/// <summary>
	/// A prefabricated Entity for a Scene.
	/// </summary>
	class Prefab
		: public Asset
	{
#pragma region Variables

	private:
		Node m_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Prefab from the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Prefab(PrefabBuilder const& builder)
			: Asset(builder.id)
			, m_data(builder.source)
		{
		}

		~Prefab()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the data within this Prefab.
		/// </summary>
		/// <returns>The data.</returns>
		Node const& get_node() const { return m_data; }

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Prefab.</returns>
		constexpr AssetType get_asset_type() const { return AssetType::Prefab; }

#pragma endregion

#pragma region Methods

	public:

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Prefab from the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A Prefab Owner.</returns>
		static Owner<Prefab> create(PrefabBuilder const& builder = {});

#pragma endregion
	};
}