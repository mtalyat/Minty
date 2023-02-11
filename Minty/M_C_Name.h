#pragma once

#include "M_Main.h"
#include "entt.hpp"
#include <string>

namespace minty
{
	struct MINTY_API Name
	{
		std::string name;

		static std::string const& getName(entt::entity const entity, entt::registry* const registry);
	};
}