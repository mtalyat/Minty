#pragma once

#include "M_Main.h"
#include "entt.hpp"
#include <string>

namespace minty
{
	/// <summary>
	/// Holds a name string for an entity.
	/// </summary>
	struct MINTY_API Name
	{
		/// <summary>
		/// The name of the entity.
		/// </summary>
		std::string name;

		/// <summary>
		/// Gets the name of a given enitty.
		/// </summary>
		/// <param name="entity">The entity to get the name from.</param>
		/// <param name="registry">The registry the entity belonds to.</param>
		/// <returns>The name, or an empty string if no Name was found.</returns>
		static std::string getName(entt::entity const entity, entt::registry* const registry);
	};
}