#pragma once

#include "M_Main.h"
#include "M_Event.h"
#include "M_Collision.h"
#include "M_Rect.h"
#include "M_Mask.h"
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
		/// <summary>
		/// The bounds of the Collider.
		/// </summary>
		Rect bounds;

		/// <summary>
		/// Is this Collider just a trigger, and does not have physics collisions?
		/// </summary>
		bool isTrigger;

		/// <summary>
		/// Is this Collider non-moving?
		/// </summary>
		bool isStatic;

		/// <summary>
		/// The bitmask for this Collider. If null, the SpriteRenderer's Sprite will be used, if there is one.
		/// </summary>
		Mask* mask;

		/// <summary>
		/// The collison cell bounds.
		/// </summary>
		Rect cellBounds;

		/// <summary>
		/// The Event invokd when a collision starts with another object.
		/// </summary>
		collider_event_t* onEnter;
		/// <summary>
		/// The Event invoked when a collision continues to happen with another object.
		/// </summary>
		collider_event_t* onStay;
		/// <summary>
		/// The Event invoked when a collison with another object ends.
		/// </summary>
		collider_event_t* onExit;

	public:
		/// <summary>
		/// Adds a new function to the onEnter Event.
		/// </summary>
		/// <param name="func">The function to be called when the Event is invoked.</param>
		void emplaceOnEnter(collider_event_t::func const& func);
		/// <summary>
		/// Adds a new function to the onStay Event.
		/// </summary>
		/// <param name="func">The function to be called when the Event is invoked.</param>
		void emplaceOnStay(collider_event_t::func const& func);
		/// <summary>
		/// Adds a new function to the onExit Event.
		/// </summary>
		/// <param name="func">The function to be called when the Event is invoked.</param>
		void emplaceOnExit(collider_event_t::func const& func);

		/// <summary>
		/// Invokes the onEnter Event.
		/// </summary>
		/// <param name="other">The Collision Event argument.</param>
		void triggerOnEnter(collider_event_arg_t other) const;
		/// <summary>
		/// Invokes the onStay Event.
		/// </summary>
		/// <param name="other">The Collision Event argument.</param>
		void triggerOnStay(collider_event_arg_t other) const;
		/// <summary>
		/// Invokes the onExit Event.
		/// </summary>
		/// <param name="other">The Collision Event argument.</param>
		void triggerOnExit(collider_event_arg_t other) const;
	};
}