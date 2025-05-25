#include "pch.h"
#include "FSM.h"
#include "Minty/Data/Set.h"

using namespace Minty;

UUID Minty::FSM::create_state(String const& name, Variable const& value)
{
	return add_state(name, State(value));
}

UUID Minty::FSM::add_state(String const& name, State const& state)
{
	MINTY_ASSERT(!name.is_empty(), F("State name cannot be empty."));

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
	MINTY_ASSERT(!name.is_empty(), F("Variable name cannot be empty."));
	return m_scope.add(name, value);
}

Bool Minty::FSM::evaluate()
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
	while (next != INVALID_ID)
	{
		// move to the next state
		state = next;

		// evaluate the state and get the next state
		next = get_state(next).evaluate(m_scope);

		if (!visitedStates.add(state))
		{
			MINTY_ERROR(F("Infinite loop detected in FSM: {}", state));
			return false;
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
	m_startingStateId = INVALID_ID;
	m_currentStateId = INVALID_ID;
}

void Minty::FSM::reset()
{
	// reset scope
	m_scope.reset();

	// set current state to starting state
	m_currentStateId = m_startingStateId;
}

void Minty::FSM::serialize(Writer& writer) const
{
	// add this to push data
	writer.push_user_data(this);

	writer.write("Scope", m_scope);
	if (m_startingStateId.is_valid())
	{
		// get the name of the starting state
		String name = m_states.get_string(m_startingStateId);
		writer.write("Start", name);
	}
	
	// write all states
	writer.indent("States");
	for (auto const& [string, key, value] : m_states)
	{
		writer.write(string, value);
	}
	writer.outdent();

	// remove this from push data
	writer.pop_user_data();
}

Bool Minty::FSM::deserialize(Reader& reader)
{
	clear();

	// add this to push data
	reader.push_user_data(this);

	// read scope
	reader.read("Scope", m_scope);

	// read states
	String name;
	if (reader.indent("States"))
	{
		// read the names
		for (Size i = 0; i < reader.get_size(); i++)
		{
			if (!reader.read_name(i, name))
			{
				MINTY_ERROR(F("Failed to read state name at index {}.", i));
				return false;
			}
			m_states.add(name, UUID::create(), State());
		}

		// read the states
		State state;
		for (Size i = 0; i < reader.get_size(); i++)
		{
			if (!reader.read_name(i, name))
			{
				MINTY_ERROR(F("Failed to read state name at index {}.", i));
				return false;
			}

			// get the state
			// no need to check if not found, just added the state above
			State& state = m_states.at(name);

			// read the state values
			if (!reader.read(i, state))
			{
				MINTY_ERROR(F("Failed to read state {}.", name));
				return false;
			}
		}

		reader.outdent();
	}

	// read starting state
	if (reader.read("Start", name))
	{
		MINTY_ASSERT(m_states.contains(name), F("Starting state {} not found.", name));
		m_startingStateId = m_states.get_key(name);
	}

	reader.pop_user_data();

	return true;
}
