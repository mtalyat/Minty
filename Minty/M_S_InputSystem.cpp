#include "pch.h"
#include "M_S_InputSystem.h"

#include "M_C_Position.h"
#include "M_C_Clickable.h"
#include "M_C_MouseDown.h"
#include "M_C_MouseUp.h"
#include "M_C_MouseClick.h"

namespace minty
{
	void InputSystem::update()
	{
	}

	void InputSystem::onMouseDown(Click const* const click)
	{
		// down events
		for (auto [entity, position, clickable, onDown] : mp_registry->view<Position const, Clickable const, MouseDown const>().each())
		{
			// if within position, trigger event

			if ((clickable.hitbox + position.toPoint()).contains(click->pos().toPointF()))
			{
				// clicked
				onDown.onDown->invoke(click);
			}
		}

		// click events
		for (auto [entity, position, clickable, onClick] : mp_registry->view<Position const, Clickable const, MouseClick>().each())
		{
			// mark as clicked

			onClick.clicked = (clickable.hitbox + position.toPoint()).contains(click->pos().toPointF());
		}
	}

	void InputSystem::onMouseUp(Click const* const click)
	{
		// up events
		for (auto [entity, position, clickable, onUp] : mp_registry->view<Position const, Clickable const, MouseUp const>().each())
		{
			// if within position, trigger event

			if ((clickable.hitbox + position.toPoint()).contains(click->pos().toPointF()))
			{
				// clicked
				onUp.onUp->invoke(click);
			}
		}

		// click events
		for (auto [entity, position, clickable, onClick] : mp_registry->view<Position const, Clickable const, MouseClick>().each())
		{
			// if marked as clicked, and released here, trigger event
			if (onClick.clicked && (clickable.hitbox + position.toPoint()).contains(click->pos().toPointF()))
			{
				onClick.onClick->invoke(click);
			}

			// so it is not clicked again
			onClick.clicked = false;
		}
	}
}
