#include "pch.h"
#include "Animation.h"
#include "Minty/Animation/AnimationInfo.h"
#include "Minty/Animation/AnimationActionFlags.h"
#include "Minty/Application/Application.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/TextReader.h"
#include "Minty/Serialization/TextWriter.h"
#include "Minty/Stream/MemoryStream.h"

using namespace Minty;

Minty::Animation::Animation(AnimationInfo const& info)
	: Asset(info.id)
	, m_duration(info.duration)
	, m_loop(info.loop)
	, m_entities(info.entities)
	, m_components()
	, m_variables()
	, m_values(info.values)
	, m_steps()
	, m_resetSteps()
{
	// set the variables
	m_variables.reserve(info.rigidVariables.get_size() + info.smoothVariables.get_size());
	for (auto const& variable : info.rigidVariables)
	{
		m_variables.add({ variable, false });
	}
	for (auto const& variable : info.smoothVariables)
	{
		m_variables.add({ variable, true });
	}

	// get the component infos from the names
	m_components.resize(info.components.get_size(), nullptr);
	Application& app = Application::get_singleton();
	for (Size i = 0; i < info.components.get_size(); i++)
	{
		// get the component info
		// TODO: Fix this line... could cause issues in the future
		m_components.at(i) = &EntityManager::get_component_info(info.components.at(i));
		MINTY_ASSERT_F(m_components.at(i) != nullptr, ErrorCode::Component_NotRegistered, info.components.at(i));
	}

	// make space for the steps
	m_steps.reserve(info.steps.get_size());
	Float lastTime = -1.0f;
	Map<StepKey, Set<StepValue>> valuesEdited;
	for (auto const& [time, actionIndices] : info.steps)
	{
		MINTY_ASSERT_F(time >= 0.0f, ErrorCode::Animation_NegativeTime, time);
		MINTY_ASSERT_F(time != lastTime, ErrorCode::Animation_DuplicateTime, time);
		MINTY_ASSERT_F(time > lastTime, ErrorCode::Animation_IncorrectTimeOrder, time);

		// create the steplist
		for(Size const actionIndex : actionIndices)
		{
			MINTY_ASSERT_F(actionIndex < info.actions.get_size(), ErrorCode::Animation_InvalidActionIndex, actionIndex);

			AnimationAction const& action = info.actions.at(actionIndex);
			StepKey key;
			Vector<StepValue> values;
			build_action(key, values, action);

			// add values to the set of edited values
			if(!valuesEdited.contains(key))
			{
				valuesEdited.add(key, Set<StepValue>{});
			}
			Set<StepValue>& valuesEditedSet = valuesEdited.at(key);
			for(auto const& value : values)
			{
				valuesEditedSet.add(value);
			}

			// add the key and values to the step list
			auto it = m_steps.find(key);
			if (it != m_steps.end())
			{
				// if the key already exists, add the values to the existing step
				auto& [count, actionList] = it->get_second();
				count = static_cast<UInt>(valuesEditedSet.get_size());
				actionList.add({time, std::move(values)});
				continue;
			}
			else
			{
				// if the key does not exist, create a new step
				m_steps.add(key, {
					static_cast<UInt>(valuesEditedSet.get_size()), 
					Vector<Tuple<Float, Vector<StepValue>>>{ {time, std::move(values) } }
					});
			}
		}

		lastTime = time;
	}

	// do the same for the reset steps
	m_resetSteps.reserve(info.resetSteps.get_size());
	Set<StepValue> valuesEditedSet;
	for(auto const& actionIndex : info.resetSteps)
	{
		MINTY_ASSERT_F(actionIndex < info.actions.get_size(), ErrorCode::Animation_InvalidActionIndex, actionIndex);

		AnimationAction const& action = info.actions.at(actionIndex);
		StepKey key;
		Vector<StepValue> values;
		build_action(key, values, action);
		auto it = m_resetSteps.find(key);
		if (it != m_resetSteps.end())
		{
			// if the key already exists, add the values to the existing step
			auto& [count, actionList] = it->get_second();
			count = static_cast<UInt>(valuesEditedSet.get_size());
			actionList = std::move(values);
			continue;
		}
		else
		{
			// if the key does not exist, create a new step
			m_resetSteps.add(key, {
				static_cast<UInt>(valuesEditedSet.get_size()), 
				std::move(values)
				});
		}
	}

	// if no entities given, default to the root entity
	if (m_entities.is_empty())
	{
		m_entities.add(EntityPath{});
	}
}

Animation::StepKey Minty::Animation::compile_key(Index const entityIndex, Index const componentIndex, AnimationActionFlags const type) const
{
	// pack the indices into a single key
	return
		static_cast<StepKey>(((entityIndex & MAX_ENTITY_INDEX) << ENTITY_OFFSET) |
			((componentIndex & MAX_COMPONENT_INDEX) << COMPONENT_OFFSET) |
			((static_cast<StepKey>(type) & MAX_FLAGS_INDEX) << FLAGS_OFFSET));
}

void Minty::Animation::extract_key(StepKey const key, Index& entityIndex, Index& componentIndex, AnimationActionFlags& type) const
{
	// extract the entity and component indices from the key
	entityIndex = static_cast<Index>((key >> ENTITY_OFFSET) & MAX_ENTITY_INDEX);
	componentIndex = static_cast<Index>((key >> COMPONENT_OFFSET) & MAX_COMPONENT_INDEX);
	type = static_cast<AnimationActionFlags>((key >> FLAGS_OFFSET) & MAX_FLAGS_INDEX);
}

Animation::StepValue Minty::Animation::compile_value(Index const variableIndex, Index const valueIndex) const
{
	// pack the value and flags into a single value
	return
		static_cast<StepValue>(
			((variableIndex & MAX_VARIABLE_INDEX) << VARIABLE_OFFSET) |
			((valueIndex & MAX_VALUE_INDEX) << VALUE_OFFSET));
}

void Minty::Animation::extract_value(StepValue const value, Index& variableIndex, Index& valueIndex) const
{
	// extract the variable index, value index, and flags from the value
	variableIndex = static_cast<Index>((value >> VARIABLE_OFFSET) & MAX_VARIABLE_INDEX);
	valueIndex = static_cast<Index>((value >> VALUE_OFFSET) & MAX_VALUE_INDEX);
}

void Minty::Animation::build_action(StepKey& key, Vector<StepValue>& values, AnimationAction const& action) const
{
	// compile the values
	values.clear();
	values.reserve(action.values.get_size());
	Bool hasSmooth = false;
	for (auto const& [variableIndex, valueIndex] : action.values)
	{
		// compile the value
		values.add(compile_value(variableIndex, valueIndex));
		hasSmooth |= m_variables.at(variableIndex).get_second();
	}

	// if the action has smooth variables, it must be a smooth action
	AnimationActionFlags type = action.type;
	if (hasSmooth)
	{
		type |= AnimationActionFlags::Smooth;
	}

	// compile the key
	key = compile_key(action.entityIndex, action.componentIndex, type);
}

void Minty::Animation::perform_action(StepKey const key, Vector<StepValue> const& values, Entity const thisEntity, EntityManager& entityManager) const
{
	// extract the key
	AnimationAction action;
	extract_key(key, action.entityIndex, action.componentIndex, action.type);

	// clear the values
	action.values.clear();
	action.values.reserve(values.get_size());

	// extract each value
	for (auto const value : values)
	{
		Index variableIndex, valueIndex;
		extract_value(value, variableIndex, valueIndex);
		action.values.add({ variableIndex, valueIndex });
	}

	// perform the action
	perform_action(action, thisEntity, entityManager);
}

void Minty::Animation::perform_action(AnimationAction const& action, Entity const thisEntity, EntityManager& entityManager) const
{
	MINTY_ASSERT_F(action.entityIndex < MAX_ENTITY_INDEX, ErrorCode::Animation_InvalidEntityIndex, action.entityIndex);

	// get the entity based on the path
	Entity entity = entityManager.get_entity(thisEntity, m_entities.at(action.entityIndex));

	// if no entity, do nothing
	if (entity == INVALID_ENTITY)
	{
		MINTY_ERROR(ErrorCode::Animation_EntityNotFound);
		return;
	}

	MINTY_ASSERT_F(action.componentIndex < MAX_COMPONENT_INDEX, ErrorCode::Animation_InvalidComponentIndex, action.componentIndex);

	// get the component
	ComponentData const* componentInfo = m_components.at(action.componentIndex);
	Component* component = componentInfo->get(entityManager, entity);

	// determine what to do based on the flags
	if ((action.type & AnimationActionFlags::Add) != AnimationActionFlags::None)
	{
		if (component == nullptr)
		{
			component = &componentInfo->create(entityManager, entity);
		}
		return;
	}
	if ((action.type & AnimationActionFlags::Remove) != AnimationActionFlags::None)
	{
		if (component != nullptr)
		{
			componentInfo->destroy(entityManager, entity);
		}
		return;
	}

	// normal step
	MINTY_ASSERT(component != nullptr, ErrorCode::Animation_ComponentNotFound);

	// build and add all of the values to set
	Shared<DynamicContainer> const container = Shared<DynamicContainer>::create();
	Shared<Stream> const stream = Shared<MemoryStream>::create(container);
	
	// TODO: do not use text writer, use binary writer
	TextWriter writer(stream);
	for (auto const& [variableIndex, valueIndex] : action.values)
	{
		// get the variable name
		String const& variableName = m_variables.at(variableIndex).get_first();

		// get a copy of the value to set
		Node const& value = m_values.at(valueIndex);
		String const strValue = Parser<Node>::to_string(value);
		
		// write the value to the writer
		writer.write(variableName, strValue);
	}

	// create serialization data
	EntitySerializationData data
	{
		.entity = entity,
		.entityManager = &entityManager
	};

	// deserialize the data
	stream->set_position(0);
	TextReader reader(stream);
	reader.push_user_data(&data);
	componentInfo->deserialize(reader, *component);
	reader.pop_user_data();
}

template<typename T>
static Bool interpolate_nodes(String const& left, String const& right, Float const t, String& result)
{
	T leftValue, rightValue;
	if (Parser<T>::parse(left, leftValue) && Parser<T>::parse(right, rightValue))
	{
		// if both are valid, interpolate
		T interpolatedValue = static_cast<T>(Math::lerp(leftValue, rightValue, t));
		result = Parser<T>::to_string(interpolatedValue);
		return true;
	}
	return false;
}

// return true when animation is completed
Bool Minty::Animation::animate(Float& time, Float const elapsedTime, Entity const thisEntity, EntityManager& entityManager) const
{
	// check if already completed
	if (time >= m_duration)
	{
		return true;
	}

	// get the new time
	Float const newTime = time + elapsedTime;

	// check interpolated steps
	for (auto const& [key, stepList] : m_steps)
	{
		auto const& [count, times] = stepList;

		// skip, if the time is not within the step range
		if (newTime < times.front().get_first() || (time > 0.0f && time >= times.back().get_first()))
		{
			continue;
		}

		// check if the key is smooth or rigid
		Index entityIndex, componentIndex;
		AnimationActionFlags type;
		extract_key(key, entityIndex, componentIndex, type);

		// get the entity
		Entity const entity = entityManager.get_entity(thisEntity, m_entities.at(entityIndex));
		MINTY_ASSERT_F(entity != INVALID_ENTITY, ErrorCode::Animation_EntityNotFound, Parser<EntityPath>::to_string(m_entities.at(entityIndex)));

		// get the component
		ComponentData const* componentInfo = m_components.at(componentIndex);
		Component* component = componentInfo->get(entityManager, entity);

		// determine what to do based on the flags
		if ((type & AnimationActionFlags::Add) != AnimationActionFlags::None)
		{
			if (component == nullptr)
			{
				component = &componentInfo->create(entityManager, entity);
			}
			continue;
		}
		if ((type & AnimationActionFlags::Remove) != AnimationActionFlags::None)
		{
			if (component != nullptr)
			{
				componentInfo->destroy(entityManager, entity);
			}
			continue;
		}

		// normal step
		Bool const interpolate = (type & AnimationActionFlags::Smooth) != AnimationActionFlags::None;

		// behave differently based on the interpolation type
		if (interpolate)
		{
			// find the last value of each variable before the new time
			Size index = 0;
			for (; index < times.get_size(); index++)
			{
				auto const& [stepTime, values] = times.at(index);
				if (newTime < stepTime)
				{
					break;
				}
			}
			Map<Index, Tuple<Float, Index>> previousValues;
			for(Size i = 0; i < index; i++)
			{
				// get the index to check
				Size j = index - 1 - i;

				auto const& [stepTime, values] = times.at(j);

				// add to the previous variable values, if there is one to set
				for(auto const& value : values)
				{
					Index variableIndex, valueIndex;
					extract_value(value, variableIndex, valueIndex);
					if (!previousValues.contains(variableIndex))
					{
						previousValues.add(variableIndex, { stepTime, valueIndex });
					}
				}

				// if all variables have been set, break
				if (previousValues.get_size() == count)
				{
					break;
				}
			}
			Map<Index, Tuple<Float, Index>> nextValues;
			for (Size i = index; i < times.get_size(); i++)
			{
				auto const& [stepTime, values] = times.at(i);

				for (auto const& value : values)
				{
					Index variableIndex, valueIndex;
					extract_value(value, variableIndex, valueIndex);
					if (!nextValues.contains(variableIndex))
					{
						nextValues.add(variableIndex, { stepTime, valueIndex });
					}
				}

				// if all variables have been set, break
				if (nextValues.get_size() == count)
				{
					break;
				}
			}

			Shared<DynamicContainer> const container = Shared<DynamicContainer>::create();
			Shared<Stream> const stream = Shared<MemoryStream>::create(container);
			// TODO: replace with binary writer
			TextWriter writer(stream);
			for (auto const& [variableIndex, timeValue] : previousValues)
			{
				auto const& [previousTime, previousValueIndex] = timeValue;
				auto const& [variableName, variableSmooth] = m_variables.at(variableIndex);
				auto it = nextValues.find(variableIndex);

				if(!variableSmooth || it == nextValues.end())
				{
					// if no next value, no interpolation, use the previous value
					Node const& node = m_values.at(timeValue.get_second());
					String const nodeStr = Parser<Node>::to_string(node);
					writer.write(variableName, nodeStr);
				}
				else
				{
					// if next value exists, interpolate
					auto const& [nextTime, nextValueIndex] = it->get_second();
					Float t = (newTime - previousTime) / (nextTime - previousTime);

					Node const& previousNode = m_values.at(previousValueIndex);
					Node const& nextNode = m_values.at(it->get_second().get_second());
					String previousValue = previousNode.get_data_string();
					String nextValue = nextNode.get_data_string();
					String resultValue;

					// figure out the type of the variable based on the value
					if (interpolate_nodes<Int64>(previousValue, nextValue, t, resultValue)) {} // signed integers
					else if (interpolate_nodes<Float64>(previousValue, nextValue, t, resultValue)) {} // floating point values
					else if (interpolate_nodes<Int2>(previousValue, nextValue, t, resultValue)) {} // int2
					else if (interpolate_nodes<Int3>(previousValue, nextValue, t, resultValue)) {} // int3
					else if (interpolate_nodes<Int4>(previousValue, nextValue, t, resultValue)) {} // int4
					else if (interpolate_nodes<Float2>(previousValue, nextValue, t, resultValue)) {} // float2
					else if (interpolate_nodes<Float3>(previousValue, nextValue, t, resultValue)) {} // float3
					else if (interpolate_nodes<Float4>(previousValue, nextValue, t, resultValue)) {} // float4
					else
					{
						MINTY_LOG_ERROR(F("Interpolation between \"{}\" and \"{}\" is not supported.", previousValue, nextValue));
					}

					// create the node with the interpolated value and add it to the root
					writer.write(variableName, resultValue);
				}
			}

			// create serialization data
			EntitySerializationData data
			{
				.entity = entity,
				.entityManager = &entityManager
			};

			// deserialize the data
			TextReader reader(stream);
			reader.push_user_data(&data);
			componentInfo->deserialize(reader, *component);
			reader.pop_user_data();
		}
		else
		{
			// find and act on any steps that are after the current time, and before the new time
			for (Size i = 0; i < times.get_size(); i++)
			{
				auto const& [stepTime, values] = times.at(i);
				if (time > stepTime)
				{
					// to early, skip
					continue;
				}

				if (newTime < stepTime)
				{
					// too late, break
					break;
				}

				// found the step
				perform_action(key, values, thisEntity, entityManager);
			}
		}
	}

	// update the time
	time = newTime;

	// check if the animation is completed
	return time >= m_duration;
}

void Minty::Animation::reset(Entity const thisEntity, EntityManager& entityManager)
{
	// perform each step within reset
	for(auto const& [key, step] : m_resetSteps)
	{
		// perform the action
		perform_action(key, step.get_second(), thisEntity, entityManager);
	}
}

Shared<Animation> Minty::Animation::create(AnimationInfo const& info)
{
	return Shared<Animation>::create(info);
}

Shared<Animation> Minty::Animation::create()
{
	AnimationInfo info{};
	return create(info);
}