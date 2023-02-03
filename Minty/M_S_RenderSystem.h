#pragma once

#include "M_System.h"

namespace minty
{
	class Screen;

	/// <summary>
	/// Handles all of the rendering within the Scene.
	/// </summary>
	class MINTY_API RenderSystem
		: public System
	{
	private:
		Screen* const mp_screen;
		entt::entity* const mp_mainCameraEntity;

	public:
		RenderSystem(entt::registry* const registry, entt::entity* const mainCameraEntity, Screen* const screen)
			: System(registry)
			, mp_screen(screen)
			, mp_mainCameraEntity(mainCameraEntity)
		{}

		void update() override;
	};
}