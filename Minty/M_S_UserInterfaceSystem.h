#pragma once

#include "M_System.h"

namespace minty
{
	class Screen;

	class MINTY_API UserInterfaceSystem
		: public System
	{
	private:
		Screen* const mp_screen;

	public:
		UserInterfaceSystem(entt::registry* const registry, Screen* const screen)
			: System(registry)
			, mp_screen(screen)
			{}

		void update() override;
	};
}