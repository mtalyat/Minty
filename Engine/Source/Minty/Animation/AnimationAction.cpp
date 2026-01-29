#include "pch.h"
#include "AnimationAction.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Core/Format.h"
#include "Minty/Tool/String.h"
#include "Minty/Serialization/Parser.h"

using namespace Minty;

static UInt get_split(Size const index, Vector<String> const& split, UInt const defaultValue)
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
	if (!Parser<UInt>::parse(part, value))
	{
		return defaultValue;
	}
	return value;
}

Bool Minty::Parser<AnimationAction>::parse(StringView const str, AnimationAction &value)
{
    // format: type?:entity/component:variable/value,variable/value,variable/value...
	StringBuilder textBuilder(str);
	textBuilder.strip();
	String const strippedText = textBuilder.get_string();
	Vector<String> halves = Tool::split(strippedText, ANIMATION_ACTION_HALF);
	MINTY_ASSERT_F(halves.get_size() == 2 || halves.get_size() == 3, ErrorCode::Animation_InvalidActionFormat, strippedText);

	Size offset = 0;

	// check if first one is the type
	String const& typeString = halves.at(0);
	value.type = AnimationActionFlags::None;
	if (typeString.get_size() == 1 && isalpha(typeString.front()))
	{
		Char typeChar = toupper(typeString.front());
		offset = 1; // skip the type part

		MINTY_ASSERT_F(typeChar == 'A' || typeChar == 'R', ErrorCode::Animation_InvalidActionType, typeChar);

		if (typeChar == 'A')
		{
			value.type = AnimationActionFlags::Add;
		}
		else if (typeChar == 'R')
		{
			value.type = AnimationActionFlags::Remove;
		}
	}

	Vector<String> majorParts = Tool::split(halves.at(offset), ANIMATION_ACTION_DELIMITER);
	// AnimationAction must have at 2 parts before the last ANIMATION_ACTION_HALF, split by ANIMATION_ACTION_DELIMITER
	MINTY_ASSERT_F(majorParts.get_size() == 2, ErrorCode::Animation_InvalidActionFormat, strippedText);
	Vector<String> minorParts;
	if (offset + 1 < halves.get_size())
	{
		minorParts = Tool::split(halves.at(offset + 1), ANIMATION_ACTION_GROUP);
	}

	value.entityIndex = get_split(0, majorParts, Animation::MAX_ENTITY_INDEX);
	value.componentIndex = get_split(1, majorParts, Animation::MAX_COMPONENT_INDEX);

	// set minor data
	value.values.resize(minorParts.get_size(), Tuple<UInt, UInt>());
	for (Size i = 0; i < minorParts.get_size(); i++)
	{
		Vector<String> parts = Tool::split(minorParts.at(i), ANIMATION_ACTION_DELIMITER);
		// AnimationAction value at index i must have exactly one ANIMATION_ACTION_DELIMITER
		MINTY_ASSERT_F(parts.get_size() == 2, ErrorCode::Animation_InvalidActionFormat, strippedText);

		UInt variableIndex = get_split(0, parts, Animation::MAX_VARIABLE_INDEX);
		UInt valueIndex = get_split(1, parts, Animation::MAX_VALUE_INDEX);
		value.values[i] = Tuple<UInt, UInt>(variableIndex, valueIndex);
	}

	return true;
}

String Minty::Parser<AnimationAction>::to_string(AnimationAction const &value)
{
    StringBuilder builder;

	// get major half
	String flagString = value.type == AnimationActionFlags::None ? "" : Parser<UInt>::to_string(static_cast<UInt>(value.type));
	String entityString = value.entityIndex == Animation::MAX_ENTITY_INDEX ? "" : Parser<UInt>::to_string(value.entityIndex);
	String componentString = value.componentIndex == Animation::MAX_COMPONENT_INDEX ? "" : Parser<UInt>::to_string(value.componentIndex);
	builder.append(flagString);
	builder.append(ANIMATION_ACTION_DELIMITER);
	builder.append(entityString);
	builder.append(ANIMATION_ACTION_DELIMITER);
	builder.append(componentString);

	// add separator
	builder.append(ANIMATION_ACTION_HALF);

	// get minor half
	for (Size i = 0; i < value.values.get_size(); i++)
	{
		if (i > 0)
		{
			builder.append(ANIMATION_ACTION_GROUP);
		}
		auto const [variableIndex, valueIndex] = value.values.at(i);
		String variableString = variableIndex == Animation::MAX_VARIABLE_INDEX ? "" : Parser<UInt>::to_string(variableIndex);
		String valueString = valueIndex == Animation::MAX_VALUE_INDEX ? "" : Parser<UInt>::to_string(valueIndex);
		builder.append(variableString);
		builder.append(ANIMATION_ACTION_DELIMITER);
		builder.append(valueString);
	}

	return builder.get_string();
}
