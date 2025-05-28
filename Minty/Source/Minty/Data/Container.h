#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// A collection of bytes.
	/// </summary>
	class Container
	{
#pragma region Constructors

	public:
		Container() = default;

		virtual ~Container() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the internal data pointer.
		/// </summary>
		/// <returns>A pointer to the internal data.</returns>
		virtual void* get_data() const = 0;

		/// <summary>
		/// Gets the number of bytes in this Container.
		/// </summary>
		/// <returns>The size in bytes.</returns>
		virtual Size get_size() const = 0;

		/// <summary>
		/// Gets the maximum number of bytes in this Container.
		/// </summary>
		/// <returns>The capacity in bytes.</returns>
		virtual Size get_capacity() const = 0;

		/// <summary>
		/// Checks if this Container is empty.
		/// </summary>
		/// <returns>True if the size is zero.</returns>
		Bool is_empty() const { return get_size() == 0; }

#pragma endregion

#pragma region Methods

	protected:
		virtual Bool append_one(void const* const object, Size const size)
		{
			return append(object, size);
		}

	public:
		/// <summary>
		/// Sets the bytes at the given index and size.
		/// </summary>
		/// <param name="data">The bytes to set.</param>
		/// <param name="size">The number of bytes to set.</param>
		/// <param name="index">The index of the bytes to set.</param>
		virtual void set_at(void const* const data, Size const size, Size const index) = 0;

		/// <summary>
		/// Resizes and sets the data to the given bytes.
		/// </summary>
		/// <param name="data">The bytes to set.</param>
		/// <param name="size">The number of bytes to set.</param>
		/// <returns>True if set successfully.</returns>
		virtual Bool set(void const* const data, Size const size);

		/// <summary>
		/// Adds the given bytes to the end of the data within this Container. Reserves more space if needed.
		/// </summary>
		/// <param name="data">The bytes to append.</param>
		/// <param name="size">The number of bytes to append.</param>
		/// <returns>True if appended successfully.</returns>
		virtual Bool append(void const* const data, Size const size) = 0;

		/// <summary>
		/// Adds the given object to the end of the data within this Container. Reserves more space if needed.
		/// </summary>
		/// <typeparam name="T">The type of the object.</typeparam>
		/// <param name="object">The object.</param>
		/// <returns>True if appended successfully.</returns>
		template<typename T>
		Bool append_object(T const& object)
		{
			return append_one(&object, sizeof(T));
		}

		/// <summary>
		/// Clears all data out of this Container.
		/// </summary>
		virtual void clear() = 0;

		/// <summary>
		/// Sets the new capacity for this Container.
		/// </summary>
		/// <param name="capacity">The new capacity to set, in bytes.</param>
		/// <returns>True on success.</returns>
		virtual Bool reserve(Size const capacity) = 0;

		/// <summary>
		/// Sets the new size for this Container.
		/// </summary>
		/// <param name="size">The number of bytes.</param>
		/// <returns>True on success.</returns>
		virtual Bool resize(Size const size) = 0;

#pragma endregion
	};
}