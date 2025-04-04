#pragma once
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Buffer.h"

namespace Minty
{
	class Vulkan_Buffer
		: public Buffer
	{
#pragma region Variables

	private:
		VkBuffer m_buffer;
		VkDeviceMemory m_memory;
		VkDeviceSize m_size;
		void* mp_mappedMemory;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Buffer(BufferBuilder const& builder);

		~Vulkan_Buffer();

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Byte data of this Buffer. Only works if this Buffer is optimized for frequent usage.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		void* get_data() const;

		/// <summary>
		/// Sets the Byte data of this Buffer.
		/// </summary>
		/// <param name="data">The new Byte data.</param>
		void set_data(void const* const data);

		/// <summary>
		/// Gets the size of this Buffer in bytes.
		/// </summary>
		/// <returns>The size.</returns>
		Size get_size() const { return static_cast<Size>(m_size); }

		/// <summary>
		/// Gets the native Buffer object.
		/// </summary>
		/// <returns>A pointer to the native object.</returns>
		void* get_native() const { return m_buffer; }

#pragma endregion
	};
}