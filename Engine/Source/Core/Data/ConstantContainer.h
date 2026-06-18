#pragma once

/**
 * @file ConstantContainer.h
 * @brief Defines the ConstantContainer class for immutable memory storage.
 * @author Mitchell Talyat
 */

#include "MemoryContainer.h"

namespace Minty
{
	/**
	 * @class ConstantContainer
	 * @brief A MemoryContainer where its size cannot be modified after creation.
	 */
	class ConstantContainer
		: public MemoryContainer
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty ConstantContainer.
		 */
		ConstantContainer();

		/**
		 * @brief Creates a ConstantContainer with the given size.
		 * @param size The size in bytes.
		 */
		ConstantContainer(Size const size);

		/**
		 * @brief Creates a ConstantContainer with the given data and size.
		 * @param data The data to copy.
		 * @param size The size in bytes.
		 */
		ConstantContainer(PointerConst const data, Size const size);

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Does nothing.
		 * @param data The data to append.
		 * @param size The number of bytes.
		 * @return False.
		 */
		inline Bool append(PointerConst const data, Size const size) override { return false; }

		/**
		 * @brief Clears this Container by zeroing out its data.
		 */
		void clear() override;

		/**
		 * @brief Does nothing.
		 * @param size The size in bytes.
		 * @return True if size is equal to the current size, otherwise false.
		 */
		inline Bool resize(Size const size) override { return size == m_size; }

		/**
		 * @brief Does nothing.
		 * @param capacity The capacity in bytes.
		 * @return True if capacity is equal to the current capacity, otherwise false.
		 */
		inline Bool reserve(Size const capacity) override { return capacity == m_capacity; }

#pragma endregion
	};
}
