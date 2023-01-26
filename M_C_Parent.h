#pragma once

#include "M_Main.h"
#include "entt.hpp"
#include <vector>

namespace minty
{
	/// <summary>
	/// A component that holds data relating to being a parent with zero or more children.
	/// </summary>
	struct MINTY_API Parent
	{
		std::vector<entt::entity>* entities;

		Parent()
			: entities(new std::vector<entt::entity>()) {}

		~Parent()
		{
			delete entities;
		}
	};
}