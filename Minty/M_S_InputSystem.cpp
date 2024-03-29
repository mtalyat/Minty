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
	bool InputSystem::onMouseDown(MouseClickEvent const* const click)
	{
		// sort it
		mp_registry->sort<Renderable>([](Renderable const& left, Renderable const& right)
			{
				if (left.layer != right.layer)
				{
					// unequal layers
					return left.layer > right.layer;
				}
				else
				{
					// equal layers
					return left.order > right.order;
				}
			});

		mp_registry->sort<Clickable, Renderable>();
		mp_registry->sort<MouseDown, Renderable>();
		mp_registry->sort<MouseClick, Renderable>();

		// click only one object
		bool clicked = false;

		// down events
		for (auto [entity, renderable, clickable, onDown] : mp_registry->view<Renderable const, Clickable const, MouseDown const>().each())
		{
			// if not rendering, cannot click
			if (renderable.invisible)
			{
				continue;
			}

			// if within position, trigger event
			if (!clicked && (clickable.hitbox + renderable.toPointF()).contains(click->toPoint().toPointF()))
			{
				// clicked in zone, ensure clicked on sprite, if required
				if (clickable.pixelPerfect)
				{
					// must click on sprite, in its bounds
					Sprite* sprite = Renderable::getSprite(entity, mp_registry);
					if (sprite == nullptr || !sprite->at(click->x - renderable.x, click->y - renderable.y).a())
					{
						// if no sprite, cannot click
						// if no alpha at color, then invisible, cannot click
						continue;
					}
				}

				if (onDown.onDown)
				{
					onDown.onDown->invoke(click);
				}

				// if clicked, do not click anything else
				clicked = true;
			}
		}

		bool output = clicked;
		clicked = false;

		// click events
		for (auto [entity, renderable, clickable, onClick] : mp_registry->view<Renderable const, Clickable const, MouseClick>().each())
		{
			// mark as clicked
			if (!clicked && !renderable.invisible && (clickable.hitbox + renderable.toPointF()).contains(click->toPoint().toPointF()))
			{
				if (clickable.pixelPerfect)
				{
					// must click on sprite, in its bounds
					Sprite* sprite = Renderable::getSprite(entity, mp_registry);
					
					onClick.clicked = sprite != nullptr && sprite->at(click->x - renderable.x, click->y - renderable.y).a();
				}
				else
				{
					// not pixel perfect, so count as clicked since inside bounds
					onClick.clicked = true;
				}

				clicked = onClick.clicked;
			}
			else {
				// not visible or not in bounds, so not clicked
				onClick.clicked = false;
			}
		}

		return output || clicked;
	}

	bool InputSystem::onMouseUp(MouseClickEvent const* const click)
	{
		// sort it
		mp_registry->sort<Renderable>([](Renderable const& left, Renderable const& right)
			{
				if (left.layer != right.layer)
				{
					// unequal layers
					return left.layer > right.layer;
				}
				else
				{
					// equal layers
					return left.order > right.order;
				}
			});

		mp_registry->sort<Clickable, Renderable>();
		mp_registry->sort<MouseUp, Renderable>();
		mp_registry->sort<MouseClick, Renderable>();

		// click only one object
		bool clicked = false;

		// up events
		for (auto [entity, renderable, clickable, onUp] : mp_registry->view<Renderable const, Clickable const, MouseUp const>().each())
		{
			// if not rendering, cannot click
			if (renderable.invisible)
			{
				continue;
			}

			// if within position, trigger event

			if (!clicked && (clickable.hitbox + renderable.toPointF()).contains(click->toPoint().toPointF()))
			{
				// clicked in zone, ensure clicked on sprite, if required
				if (clickable.pixelPerfect)
				{
					// must click on sprite, in its bounds
					Sprite* sprite = Renderable::getSprite(entity, mp_registry);
					if (sprite == nullptr || !sprite->at(click->x - renderable.x, click->y - renderable.y).a())
					{
						// if no sprite, cannot click
						// if no alpha at color, then invisible, cannot click
						continue;
					}
				}

				// clicked
				if (onUp.onUp)
				{
					onUp.onUp->invoke(click);
				}

				// if clicked, do not click anything else
				clicked = true;
			}
		}

		bool output = clicked;
		clicked = false;

		// click events
		for (auto [entity, renderable, clickable, onClick] : mp_registry->view<Renderable const, Clickable const, MouseClick>().each())
		{
			// if marked as clicked, and released here, trigger event
			if (!clicked && !renderable.invisible && onClick.clicked && (clickable.hitbox + renderable.toPointF()).contains(click->toPoint().toPointF()))
			{
				// clicked in zone, ensure clicked on sprite, if required
				if (clickable.pixelPerfect)
				{
					// must click on sprite, in its bounds
					Sprite* sprite = Renderable::getSprite(entity, mp_registry);
					if (sprite == nullptr || !sprite->at(click->x - renderable.x, click->y - renderable.y).a())
					{
						// if no sprite, cannot click
						// if no alpha at color, then invisible, cannot click
						onClick.clicked = false;
						continue;
					}
				}

				if (onClick.onClick)
				{
					onClick.onClick->invoke(click);
				}

				// if clicked, do not click anything else
				clicked = true;
			}

			// so it is not clicked again
			onClick.clicked = false;
		}

		return output || clicked;
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
		for (auto [entity, renderable, clickable, hover, onEnter] : mp_registry->view<Renderable const, Clickable const, MouseHover, MouseEnter>().each())
		{
			// if invisible, do nothing
			if (renderable.invisible)
			{
				continue;
			}

			// if does not contain mouse, and now it does
			if (!hover.hovering && (clickable.hitbox + renderable.toPointF()).contains(newMouse))
			{
				hover.hovering = true;

				if (onEnter.onEnter)
				{
					onEnter.onEnter->invoke(&mme);
				}
			}
		}

		// mouse exit must not contain new x and y, but it did before
		for (auto [entity, renderable, clickable, hover, onExit] : mp_registry->view<Renderable const, Clickable const, MouseHover, MouseExit>().each())
		{
			// if does contain mouse, and now it does not
			if (renderable.invisible || hover.hovering && !(clickable.hitbox + renderable.toPointF()).contains(newMouse))
			{
				hover.hovering = false;

				if (onExit.onExit)
				{
					onExit.onExit->invoke(&mme);
				}
			}
		}

		// mouse move must either contain new x and y, or contain old x and y
		for (auto [entity, renderable, clickable, hover, onMove] : mp_registry->view<Renderable const, Clickable const, MouseHover, MouseMove>().each())
		{
			// if invisible, do nothing
			if (renderable.invisible)
			{
				continue;
			}

			// if did contain mouse, or now it does
			bool c = (clickable.hitbox + renderable.toPointF()).contains(newMouse);
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
