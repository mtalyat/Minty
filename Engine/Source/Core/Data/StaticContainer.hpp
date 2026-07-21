#pragma once

/**
 * @file StaticContainer.hpp
 * @brief Header file for the StaticContainer class.
 * @author Mitchell Talyat
 */

#include "MemoryContainer.hpp"

namespace Minty
{
	/// <summary>
	/// A Container of bytes that has a constant capacity. The size is dynamic, but only within the capacity.
	/// </summary>
	class StaticContainer
		: public MemoryContainer
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a StaticContainer with no capacity.
		 */
		StaticContainer();

		/**
		 * @brief Creates a StaticContainer with the given capacity.
		 * @param capacity The capacity in bytes.
		 */
		StaticContainer(Size const capacity);

		/**
		 * @brief Creates a StaticContainer with the given data and size.
		 * @param data The byte data.
		 * @param size The size of the data in bytes.
		 */
		StaticContainer(PointerConst const data, Size const size);

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Adds the given bytes to the end of the data within this Container. Fails if capacity would be exceeded.
		 * @param data The bytes to append.
		 * @param size The number of bytes to append.
		 * @returns True if appended successfully.
		 */
		Bool append(PointerConst const data, Size const size) override;

		/**
		 * @brief Sets the new capacity for this Container. Fails if capacity is different than current.
		 * @param capacity The new capacity in bytes.
		 * @returns True on success.
		 */
		Bool reserve(Size const capacity) override { return capacity == m_capacity; }

		/**
		 * @brief Resizes this Container to the given size. Fails if size exceeds capacity.
		 * @param size The new size in bytes.
		 * @returns True on success.
		 */
		Bool resize(Size const size) override;
	};

#pragma endregion
}
