#ifndef MINTY_RENDER_BUFFER_H
#define MINTY_RENDER_BUFFER_H

/**
 * @file Buffer.h
 * @brief Header file defining the Buffer class and BufferInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Pointer.h"
#include "Minty/Render/BufferUsage.h"

namespace Minty
{
	struct BufferInfo;

	/**
	 * @brief Holds an array of data on the GPU.
	 */
	class Buffer
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Buffer.
		 * @param info The arguments.
		 */
		Buffer(BufferInfo const& info);

		virtual ~Buffer() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Byte data of this Buffer. Only works if this Buffer is optimized for frequent usage.
		 * @return A pointer to the data.
		 */
		virtual Any get_data() const = 0;

		/**
		 * @brief Sets the Byte data of this Buffer.
		 * @param data The new Byte data.
		 */
		virtual void set_data(void const* const data) = 0;

		/**
		 * @brief Gets the size of this Buffer in bytes.
		 * @return The size.
		 */
		virtual Size get_size() const = 0;

		/**
		 * @brief Gets the BufferUsage.
		 * @return The BufferUsage.
		 */
		inline BufferUsage get_usage() const { return m_usage; }

		/**
		 * @brief Checks if this Buffer is optimized for frequent usage.
		 * @return True, if frequent.
		 */
		inline Bool is_frequent() const { return m_frequent; }

		/**
		 * @brief Gets the native Buffer object.
		 * @return A pointer to the native object.
		 */
		virtual Any get_native() const = 0;

		/**
		 * @brief Creates a new Buffer.
		 * @param info The info to use.
		 * @return A Buffer Owner.
		 */
		static Shared<Buffer> create(BufferInfo const& info = {});

#pragma endregion

#pragma region Variables

	private:
		BufferUsage m_usage;
		Bool m_frequent;

#pragma endregion
	};
}

#endif // MINTY_RENDER_BUFFER_H