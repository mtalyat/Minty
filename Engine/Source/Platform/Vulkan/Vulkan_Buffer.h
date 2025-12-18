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
		Any mp_mappedMemory;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Buffer(BufferInfo const& info);

		~Vulkan_Buffer();

#pragma endregion

#pragma region Accessors

	public:
		Any get_data() const override;

		void set_data(AnyConst const data) override;

		Size get_size() const override { return static_cast<Size>(m_size); }

		Any get_native() const override { return m_buffer; }

		VkBuffer get_buffer() const { return m_buffer; }

		VkDeviceMemory get_memory() const { return m_memory; }

#pragma endregion
	};
}