#include "pch.h"
#include "AnimationActionFlags.h"

using namespace Minty;

String Minty::to_string(AnimationActionType const obj)
{
	switch (obj)
	{
	case AnimationActionType::Add: return "Add";
	case AnimationActionType::Remove: return "Remove";

	default: return "";
	}
}

AnimationActionType Minty::parse_to_animation_action_type(String const& string)
{
	if (string == "Add") return AnimationActionType::Add;
	if (string == "Remove") return AnimationActionType::Remove;

	return AnimationActionType();
}

Bool Minty::parse_try_animation_action_type(String const& string, AnimationActionType& value)
{
	value = parse_to_animation_action_type(string);
	return true;
}