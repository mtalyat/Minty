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
#include "Minty/Data/ConstantContainer.h"

namespace Minty
{
	struct PrefabInfo;

	/**
	 * @brief A prefabricated Entity for a Scene.
	 */
	class Prefab
		: public Asset
	{
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
		 * @brief Gets the AssetType of this Asset.
		 * @return Prefab.
		 */
		inline AssetType get_asset_type() const { return AssetType::Prefab; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Opens a Reader for this Prefab's data.
		 * @return A Unique Reader.
		 */
		Unique<Reader> open_reader() const;

		/**
		 * @brief Creates a new Prefab from the given arguments.
		 * @param info The arguments.
		 * @return A Prefab Owner.
		 */
		static Shared<Prefab> create(PrefabInfo const& info);

		/**
		 * @brief Creates a default Prefab.
		 * @return A Prefab Owner.
		 */
		static Shared<Prefab> create();

#pragma endregion

#pragma region Variables

	private:
		Shared<ConstantContainer> m_data;

#pragma endregion
	};
}

#endif // MINTY_ENTITY_PREFAB_H