#pragma once

/**
 * @file MemoryContainer.h
 * @brief Header file for the MemoryContainer class.
 */

#include "Container.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Memory/DefaultAllocator.hpp"

namespace Minty
{
	/**
	 * @class MemoryContainer
	 * @brief A Container that manages its own memory.
	 */
	class MemoryContainer
		: public Container
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty MemoryContainer.
		 */
		MemoryContainer();

		/**
		 * @brief Creates a MemoryContainer with the given capacity.
		 * @param capacity The capacity in bytes.
		 */
		MemoryContainer(MemoryContainer const& other);

		/**
		 * @brief Moves a MemoryContainer.
		 * @param other The other MemoryContainer.
		 */
		MemoryContainer(MemoryContainer&& other) noexcept;

		virtual ~MemoryContainer();

#pragma endregion

#pragma region Operators

	public:
		MemoryContainer& operator=(MemoryContainer const& other);

		MemoryContainer& operator=(MemoryContainer&& other) noexcept;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the internal data pointer.
		 * @returns A pointer to the internal data.
		 */
		inline Pointer get_data() const override { return mp_data; }

		/**
		 * @brief Gets the number of bytes in this Container.
		 * @returns The size in bytes.
		 */
		inline Size get_size() const override { return m_size; }

		/**
		 * @brief Gets the capacity of this Container.
		 * @returns The capacity in bytes.
		 */
		inline Size get_capacity() const override { return m_capacity; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Sets the bytes at the given index and size.
		 * @param data The bytes to set.
		 */
		void set_at(PointerConst const data, Size const size, Size const index) override;
		
		/**
		 * @brief Gets the bytes at the given index.
		 * @param index The index to get from.
		 */
		PointerConst get_at(Size const index) const override;

		/**
		 * @brief Clears this Container.
		 */
		virtual void clear() override;

		/**
		 * @brief Adds the given bytes to the end of the data within this Container. Reserves more space if needed.
		 * @param data The bytes to append.
		 */
		virtual Bool resize(Size const size) override;

#pragma endregion

#pragma region Variables

	protected:
		Size m_capacity;
		Size m_size;
		Byte* mp_data;
		DefaultAllocator m_allocator;

#pragma endregion
	};
}
