#ifndef MINTY_LAYER_LAYERMANAGER_H
#define MINTY_LAYER_LAYERMANAGER_H

/**
 * @file LayerManager.h
 * @brief Header file for the LayerManager class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Manager/Manager.h"

namespace Minty
{
	struct LayerManagerInfo;

	/**
	 * @brief Controls the layers in the engine.
	 */
	class LayerManager
		: public Manager
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new LayerManager with the given arguments.
		 * @param info The arguments.
		 */
		LayerManager(LayerManagerInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the name of the given Layer.
		 * @param layer The Layer.
		 * @return The name of the Layer.
		 */
		inline String const& get_name(Layer const layer) const
		{
			MINTY_ASSERT(layer >= 0 && layer < LAYER_COUNT, ErrorCode::Argument_OutOfRange);
			return m_names[layer];
		}
		
		/**
		 * @brief Gets the first Layer with the given name.
		 * @param name The name of the Layer.
		 * @return The Layer index, or LAYER_NONE if no Layer was found.
		 */
		Layer get_layer(String const& name) const;

		/**
		 * @brief Gets the Layer mask for the given Layer.
		 * @param layer The Layer.
		 * @return The Layer mask.
		 */
		inline Layer get_mask(Layer const layer) const
		{
			MINTY_ASSERT(layer >= 0 && layer < LAYER_COUNT, ErrorCode::Argument_OutOfRange);
			return m_matrix[layer];
		}

		/**
		 * @brief Determines whether a collision occurs between two layers.
		 * @param layerA The first layer to check for collision.
		 * @param layerB The second layer to check for collision.
		 * @return True if a collision is detected between the two layers; otherwise, false.
		 */
		Bool check_for_collision(Layer const layerA, Layer const layerB) const;

		/**
		 * @brief Converts the layer index to a bit.
		 * @param layer The Layer index.
		 * @return The Layer as a bit.
		 */
		inline static Layer layer_to_bit(Layer const layer) { return 1 << layer; }

		/**
		 * @brief Creates a new LayerManager with the given arguments.
		 * @param info The arguments.
		 * @return A LayerManager Owner.
		 */
		static Unique<LayerManager> create(LayerManagerInfo const& info);

		/**
		 * @brief Creates a new LayerManager with default settings.
		 * @return A LayerManager Owner.
		 */
		static Unique<LayerManager> create();

		/**
		 * @brief Gets the active Context's LayerManager.
		 * @return The LayerManager.
		 */
		static Unique<LayerManager> const& get_instance();

		/**
		 * @brief Gets the active Context's LayerManager.
		 * @return A reference to the LayerManager.
		 */
		static LayerManager& get_singleton();

#pragma endregion

#pragma region Variables

	private:
		// the layer matrix
		String m_names[LAYER_COUNT];
		Layer m_matrix[LAYER_COUNT];

#pragma endregion
	};
}

#endif // MINTY_LAYER_LAYERMANAGER_H