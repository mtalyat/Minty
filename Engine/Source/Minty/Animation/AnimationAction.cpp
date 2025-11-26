#include "pch.h"
#include "AnimationAction.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Core/Format.h"
#include "Minty/Tool/Util.h"

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
	String strippedText = text.strip();
	Vector<String> halves = Util::split(strippedText, ANIMATION_ACTION_HALF);
	MINTY_ASSERT(halves.get_size() == 2 || halves.get_size() == 3, ErrorCode::Animation_InvalidActionFormat, strippedText);

	Size offset = 0;

	// check if first one is the type
	String const& typeString = halves.at(0);
	type = AnimationActionType::None;
	if (typeString.get_size() == 1 && isalpha(typeString.front()))
	{
		Char typeChar = toupper(typeString.front());
		offset = 1; // skip the type part

		MINTY_ASSERT(typeChar == 'A' || typeChar == 'R', ErrorCode::Animation_InvalidActionType, typeChar);

		if (typeChar == 'A')
		{
			type = AnimationActionType::Add;
		}
		else if (typeChar == 'R')
		{
			type = AnimationActionType::Remove;
		}
	}

	Vector<String> majorParts = Util::split(halves.at(offset), ANIMATION_ACTION_DELIMITER);
	// AnimationAction must have at 2 parts before the last ANIMATION_ACTION_HALF, split by ANIMATION_ACTION_DELIMITER
	MINTY_ASSERT(majorParts.get_size() == 2, ErrorCode::Animation_InvalidActionFormat, strippedText);
	Vector<String> minorParts;
	if (offset + 1 < halves.get_size())
	{
		minorParts = Util::split(halves.at(offset + 1), ANIMATION_ACTION_GROUP);
	}

	entityIndex = get_split(0, majorParts, Animation::MAX_ENTITY_INDEX);
	componentIndex = get_split(1, majorParts, Animation::MAX_COMPONENT_INDEX);

	// set minor data
	values.resize(minorParts.get_size(), Tuple<UInt, UInt>());
	for (Size i = 0; i < minorParts.get_size(); i++)
	{
		Vector<String> parts = Util::split(minorParts.at(i), ANIMATION_ACTION_DELIMITER);
		// AnimationAction value at index i must have exactly one ANIMATION_ACTION_DELIMITER
		MINTY_ASSERT(parts.get_size() == 2, ErrorCode::Animation_InvalidActionFormat, strippedText);

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
