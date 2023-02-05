#include "pch.h"
#include "M_S_UserInterfaceSystem.h"

#include "M_Screen.h"

#include "M_C_UI.h"
#include "M_C_Renderable.h"
#include "M_C_Renderer.h"

namespace minty
{
	void UserInterfaceSystem::update()
	{
		// update rendering positioning
		for (auto [entity, ui, renderable, renderer] : mp_registry->view<UI const, Renderable, Renderer const>().each())
		{
			renderable.x = ui.x + mp_screen->width * ui.anchorX - renderer.sprite->width * ui.pivotX;
			renderable.y = ui.y + mp_screen->height * ui.anchorY - renderer.sprite->height * ui.pivotY;
		}
	}
}
