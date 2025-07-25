#include "pch.h"
#include "Animation.h"
#include "Minty/Context/Context.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Animation::Animation(AnimationBuilder const& builder)
	: Asset(builder.id)
	, m_duration(builder.duration)
	, m_loop(builder.loop)
	, m_entities(builder.entities)
	, m_components()
	, m_variables()
	, m_values(builder.values)
	, m_steps()
	, m_resetSteps()
{
	// set the variables
	m_variables.reserve(builder.rigidVariables.get_size() + builder.smoothVariables.get_size());
	for (auto const& variable : builder.rigidVariables)
	{
		m_variables.add({ variable, false });
	}
	for (auto const& variable : builder.smoothVariables)
	{
		m_variables.add({ variable, true });
	}

	// get the component infos from the names
	m_components.resize(builder.components.get_size(), nullptr);
	Context const& context = Context::get_singleton();
	for (Size i = 0; i < builder.components.get_size(); i++)
	{
		// get the component info
		m_components.at(i) = context.get_component_info(builder.components.at(i));
		MINTY_ASSERT(m_components.at(i) != nullptr, F("Component \"{}\" does not exist.", builder.components.at(i)));
	}

	// make space for the steps
	m_steps.reserve(builder.steps.get_size());
	Float lastTime = -1.0f;
	Map<StepKey, Set<StepValue>> valuesEdited;
	for (auto const& [time, actionIndices] : builder.steps)
	{
		MINTY_ASSERT(time >= 0.0f, "Time must be non-negative.");
		MINTY_ASSERT(time > lastTime, "Times must be in ascending order. Do not duplicate times.");

		// create the steplist
		for(Size const actionIndex : actionIndices)
		{
			MINTY_ASSERT(actionIndex < builder.actions.get_size(), "Action index is out of range.");

			AnimationAction const& action = builder.actions.at(actionIndex);
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
	m_resetSteps.reserve(builder.resetSteps.get_size());
	Set<StepValue> valuesEditedSet;
	for(auto const& actionIndex : builder.resetSteps)
	{
		MINTY_ASSERT(actionIndex < builder.actions.get_size(), "Action index is out of range.");

		AnimationAction const& action = builder.actions.at(actionIndex);
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

Animation::StepKey Minty::Animation::compile_key(Index const entityIndex, Index const componentIndex, AnimationActionType const type) const
{
	// pack the indices into a single key
	return
		static_cast<StepKey>(((entityIndex & MAX_ENTITY_INDEX) << ENTITY_OFFSET) |
			((componentIndex & MAX_COMPONENT_INDEX) << COMPONENT_OFFSET) |
			((static_cast<StepKey>(type) & MAX_FLAGS_INDEX) << FLAGS_OFFSET));
}

void Minty::Animation::extract_key(StepKey const key, Index& entityIndex, Index& componentIndex, AnimationActionType& type) const
{
	// extract the entity and component indices from the key
	entityIndex = static_cast<Index>((key >> ENTITY_OFFSET) & MAX_ENTITY_INDEX);
	componentIndex = static_cast<Index>((key >> COMPONENT_OFFSET) & MAX_COMPONENT_INDEX);
	type = static_cast<AnimationActionType>((key >> FLAGS_OFFSET) & MAX_FLAGS_INDEX);
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
	AnimationActionType type = action.type;
	if (hasSmooth)
	{
		type |= AnimationActionType::Smooth;
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
	MINTY_ASSERT(action.entityIndex < MAX_ENTITY_INDEX, "Entity index is out of range.");

	// get the entity based on the path
	Entity entity = entityManager.get_entity(thisEntity, m_entities.at(action.entityIndex));

	// if no entity, do nothing
	if (entity == INVALID_ENTITY)
	{
		MINTY_ERROR("Animation Entity not found.");
		return;
	}

	MINTY_ASSERT(action.componentIndex < MAX_COMPONENT_INDEX, "Component index is out of range.");

	// get the component
	ComponentInfo const* componentInfo = m_components.at(action.componentIndex);
	Component* component = componentInfo->get(entityManager, entity);

	// determine what to do based on the flags
	if ((action.type & AnimationActionType::Add) != AnimationActionType::None)
	{
		if (component == nullptr)
		{
			component = &componentInfo->create(entityManager, entity);
		}
		return;
	}
	if ((action.type & AnimationActionType::Remove) != AnimationActionType::None)
	{
		if (component != nullptr)
		{
			componentInfo->destroy(entityManager, entity);
		}
		return;
	}

	// normal step
	MINTY_ASSERT(component != nullptr, "Component is null. Cannot perform action.");

	// build and add all of the values to set
	Node root{};
	for (auto const& [variableIndex, valueIndex] : action.values)
	{
		// get the variable name
		String const& variableName = m_variables.at(variableIndex).get_first();

		// get a copy of the value to set
		Node value = m_values.at(valueIndex);
		value.set_name(variableName);

		// add the value to the root node
		root.add_child(std::move(value));
	}

	// create serialization data
	EntitySerializationData data
	{
		.entity = entity,
		.entityManager = &entityManager
	};

	// deserialize the data
	TextNodeReader reader(root);
	reader.push_user_data(&data);
	component->deserialize(reader);
	reader.pop_user_data();
}

template<typename T>
static Bool interpolate_nodes(String const& left, String const& right, Float const t, String& result, Bool(*try_func)(String const&, T&))
{
	T leftValue, rightValue;
	if (try_func(left, leftValue) && try_func(right, rightValue))
	{
		// if both are valid, interpolate
		T interpolatedValue = static_cast<T>(Math::lerp(leftValue, rightValue, t));
		result = to_string(interpolatedValue);
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
		AnimationActionType type;
		extract_key(key, entityIndex, componentIndex, type);

		// get the entity
		Entity entity = entityManager.get_entity(thisEntity, m_entities.at(entityIndex));

		// get the component
		ComponentInfo const* componentInfo = m_components.at(componentIndex);
		Component* component = componentInfo->get(entityManager, entity);

		// determine what to do based on the flags
		if ((type & AnimationActionType::Add) != AnimationActionType::None)
		{
			if (component == nullptr)
			{
				component = &componentInfo->create(entityManager, entity);
			}
			continue;
		}
		if ((type & AnimationActionType::Remove) != AnimationActionType::None)
		{
			if (component != nullptr)
			{
				componentInfo->destroy(entityManager, entity);
			}
			continue;
		}

		// normal step
		Bool const interpolate = (type & AnimationActionType::Smooth) != AnimationActionType::None;

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

			Node root;
			for (auto const& [variableIndex, timeValue] : previousValues)
			{
				auto const& [previousTime, previousValueIndex] = timeValue;
				auto const& [variableName, variableSmooth] = m_variables.at(variableIndex);
				auto it = nextValues.find(variableIndex);

				if(!variableSmooth || it == nextValues.end())
				{
					// if no next value, no interpolation, use the previous value
					Node node = m_values.at(timeValue.get_second());
					node.set_name(variableName);
					root.add_child(std::move(node));
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
					if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_long)) {} // signed integers
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_double)) {} // floating point values
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_int2)) {} // int2
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_int3)) {} // int3
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_int4)) {} // int4
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_float2)) {} // float2
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_float3)) {} // float3
					else if (interpolate_nodes(previousValue, nextValue, t, resultValue, try_float4)) {} // float4
					else
					{
						MINTY_ERROR(F("Interpolation between \"{}\" and \"{}\" is not supported.", previousValue, nextValue));
					}

					// create the node with the interpolated value and add it to the root
					Node node;
					node.set_name(variableName);
					node.set_data(resultValue);
					root.add_child(std::move(node));
				}
			}

			// create serialization data
			EntitySerializationData data
			{
				.entity = entity,
				.entityManager = &entityManager
			};

			// deserialize the data
			TextNodeReader reader(root);
			reader.push_user_data(&data);
			component->deserialize(reader);
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

Owner<Animation> Minty::Animation::create(AnimationBuilder const& builder)
{
	return Owner<Animation>(builder);
}
