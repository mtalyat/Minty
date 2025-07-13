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
	, m_variables(builder.variables)
	, m_values(builder.values)
	, m_steps()
	, m_resetSteps()
{
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
	for (auto const& [time, actionIndices] : builder.steps)
	{
		MINTY_ASSERT(time >= 0.0f, "Time must be non-negative.");
		MINTY_ASSERT(time > lastTime, "Times must be in ascending order. Do not duplicate times.");

		// create the steplist
		StepList stepList;
		build_step_list(stepList, builder.actions, actionIndices);

		// add the steplist to the steps
		m_steps.add({ time, std::move(stepList) });

		lastTime = time;
	}

	// do the same for the reset steps
	m_resetSteps.reserve(builder.resetSteps.get_size());
	build_step_list(m_resetSteps, builder.actions, builder.resetSteps);

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

void Minty::Animation::build_step_list(StepList& stepList, Vector<AnimationAction> const& actions, Vector<Size> const& actionIndices) const
{
	// add each step
	for (auto const& index : actionIndices)
	{
		AnimationAction const& action = actions.at(index);

		// compile the key
		StepKey key = compile_key(action.entityIndex, action.componentIndex, action.type);

		// compile the values
		Vector<StepValue> values(action.values.get_size());
		for (auto const& [variableIndex, valueIndex] : action.values)
		{
			// compile the value
			values.add(compile_value(variableIndex, valueIndex));
		}

		// add the compiled values to the step list
		stepList.add({ key, std::move(values) });
	}
}

void Minty::Animation::perform_step(StepList const& stepList, Entity const thisEntity, EntityManager& entityManager) const
{
	AnimationAction action;
	for(auto const& [stepKey, valueList] : stepList)
	{
		// extract the key
		extract_key(stepKey, action.entityIndex, action.componentIndex, action.type);
		
		// clear the values
		action.values.clear();
		action.values.reserve(valueList.get_size());

		// extract each value
		for(auto const value : valueList)
		{
			Index variableIndex, valueIndex;
			extract_value(value, variableIndex, valueIndex);
			action.values.add({ variableIndex, valueIndex });
		}

		// perform the action
		perform_action(action, thisEntity, entityManager);
	}
}

void Minty::Animation::perform_action(AnimationAction const& step, Entity const thisEntity, EntityManager& entityManager) const
{
	MINTY_ASSERT(step.entityIndex < MAX_ENTITY_INDEX, "Entity index is out of range.");

	// get the entity based on the path
	Entity entity = entityManager.get_entity(thisEntity, m_entities.at(step.entityIndex));

	// if no entity, do nothing
	if (entity == INVALID_ENTITY)
	{
		MINTY_ERROR("Animation Entity not found.");
		return;
	}

	MINTY_ASSERT(step.componentIndex < MAX_COMPONENT_INDEX, "Component index is out of range.");

	// get the component
	ComponentInfo const* componentInfo = m_components.at(step.componentIndex);
	Component* component = componentInfo->get(entityManager, entity);

	// determine what to do based on the flags
	if (step.type == AnimationActionType::Add)
	{
		if (component == nullptr)
		{
			component = &componentInfo->create(entityManager, entity);
		}
		return;
	}
	if (step.type == AnimationActionType::Remove)
	{
		if (component != nullptr)
		{
			componentInfo->destroy(entityManager, entity);
		}
		return;
	}

	// normal step

	// build and add all of the values to set
	Node root{};
	for(auto const& [variableIndex, valueIndex] : step.values)
	{
		// get the variable name
		String const& variableName = m_variables.at(variableIndex);

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

Bool Minty::Animation::animate(Float& time, Float const elapsedTime, Index& index, Entity const thisEntity, EntityManager& entityManager) const
{
	// check if already completed
	if (time >= m_duration)
	{
		return true;
	}

	// increase time
	time += elapsedTime;

	// if no more times in the animation, do nothing
	if (index >= m_steps.get_size())
	{
		return false;
	}

	Float const nextTime = m_steps.at(index).get_first();

	// if current time < the next time, wait and do nothing
	if (time < nextTime)
	{
		return false;
	}

	// find the index range
	Index i = index;
	for (; i < m_steps.get_size(); i++)
	{
		// get the step
		auto const& step = m_steps.at(i);

		// if the time is less than the step's time, we are done
		if (time < step.get_first())
		{
			break;
		}

		// perform the step
		StepList const& stepList = step.get_second();
		perform_step(stepList, thisEntity, entityManager);
	}

	// update index
	index = i + 1;

	// check if we are done
	return time >= m_duration;
}

void Minty::Animation::reset(Entity const thisEntity, EntityManager& entityManager)
{
	// perform each step within reset
	perform_step(m_resetSteps, thisEntity, entityManager);
}

Owner<Animation> Minty::Animation::create(AnimationBuilder const& builder)
{
	return Owner<Animation>(builder);
}
