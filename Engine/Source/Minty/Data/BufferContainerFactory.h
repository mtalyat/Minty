#ifndef MINTY_DATA_BUFFERCONTAINERFACTORY_H
#define MINTY_DATA_BUFFERCONTAINERFACTORY_H

/**
 * @file BufferContainerFactory.h
 * @brief Header file for the BufferContainerFactory class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/BufferContainer.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/**
	 * @class BufferContainerFactory
	 * @brief A factory that creates and manages BufferContainers of a specific usage and initial capacity.
	 */
	class BufferContainerFactory
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a BufferContainerFactory with the given initial capacity and BufferUsage.
		 * @param initialCapacity The initial capacity in bytes for each BufferContainer.
		 * @param usage The BufferUsage to use for each BufferContainer.
		 */
		BufferContainerFactory(Size const initialCapacity, BufferUsage const usage);

		~BufferContainerFactory() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets a BufferContainer with at least the given size.
		 * @param size The minimum size in bytes the BufferContainer must be able to hold.
		 * @returns A reference to a BufferContainer.
		 */
		BufferContainer& get_container(Size const size);

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Marks all BufferContainers as unused, so they can be reused.
		 */
		void reset();

#pragma endregion

#pragma region Variables

	private:
		Size m_initialCapacity;
		BufferUsage m_usage;
		Vector<Vector<Tuple<Bool, BufferContainer>>> m_containers;

#pragma endregion
	};
}

#endif // MINTY_DATA_BUFFERCONTAINERFACTORY_H