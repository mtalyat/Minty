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
	// format: type?:entity/component:variable/value,variable/value,variable/value...
	Vector<String> halves = text.split(ANIMATION_ACTION_HALF);
	MINTY_ASSERT(halves.get_size() == 2 || halves.get_size() == 3, F("AnimationAction must have exactly one or two '{}' to split into halves.", ANIMATION_ACTION_HALF));

	Vector<String> majorParts = halves.at(0).split(ANIMATION_ACTION_DELIMITER);
	MINTY_ASSERT(majorParts.get_size() == 2, F("AnimationAction must have at 2 parts before the last '{}', split by '{}'.", ANIMATION_ACTION_HALF, ANIMATION_ACTION_DELIMITER));

	Vector<String> minorParts = halves.at(1).split(ANIMATION_ACTION_GROUP);

	// set major data
	if (halves.get_size() == 3)
	{
		// if there are 3 halves, the first is the type
		String const& typeString = halves.at(0);
		if (typeString == "A")
		{
			type = AnimationActionType::Add;
		}
		else if (typeString == "R")
		{
			type = AnimationActionType::Remove;
		}
		else if (typeString.is_empty())
		{
			type = AnimationActionType::None;
		}
		else
		{
			type = parse_to_animation_action_type(halves.at(0));
		}
	}
	else
	{
		// default to None if there are only 2 halves
		type = AnimationActionType::None;
	}
	entityIndex = get_split(0, majorParts, Animation::MAX_ENTITY_INDEX);
	componentIndex = get_split(1, majorParts, Animation::MAX_COMPONENT_INDEX);

	// set minor data
	values.resize(minorParts.get_size(), Tuple<UInt, UInt>());
	for (Size i = 0; i < minorParts.get_size(); i++)
	{
		Vector<String> parts = minorParts.at(i).split(ANIMATION_ACTION_DELIMITER);
		MINTY_ASSERT(parts.get_size() == 2, F("AnimationAction value at index {} must have exactly one '{}' to split into parts.", i, ANIMATION_ACTION_DELIMITER));

		UInt variableIndex = get_split(0, parts, Animation::MAX_VARIABLE_INDEX);
		UInt valueIndex = get_split(1, parts, Animation::MAX_VALUE_INDEX);
		values[i] = Tuple<UInt, UInt>(variableIndex, valueIndex);
	}

	return true;
}

String Minty::AnimationAction::to_string() const
{
	// get major half
	String flagString = type == AnimationActionType::None ? "" : Minty::to_string(static_cast<UInt>(type));
	String entityString = entityIndex == Animation::MAX_ENTITY_INDEX ? "" : Minty::to_string(entityIndex);
	String componentString = componentIndex == Animation::MAX_COMPONENT_INDEX ? "" : Minty::to_string(componentIndex);
	String majorString = F("{}{}{}{}{}", flagString, ANIMATION_ACTION_DELIMITER, entityString, ANIMATION_ACTION_DELIMITER, componentString);

	// get minor half
	String minorString = "";
	for (Size i = 0; i < values.get_size(); i++)
	{
		if (i > 0)
		{
			minorString += String(ANIMATION_ACTION_GROUP, 1);
		}
		auto const [variableIndex, valueIndex] = values.at(i);
		String variableString = variableIndex == Animation::MAX_VARIABLE_INDEX ? "" : Minty::to_string(variableIndex);
		String valueString = valueIndex == Animation::MAX_VALUE_INDEX ? "" : Minty::to_string(valueIndex);
		minorString += F("{}{}{}", variableString, ANIMATION_ACTION_DELIMITER, valueString);
	}

	return F("{}{}{}", majorString, ANIMATION_ACTION_HALF, minorString);
}
