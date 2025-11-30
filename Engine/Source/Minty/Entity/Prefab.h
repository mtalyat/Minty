#ifndef MINTY_ENTITY_PREFAB_H
#define MINTY_ENTITY_PREFAB_H

/**
 * @file Prefab.h
 * @brief Header file defining the Prefab class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"
#include "Minty/Component/Component.h"
#include "Minty/Serialization/Node.h"

namespace Minty
{
	struct PrefabInfo;

	/**
	 * @brief A prefabricated Entity for a Scene.
	 */
	class Prefab
		: public Asset
	{
#pragma region Variables

	private:
		Node m_data;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Prefab from the given arguments.
		 * @param info The arguments.
		 */
		Prefab(PrefabInfo const& info);

		~Prefab()
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the data within this Prefab.
		 * @return The data.
		 */
		Node const& get_node() const { return m_data; }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Prefab.
		 */
		inline AssetType get_asset_type() const { return AssetType::Prefab; }

#pragma endregion

#pragma region Methods

	public:

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Creates a new Prefab from the given arguments.
		 * @param info The arguments.
		 * @return A Prefab Owner.
		 */
		static Shared<Prefab> create(PrefabInfo const& info);

#pragma endregion
	};
}

#endif // MINTY_ENTITY_PREFAB_H