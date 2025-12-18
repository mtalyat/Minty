#ifndef MINTY_DATA_CONTAINER_H
#define MINTY_DATA_CONTAINER_H

/**
 * @file Container.h
 * @brief Header file for the Container class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
	/**
	 * @class Container
	 * @brief An abstract base class for data containers.
	 */
	class Container
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Container.
		 */
		Container() = default;

		virtual ~Container() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the internal data pointer.
		 * @returns A pointer to the internal data.
		 */
		virtual Any get_data() const = 0;

		/**
		 * @brief Gets the size of this Container.
		 * @returns The size in bytes.
		 */
		virtual Size get_size() const = 0;

		/**
		 * @brief Gets the capacity of this Container.
		 * @returns The capacity in bytes.
		 */
		virtual Size get_capacity() const = 0;

		/**
		 * @brief Checks if this Container is empty.
		 * @returns True if the Container has no data.
		 */
		Bool is_empty() const { return get_size() == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Sets the bytes at the given index.
		 * @param data The bytes to set.
		 * @param size The number of bytes to set.
		 * @param index The index of the bytes to set.
		 */
		virtual void set_at(AnyConst const data, Size const size, Size const index) = 0;

		/**
		 * @brief Sets the bytes for this Container.
		 * @param data The bytes to set.
		 * @param size The number of bytes to set.
		 * @returns True if set successfully.
		 */
		virtual Bool set(AnyConst const data, Size const size);

		/**
		 * @brief Gets the bytes at the given index.
		 * @param index The index to the bytes.
		 * @returns A pointer to the bytes at the given index.
		 */
		virtual AnyConst get_at(Size const index) const = 0;

		/**
		 * @brief Gets the object of type T at the given index.
		 * @tparam T The type of the object.
		 * @param index The index of the object.
		 * @returns A reference to the object at the given index.
		 */
		template<typename T>
		T const& get_object(Size const index) const
		{
			return *static_cast<T const*>(get_at(index));
		}

		/**
		 * @brief Adds the given bytes to the end of the data within this Container. Reserves more space if needed.
		 * @param data The bytes to append.
		 * @param size The number of bytes to append.
		 * @returns True if appended successfully.
		 */
		virtual Bool append(AnyConst const data, Size const size) = 0;

		/**
		 * @brief Adds the given object to the end of the data within this Container. Reserves more space if needed.
		 * @tparam T The type of the object.
		 * @param object The object to append.
		 * @returns True if appended successfully.
		 */
		template<typename T>
		Bool append_object(T const& object)
		{
			return append_one(&object, sizeof(T));
		}

		/**
		 * @brief Clears this Container.
		 */
		virtual void clear() = 0;

		/**
		 * @brief Sets the new capacity for this Container.
		 * @param capacity The new capacity in bytes.
		 * @returns True on success.
		 */
		virtual Bool reserve(Size const capacity) = 0;

		/**
		 * @brief Resizes this Container to the given size.
		 * @param size The new size in bytes.
		 * @returns True on success.
		 */
		virtual Bool resize(Size const size) = 0;
		
	protected:
		inline virtual Bool append_one(AnyConst const object, Size const size) { return append(object, size); }

#pragma endregion
	};
}

#endif // MINTY_DATA_CONTAINER_H