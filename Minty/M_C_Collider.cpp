#include "pch.h"
#include "M_C_Collider.h"

void minty::Collider::triggerOnEnter(Collision* const other) const
{
	if (onEnter)
	{
		onEnter->invoke(other);
	}
}

void minty::Collider::triggerOnStay(Collision* const other) const
{
	if (onStay)
	{
		onStay->invoke(other);
	}
}

void minty::Collider::triggerOnExit(Collision* const other) const
{
	if (onExit)
	{
		onExit->invoke(other);
	}
}
