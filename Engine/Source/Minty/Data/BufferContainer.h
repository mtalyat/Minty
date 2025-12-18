#ifndef MINTY_DATA_BUFFERCONTAINER_H
#define MINTY_DATA_BUFFERCONTAINER_H

/**
 * @file BufferContainer.h
 * @brief Header file for the BufferContainer class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Container.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/BufferUsage.h"

namespace Minty
{
	class Buffer;

	/**
	 * @class BufferContainer
	 * @brief A container that holds data in a GPU buffer.
	 */
	class BufferContainer
		: public Container
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty BufferContainer.
		 */
		BufferContainer();

		/**
		 * @brief Creates a BufferContainer with the given BufferUsage.
		 * @param usage The BufferUsage to use.
		 */
		BufferContainer(BufferUsage const usage);

		/**
		 * @brief Creates a BufferContainer with the given capacity and BufferUsage.
		 * @param capacity The capacity in bytes.
		 * @param usage The BufferUsage to use.
		 */
		BufferContainer(Size const capacity, BufferUsage const usage);

		/**
		 * @brief Copies the given BufferContainer.
		 * @param other The BufferContainer to copy.
		 */
		BufferContainer(BufferContainer const& other);

		/**
		 * @brief Moves the given BufferContainer.
		 * @param other The BufferContainer to move.
		 */
		BufferContainer(BufferContainer&& other) noexcept;

		~BufferContainer();

#pragma endregion

#pragma region Operators

	public:
		BufferContainer& operator=(BufferContainer const& other);
		BufferContainer& operator=(BufferContainer&& other) noexcept;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the internal Buffer data pointer.
		 * @returns A pointer to the internal Buffer data.
		 */
		Any get_data() const override;

		/**
		 * @brief Gets the size of this BufferContainer.
		 * @returns The size in bytes.
		 */
		inline Size get_size() const override { return m_size; }
		
		/**
		 * @brief Gets the capacity of this BufferContainer.
		 * @returns The capacity in bytes.
		 */
		inline Size get_capacity() const override { return m_capacity; }

		/**
		 * @brief Gets a reference to the internal Buffer.
		 * @returns A reference to the internal Buffer.
		 */
		inline Ref<Buffer> get_buffer() const { return m_buffer.to_ref(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Sets the bytes at the given index.
		 * @param data The bytes to set.
		 * @param size The number of bytes to set.
		 * @param index The index of the bytes to set.
		 */
		void set_at(AnyConst const data, Size const size, Size const index) override;

		/**
		 * @brief Gets the bytes at the given index.
		 * @param index The index to the bytes.
		 * @returns A pointer to the bytes at the given index.
		 */
		AnyConst get_at(Size const index) const override;

		/**
		 * @brief Adds the given bytes to the end of the data within this BufferContainer. Reserves more space if needed.
		 * @param data The bytes to append.
		 * @param size The number of bytes to append.
		 * @returns True if appended successfully.
		 */
		Bool append(AnyConst const data, Size const size) override;

		/**
		 * @brief Clears this BufferContainer.
		 */
		void clear() override;

		/**
		 * @brief Sets the new capacity for this BufferContainer.
		 * @param newCapacity The new capacity in bytes.
		 * @returns True on success.
		 */
		Bool reserve(Size const newCapacity) override;

		/**
		 * @brief Resizes this BufferContainer.
		 * @param newSize The new size in bytes.
		 * @returns True on success.
		 */
		Bool resize(Size const newSize) override;

#pragma endregion

#pragma region Variables

	private:
		Shared<Buffer> m_buffer;
		BufferUsage m_usage;
		Size m_capacity;
		Size m_size;

#pragma endregion
	};
}

#endif // MINTY_DATA_BUFFERCONTAINER_H