#pragma once

#include "M_Main.h"
#include "M_Hitbox.h"
#include "M_Event.h"
#include "M_Collision.h"
#include "entt.hpp"

#define collider_event_arg_t Collision const&
#define collider_event_t Event<collider_event_arg_t>

namespace minty
{
	template class MINTY_API Event<Collision const&>;

	/// <summary>
	/// Holds data regarding a collision.
	/// </summary>
	struct MINTY_API Collider
	{
		Hitbox* hitbox;

		bool isTrigger;
		bool isStatic;

		Rect cellBounds;

		collider_event_t* onEnter;
		collider_event_t* onStay;
		collider_event_t* onExit;

	public:
		void emplaceOnEnter(collider_event_t::func const& func);
		void emplaceOnStay(collider_event_t::func const& func);
		void emplaceOnExit(collider_event_t::func const& func);

		void triggerOnEnter(collider_event_arg_t) const;
		void triggerOnStay(collider_event_arg_t) const;
		void triggerOnExit(collider_event_arg_t) const;
	};
}