#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Manager/Manager.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a LayerManager.
	/// </summary>
	struct LayerManagerBuilder
	{
		/// <summary>
		/// The layer collision matrix data.
		/// Each tuple contains the name of the layer, the layer itself, and the layer mask of the layers it collides with.
		/// Each bit, starting with the least significant bit, corresponds to the layer index of the layer it collides with.
		/// </summary>
		Vector<Tuple<String, Layer, Layer>> layerCollisions = {
			{ "None", LAYER_NONE, LAYER_NONE },
			{ "Default", LAYER_DEFAULT, LAYER_ALL }
		};
	};

	/// <summary>
	/// Controls the layers in the engine.
	/// </summary>
	class LayerManager
		: public Manager
	{
#pragma region Variables

	private:
		// the layer matrix
		String m_names[LAYER_COUNT];
		Layer m_matrix[LAYER_COUNT];

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new LayerManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		LayerManager(LayerManagerBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the name of the given Layer.
		/// </summary>
		/// <param name="layer">The Layer.</param>
		/// <returns>The name of the Layer.</returns>
		inline String const& get_name(Layer const layer) const
		{
			MINTY_ASSERT(layer >= 0 && layer < LAYER_COUNT, "Layer index out of bounds.");
			return m_names[layer];
		}
		
		/// <summary>
		/// Gets the first Layer with the given name.
		/// </summary>
		/// <param name="name">The name of the Layer.</param>
		/// <returns>The Layer index, opr LAYER_NONE if no Layer was found..</returns>
		Layer get_layer(String const& name) const;

		/// <summary>
		/// Gets the Layer mask for the given Layer.
		/// </summary>
		/// <param name="layer"></param>
		/// <returns></returns>
		inline Layer get_mask(Layer const layer) const
		{
			MINTY_ASSERT(layer >= 0 && layer < LAYER_COUNT, "Layer index out of bounds.");
			return m_matrix[layer];
		}

#pragma endregion

#pragma region Statics

		/// <summary>
		/// Creates a new LayerManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A LayerManager Owner.</returns>
		static Owner<LayerManager> create(LayerManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the active Context's LayerManager.
		/// </summary>
		/// <returns>The LayerManager.</returns>
		static LayerManager& get_singleton();

#pragma endregion

	};
}