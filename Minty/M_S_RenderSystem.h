#pragma once

#include "M_System.h"
#include "M_Point.h"
#include "M_PointF.h"
#include "entt.hpp"

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
		/// <summary>
		/// Creates a new RenderSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		/// <param name="mainCameraEntity">The main Camera entity.</param>
		/// <param name="screen">The Engine Screen.</param>
		RenderSystem(entt::registry* const registry, entt::entity* const mainCameraEntity, Screen* const screen)
			: System(registry)
			, mp_screen(screen)
			, mp_mainCameraEntity(mainCameraEntity)
		{}

		void update() override;

		/// <summary>
		/// Converts the given Screen position to a world position.
		/// </summary>
		/// <param name="screenPosition">The Screen position.</param>
		/// <param name="cameraEntity">The Camera the point is on.</param>
		/// <returns></returns>
		PointF screenToWorldPosition(Point const& screenPosition, entt::entity const cameraEntity);

		/// <summary>
		/// Converts the given world position to a Screen position.
		/// </summary>
		/// <param name="worldPosition">The world position.</param>
		/// <param name="cameraEntity">The Camera the point will be on.</param>
		/// <returns></returns>
		Point worldToScreenPosition(PointF const& worldPosition, entt::entity const cameraEntity);
	};
}