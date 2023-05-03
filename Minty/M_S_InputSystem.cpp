#include "pch.h"
#include "M_S_InputSystem.h"

#include "M_C_Renderable.h"
#include "M_C_Clickable.h"
#include "M_C_MouseDown.h"
#include "M_C_MouseUp.h"
#include "M_C_MouseClick.h"
#include "M_C_MouseHover.h"
#include "M_C_MouseEnter.h"
#include "M_C_MouseExit.h"
#include "M_C_MouseMove.h"

namespace minty
{
	void InputSystem::onMouseDown(MouseClickEvent const* const click)
	{
		// down events
		for (auto [entity, renderable, clickable, onDown] : mp_registry->view<Renderable const, Clickable const, MouseDown const>().each())
		{
			// if within position, trigger event

			if ((clickable.hitbox + renderable.toPointF()).contains(click->toPoint().toPointF()))
			{
				// clicked
				if (onDown.onDown)
				{
					onDown.onDown->invoke(click);
				}
			}
		}

		// click events
		for (auto [entity, renderable, clickable, onClick] : mp_registry->view<Renderable const, Clickable const, MouseClick>().each())
		{
			// mark as clicked

			onClick.clicked = (clickable.hitbox + renderable.toPointF()).contains(click->toPoint().toPointF());
		}
	}

	void InputSystem::onMouseUp(MouseClickEvent const* const click)
	{
		// up events
		for (auto [entity, position, clickable, onUp] : mp_registry->view<Renderable const, Clickable const, MouseUp const>().each())
		{
			// if within position, trigger event

			if ((clickable.hitbox + position.toPointF()).contains(click->toPoint().toPointF()))
			{
				// clicked
				if (onUp.onUp)
				{
					onUp.onUp->invoke(click);
				}
			}
		}

		// click events
		for (auto [entity, position, clickable, onClick] : mp_registry->view<Renderable const, Clickable const, MouseClick>().each())
		{
			// if marked as clicked, and released here, trigger event
			if (onClick.clicked && (clickable.hitbox + position.toPointF()).contains(click->toPoint().toPointF()))
			{
				if (onClick.onClick)
				{
					onClick.onClick->invoke(click);
				}
			}

			// so it is not clicked again
			onClick.clicked = false;
		}
	}
	
	void InputSystem::onMouseMove(int const x, int const y)
	{
		// check all for movement

		// create mouse move event using old x and y, and new x and y
		MouseMoveEvent mme{
			m_mouseX, m_mouseY,
			x, y
		};

		PointF oldMouse(m_mouseX, m_mouseY);
		PointF newMouse(x, y);

		// mouse enter must contain new x and y
		for (auto [entity, position, clickable, hover, onEnter] : mp_registry->view<Renderable const, Clickable const, MouseHover, MouseEnter>().each())
		{
			// if does not contain mouse, and now it does
			if (!hover.hovering && (clickable.hitbox + position.toPointF()).contains(newMouse))
			{
				hover.hovering = true;

				if (onEnter.onEnter)
				{
					onEnter.onEnter->invoke(&mme);
				}
			}
		}

		// mouse exit must not contain new x and y, but it did before
		for (auto [entity, position, clickable, hover, onExit] : mp_registry->view<Renderable const, Clickable const, MouseHover, MouseExit>().each())
		{
			// if does contain mouse, and now it does not
			if (hover.hovering && !(clickable.hitbox + position.toPointF()).contains(newMouse))
			{
				hover.hovering = false;

				if (onExit.onExit)
				{
					onExit.onExit->invoke(&mme);
				}
			}
		}

		// mouse move must either contain new x and y, or contain old x and y
		for (auto [entity, position, clickable, hover, onMove] : mp_registry->view<Renderable const, Clickable const, MouseHover, MouseMove>().each())
		{
			// if did contain mouse, or now it does
			bool c = (clickable.hitbox + position.toPointF()).contains(newMouse);
			if (hover.hovering || c)
			{
				hover.hovering = c;

				if (onMove.onMove)
				{
					onMove.onMove->invoke(&mme);
				}
			}
		}

		// finally, update with new positional value for next time the mouse moves
		m_mouseX = x;
		m_mouseY = y;
	}
}
