#include "pch.h"
#include "AnimationAction.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Core/Format.h"

using namespace Minty;

UInt get_split(Size const index, Vector<String> const& split, UInt const defaultValue)
{
	if (index >= split.get_size())
	{
		return defaultValue;
	}
	String const& part = split.at(index);
	if (part.is_empty())
	{
		return defaultValue;
	}
	UInt value = 0;
	if (!try_uint(part, value))
	{
		return defaultValue;
	}
	return value;
}

Bool Minty::AnimationAction::parse(String const& text)
{
	// split into parts based on /
	Vector<String> parts = String::split(text, '/');

	// create the step
	entityIndex = get_split(1, parts, Animation::MAX_ENTITY_INDEX);
	componentIndex = get_split(2, parts, Animation::MAX_COMPONENT_INDEX);
	variableIndex = get_split(3, parts, Animation::MAX_VARIABLE_INDEX);
	timeIndex = Animation::MAX_TIME_INDEX;
	valueIndex = get_split(4, parts, Animation::MAX_VALUE_INDEX);
	type = static_cast<AnimationActionType>(get_split(0, parts, 0));

	return true;
}

String Minty::AnimationAction::to_string() const
{
	String flagString = type == AnimationActionType::None ? "" : Minty::to_string(static_cast<UInt>(type));
	String entityString = entityIndex == Animation::MAX_ENTITY_INDEX ? "" : Minty::to_string(entityIndex);
	String componentString = componentIndex == Animation::MAX_COMPONENT_INDEX ? "" : Minty::to_string(componentIndex);
	String variableString = variableIndex == Animation::MAX_VARIABLE_INDEX ? "" : Minty::to_string(variableIndex);
	String valueString = valueIndex == Animation::MAX_VALUE_INDEX ? "" : Minty::to_string(valueIndex);

	return F("{}/{}/{}/{}/{}", flagString, entityString, componentString, variableString, valueString);
}
