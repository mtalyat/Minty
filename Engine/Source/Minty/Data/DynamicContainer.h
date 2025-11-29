#ifndef MINTY_DATA_DYNAMICCONTAINER_H
#define MINTY_DATA_DYNAMICCONTAINER_H

/**
 * @file DynamicContainer.h
 * @brief Header file for the DynamicContainer class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/MemoryContainer.h"

namespace Minty
{
	/**
	 * @class DynamicContainer
	 * @brief A MemoryContainer that can dynamically resize its capacity.
	 */
	class DynamicContainer
		: public MemoryContainer
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty DynamicContainer.
		 */
		DynamicContainer();

		/**
		 * @brief Creates a DynamicContainer with the given capacity.
		 * @param capacity The initial capacity in bytes.
		 */
		DynamicContainer(Size const capacity);

		/**
		 * @brief Creates a DynamicContainer with the given data and size.
		 * @param data The byte data.
		 * @param size The size of the data in bytes.
		 */
		DynamicContainer(void const* const data, Size const size);

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Adds the given bytes to the end of the data within this Container. Reserves more space if needed.
		 * @param data The bytes to append.
		 * @param size The number of bytes to append.
		 * @return True if appended successfully.
		 */
		virtual Bool append(void const* const data, Size const size) override;

		/**
		 * @brief Sets the new capacity for this Container.
		 * @param newCapacity The new capacity in bytes.
		 * @return True on success.
		 */
		virtual Bool reserve(Size const newCapacity) override;

#pragma endregion
	};
}

#endif // MINTY_DATA_DYNAMICCONTAINER_H