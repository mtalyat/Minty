#pragma once

#include "M_System.h"

namespace minty
{
	class MINTY_API TargetSystem
		: public System
	{
	public:
		TargetSystem(entt::registry* const registry)
			: System(registry)
		{}

		virtual void fixedUpdate() override;
	};
}