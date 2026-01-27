#include "pch.h"
#include "FSM.h"
#include "Minty/Data/Set.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

UUID Minty::FSM::create_state(String const& name, Variable const& value)
{
	return add_state(name, State(value));
}

UUID Minty::FSM::add_state(String const& name, State const& state)
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);

	UUID id = UUID::create();
	// if no states, set this as the starting state and current state
	if (m_states.is_empty())
	{
		m_startingStateId = id;
		m_currentStateId = id;
	}
	m_states.add(name, id, state);
	return id;
}

UUID Minty::FSM::create_variable(String const& name, Int const value)
{
	MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	return m_scope.add(name, value);
}

Bool Minty::FSM::evaluate(Bool const continuous)
{
	// do nothing if no current state
	if (!has_current_state())
	{
		return false;
	}

	// to check for infinite loops, keep a set of states that have been traversed this evaluation
	Set<UUID> visitedStates;

	UUID state = m_currentStateId;
	UUID next = state;

	// keep looping until no more transitions have been made
	if (next != UUID())
	{
		do {
			// move to the next state
			state = next;

			// evaluate the state and get the next state
			next = get_state(next).evaluate(m_scope);

			if (!visitedStates.add(state))
			{
				MINTY_ERROR_F(ErrorCode::InfiniteLoop, state);
				return false;
			}
		} while (continuous && next != UUID());

		if (next != UUID())
		{
			state = next;
		}
	}

	// if nothing happened, return false
	if (state == m_currentStateId)
	{
		return false;
	}

	// set the current state to the new state
	m_currentStateId = state;

	// return true to indicate a state change
	return true;
}

void Minty::FSM::clear()
{
	m_scope.clear();
	m_states.clear();
	m_startingStateId = UUID();
	m_currentStateId = UUID();
}

void Minty::FSM::reset()
{
	// reset scope
	m_scope.reset();
	
	restart();
}

void Minty::FSM::restart()
{
	// set current state to starting state
	m_currentStateId = m_startingStateId;
}

void Minty::Serializer<FSM>::serialize(Writer &writer, FSM const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<FSM>::deserialize(Reader &reader, FSM &value)
{
	value.clear();

	// add this to push data
	reader.push_user_data(&value);

	// read scope
	reader.read("Scope", value.m_scope);

	// read states
	String name;
	if (reader.indent("States"))
	{
		// read the states
		while(reader.indent_next(name))
		{
			// not implemented: override existing states
			if(value.m_states.contains(name))
			{
				MINTY_NOT_IMPLEMENTED();
				continue;
			}

			// create the state
			value.m_states.add(name, UUID::create(), State());

			// read the state values
			State& state = value.m_states.at(name);
			Serializer<State>::deserialize(reader, state);

			reader.outdent();
		}

		reader.outdent();
	}

	// read starting state
	if (reader.read("Start", name))
	{
		MINTY_ASSERT_F(value.m_states.contains(name), ErrorCode::Serialization_InvalidData, name);
		value.m_startingStateId = value.m_states.get_key(name);
	}

	reader.pop_user_data();

	return true;
}