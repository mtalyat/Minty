#include "pch.h"
#include "M_C_Collider.h"

void minty::Collider::emplaceOnEnter(collider_event_t::func const& func)
{
	if (!onEnter)
	{
		onEnter = new collider_event_t();
	}

	onEnter->emplace(func);
}

void minty::Collider::emplaceOnStay(collider_event_t::func const& func)
{
	if (!onStay)
	{
		onStay = new collider_event_t();
	}

	onStay->emplace(func);
}

void minty::Collider::emplaceOnExit(collider_event_t::func const& func)
{
	if (!onExit)
	{
		onExit = new collider_event_t();
	}

	onExit->emplace(func);
}

void minty::Collider::triggerOnEnter(collider_event_arg_t other) const
{
	if (onEnter)
	{
		onEnter->invoke(other);
	}
}

void minty::Collider::triggerOnStay(collider_event_arg_t other) const
{
	if (onStay)
	{
		onStay->invoke(other);
	}
}

void minty::Collider::triggerOnExit(collider_event_arg_t other) const
{
	if (onExit)
	{
		onExit->invoke(other);
	}
}
