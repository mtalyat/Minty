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
	, m_times()
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
	m_steps.reserve(builder.steps.get_size() * 2);
	for (auto const& [time, steps] : builder.steps)
	{
		MINTY_ASSERT(m_times.is_empty() || m_times.at(m_times.get_size() - 1) < time, "Times must be in ascending order.");

		// get time index and add to times
		StepTime timeIndex = static_cast<StepTime>(m_times.get_size());
		m_times.add(time);

		// add each step
		for (auto const& index : steps)
		{
			AnimationAction const& step = builder.actions.at(index);

			// compile the key
			StepKey key = compile_key(step.entityIndex, step.componentIndex, step.variableIndex);

			// compile the value
			StepValue value = compile_value(step.valueIndex, step.type);

			// add the compiled values to the steps
			m_steps[key].add(timeIndex, value);
		}
	}

	// do the same for the reset steps
	m_resetSteps.reserve(builder.resetSteps.get_size() * 2);
	for (auto const& index : builder.resetSteps)
	{
		AnimationAction const& step = builder.actions.at(index);

		// compile the key
		StepKey key = compile_key(step.entityIndex, step.componentIndex, step.variableIndex);
		
		// compile the value
		StepValue value = compile_value(step.valueIndex, step.type);

		// add the compiled values to the reset steps
		m_resetSteps[key].add(value);
	}
}

Animation::StepKey Minty::Animation::compile_key(Index const entityIndex, Index const componentIndex, Index const variableIndex) const
{
	// pack the indices into a single key
	return
		((entityIndex & MAX_ENTITY_INDEX) << ENTITY_OFFSET) |
		((componentIndex & MAX_COMPONENT_INDEX) << COMPONENT_OFFSET) |
		((variableIndex & MAX_VARIABLE_INDEX) << VARIABLE_OFFSET);
}

Animation::StepValue Minty::Animation::compile_value(Index const valueIndex, AnimationActionType const flags) const
{
	// pack the value and flags into a single value
	return
		((valueIndex & MAX_VALUE_INDEX) << VALUE_OFFSET) |
		((static_cast<UInt>(flags) & MAX_FLAGS_INDEX) << FLAGS_OFFSET);
}

void Minty::Animation::perform_step(StepKey const key, StepTime const time, StepValue const value, Entity const thisEntity, EntityManager& entityManager) const
{
	// unpack the step
	AnimationAction step{};
	step.entityIndex = (key >> ENTITY_OFFSET) & MAX_ENTITY_INDEX;
	step.componentIndex = (key >> COMPONENT_OFFSET) & MAX_COMPONENT_INDEX;
	step.variableIndex = (key >> VARIABLE_OFFSET) & MAX_VARIABLE_INDEX;
	step.timeIndex = (time >> TIME_OFFSET) & MAX_TIME_INDEX;
	step.valueIndex = (value >> VALUE_OFFSET) & MAX_VALUE_INDEX;
	step.type = static_cast<AnimationActionType>((value >> FLAGS_OFFSET) & MAX_FLAGS_INDEX);

	// perform the step
	return perform_step(step, thisEntity, entityManager);
}

void Minty::Animation::perform_step(AnimationAction const& step, Entity const thisEntity, EntityManager& entityManager) const
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

	MINTY_ASSERT(step.variableIndex < MAX_VARIABLE_INDEX, "Variable index is out of range.");
	
	// get the variable name
	String const& variableName = m_variables.at(step.variableIndex);

	MINTY_ASSERT(step.valueIndex < MAX_VALUE_INDEX, "Value index is out of range.");

	// get a copy of the value to set
	Node value = m_values.at(step.valueIndex);
	value.set_name(variableName);

	// create serialization data
	EntitySerializationData data
	{
		.entity = entity,
		.entityManager = &entityManager
	};

	// create a root node for the deserialization
	Node root;
	root.add_child(std::move(value));

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
	if (index >= m_times.get_size())
	{
		return false;
	}

	// if current time < the next time, wait and do nothing
	if (time < m_times.at(index))
	{
		return false;
	}

	// find the index range
	Index endIndex = index;
	Index nextIndex = index + 1;
	while (nextIndex < m_times.get_size() && time >= m_times.at(nextIndex))
	{
		// increment the end index
		endIndex = nextIndex;
		nextIndex++;
	}

	// go through each step list
	for (auto const& [stepKey, map] : m_steps)
	{
		// start at end, apply first value that shows up, if any
		for (Long i = endIndex; i >= index; i--)
		{
			auto found = map.find(static_cast<StepKey>(i));
			if (found != map.end())
			{
				// perform step since a step was found
				perform_step(stepKey, found->get_first(), found->get_second(), thisEntity, entityManager);
				break;
			}
		}
	}

	// update index
	index = endIndex + 1;

	// check if we are done
	return time >= m_duration;
}

void Minty::Animation::reset(Entity const thisEntity, EntityManager& entityManager)
{
	// perform each step within reset
	for (auto const& [stepKey, values] : m_resetSteps)
	{
		for (auto const& value : values)
		{
			// perform the step
			perform_step(stepKey, 0, value, thisEntity, entityManager);
		}
	}
}

Owner<Animation> Minty::Animation::create(AnimationBuilder const& builder)
{
	return Owner<Animation>(builder);
}
