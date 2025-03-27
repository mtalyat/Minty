#pragma once
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/RenderManager.h"

namespace Minty
{
	class Vulkan_RenderManager
		: public RenderManager
	{
#pragma region Variables

	private:
		VkInstance m_instance;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_RenderManager(RenderManagerBuilder const& builder);

		~Vulkan_RenderManager();

#pragma endregion

#pragma region Get Set

	public:
		inline VkInstance get_instance() const { return m_instance; }

		inline VkPhysicalDevice get_physical_device() const { return m_physicalDevice; }

		inline VkDevice get_device() const { return m_device; }

#pragma endregion

#pragma region Methods

	public:
		VkInstance create_instance();

		void destroy_instance(VkInstance const instance);

#pragma endregion


#pragma region Statics

		/// <summary>
		/// Gets the active Context's Vulkan RenderManager.
		/// </summary>
		/// <returns>The Vulkan_RenderManager.</returns>
		inline static Vulkan_RenderManager& instance()
		{
			return static_cast<Vulkan_RenderManager&>(RenderManager::instance());
		}

#pragma endregion

	};
}