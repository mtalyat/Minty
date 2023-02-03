#pragma once

#include "M_Main.h"
#include "M_Hitbox.h"
#include "M_Event.h"
#include "M_Collision.h"
#include "entt.hpp"

#define collider_event_t Event<Collision* const>

namespace minty
{
	template class MINTY_API Event<Collision* const>;

	/// <summary>
	/// Holds data regarding a collision.
	/// </summary>
	struct MINTY_API Collider
	{
		Hitbox* hitbox;

		bool isTrigger;
		bool isStatic;

		Rect cellBounds;

		Event<Collision* const>* onEnter;
		Event<Collision* const>* onStay;
		Event<Collision* const>* onExit;

	public:
		void triggerOnEnter(Collision* const) const;

		void triggerOnStay(Collision* const) const;

		void triggerOnExit(Collision* const) const;
	};
}