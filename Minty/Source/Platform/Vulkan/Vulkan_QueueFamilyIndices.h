#pragma once
#include "Minty/Core/Types.h"
#include <optional>

namespace Minty
{
	/// <summary>
	/// Holds the indices to the queue families to be used.
	/// </summary>
	struct Vulkan_QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		/// <summary>
		/// Checks if this QueueFamilyIndices has a valid index for each family.
		/// </summary>
		/// <returns>True when all indices are valid.</returns>
		Bool is_complete() const
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
}