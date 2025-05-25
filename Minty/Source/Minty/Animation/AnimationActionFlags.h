#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Determines what additional actions are taken during an animation step.
	/// </summary>
	enum class AnimationActionType
	{
		/// <summary>
		/// No additional action taken.
		/// </summary>
		None = 0,

		/// <summary>
		/// Add the associated component to the entity.
		/// </summary>
		Add = 1,

		/// <summary>
		/// Remove the associated component from the entity.
		/// </summary>
		Remove = 2,
	};

	MINTY_ENUM_OPERATORS(AnimationActionType)

	String to_string(AnimationActionType const obj);
	AnimationActionType parse_to_animation_action_type(String const& string);
	Bool parse_try_animation_action_type(String const& string, AnimationActionType& value);
	template<>
	inline AnimationActionType parse_to<AnimationActionType>(String const& string) { return parse_to_animation_action_type(string); }
	template<>
	inline Bool parse_try<AnimationActionType>(String const& string, AnimationActionType& value) { return parse_try_animation_action_type(string, value); }
}