#pragma once

/**
 * @file ListContainer.hpp
 * @brief Header file for the ListContainer class.
 * @author Mitchell Talyat
 */

#include "DynamicContainer.hpp"
#include "Core/Constant/Default.hpp"
#include "Core/Debug/Debug.hpp"

namespace Minty
{
	/**
	 * @class ListContainer
	 * @brief A DynamicContainer that stores a list of elements of fixed stride (size in bytes).
	 */
	class ListContainer
		: public DynamicContainer
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty ListContainer.
		 */
		ListContainer();

		/**
		 * @brief Creates a ListContainer with the given element stride and capacity.
		 * @param stride The size of each element in bytes.
		 */
		ListContainer(Size const stride, Size const capacity = DEFAULT_COLLECTION_SIZE);

		/**
		 * @brief Creates a ListContainer with the given data, stride, and count.
		 * @param data The byte data.
		 */
		ListContainer(PointerConst const data, Size const stride, Size const count);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the stride (size of each element in bytes) for this Container.
		 * @returns The size of an element in bytes.
		 */
		inline Size get_stride() const { return m_stride; }

		/**
		 * @brief Sets the stride (size of each element in bytes) for this Container.
		 * @param stride The size of an element in bytes.
		 */
		inline void set_stride(Size const stride)
		{
			MINTY_ASSERT(stride > 0, ErrorCodeEnum::Argument_ExpectedNonZero);
			MINTY_ASSERT(m_size % stride == 0, ErrorCodeEnum::Argument_InvalidSize); // size must be multiple of stride
			m_stride = stride;
		}

		/**
		 * @brief Gets the size of this Container in bytes.
		 * @returns The size in bytes.
		 */
		inline Size get_size() const override { return m_size; }

		/**
		 * @brief Gets the number of elements in this Container.
		 * @returns The number of elements.
		 */
		inline Size get_count() const { return m_size / m_stride; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Sets the element bytes at the given element index.
		 * @param data The bytes of the element(s) to set.
		 * @param count The number of elements to set.
		 * @param index The index of the element(s) to set.
		 */
		void set_at(PointerConst const data, Size const count, Size const index) override;

		/**
		 * @brief Gets the bytes of the element at the given index.
		 * @param index The index of the element to get.
		 */
		PointerConst get_at(Size const index) const override;

		/**
		 * @brief Sets the element bytes for this Container.
		 * @param data The bytes of the element(s) to set.
		 * @param count The number of elements to set.
		 */
		Bool set(PointerConst const data, Size const count) override;

		/**
		 * @brief Adds the given element bytes to the end of the data within this Container.
		 * @param data The bytes of the element(s) to append.
		 * @param count The number of elements to append.
		 */
		Bool append(PointerConst const data, Size const count = 1) override;

		/**
		 * @brief Sets the new capacity for this Container.
		 * @param newCapacity The new capacity in bytes.
		 * @returns True on success.
		 */
		Bool reserve(Size const newCapacity) override;

		/**
		 * @brief Resizes this Container to the given number of elements.
		 * @param count The new number of elements.
		 * @returns True on success.
		 */
		Bool resize(Size const count) override;

	protected:
		inline Bool append_one(PointerConst const object, Size const size) override
		{
			MINTY_ASSERT(size == m_stride, ErrorCodeEnum::Argument_InvalidSize); // object size must match stride
			return append(object, 1);
		}

#pragma endregion

#pragma region Variables

	protected:
		Size m_stride;

#pragma endregion
	};
}
