#pragma once
#include "Minty/Data/Lookup.h"
#include "Minty/Data/Scope.h"
#include "Minty/Data/UUID.h"
#include "Minty/FSM/State.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// A Finite State Machine (FSM) is a model of computation that can be in one of a finite number of states at any given time.
	/// </summary>
	class FSM
		: public SerializableObject
	{
#pragma region Variables

	private:
		BasicScope m_scope;
		Lookup<UUID, State> m_states;
		UUID m_currentStateId;
		UUID m_startingStateId;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty FSM.
		/// </summary>
		FSM()
			: m_scope()
			, m_states()
			, m_currentStateId(INVALID_ID)
			, m_startingStateId(INVALID_ID)
		{
		}

		~FSM()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Scope of this FSM.
		/// </summary>
		/// <returns>The Scope.</returns>
		BasicScope& get_scope()
		{
			return m_scope;
		}

		/// <summary>
		/// Gets the Scope of this FSM.
		/// </summary>
		/// <returns>The Scope.</returns>
		BasicScope const& get_scope() const
		{
			return m_scope;
		}

		/// <summary>
		/// Gets the State with the given ID.
		/// </summary>
		/// <param name="id">The ID.</param>
		/// <returns>The State.</returns>
		State& get_state(UUID const id)
		{
			MINTY_ASSERT(m_states.contains(id), F("No state found with ID {}.", id));
			return m_states.at(id);
		}

		/// <summary>
		/// Gets the State with the given ID.
		/// </summary>
		/// <param name="id">The ID.</param>
		/// <returns>The State.</returns>
		State const& get_state(UUID const id) const
		{
			MINTY_ASSERT(m_states.contains(id), F("No state found with ID {}.", id));
			return m_states.at(id);
		}

		/// <summary>
		/// Sets the current State using the given ID.
		/// </summary>
		/// <param name="id">The ID of the State.</param>
		void set_current_state(UUID const id)
		{
			MINTY_ASSERT(m_states.contains(id), F("No state found with ID {}.", id));
			m_currentStateId = id;
		}

		/// <summary>
		/// Gets the ID of the current State.
		/// </summary>
		/// <returns>The ID of the current State.</returns>
		UUID get_current_state_id() const
		{
			return m_currentStateId;
		}

		/// <summary>
		/// Gets the current State.
		/// </summary>
		/// <returns>The State.</returns>
		State& get_current_state()
		{
			MINTY_ASSERT(m_states.contains(m_currentStateId), F("No state found with ID {}.", m_currentStateId));
			return m_states.at(m_currentStateId);
		}

		/// <summary>
		/// Gets the current State.
		/// </summary>
		/// <returns>The State.</returns>
		State const& get_current_state() const
		{
			MINTY_ASSERT(m_states.contains(m_currentStateId), F("No state found with ID {}.", m_currentStateId));
			return m_states.at(m_currentStateId);
		}

		/// <summary>
		/// Checks if this FSM has a current State.
		/// </summary>
		/// <returns>True if there is a State selected currently, otherwise false.</returns>
		Bool has_current_state() const
		{
			return m_currentStateId.is_valid();
		}

		/// <summary>
		/// Sets the starting state using the given ID.
		/// </summary>
		/// <param name="id">The ID of the State.</param>
		void set_starting_state(UUID const id)
		{
			MINTY_ASSERT(m_states.contains(id), F("No state found with ID {}.", id));
			m_startingStateId = id;
		}

		/// <summary>
		/// Gets the ID of the starting state.
		/// </summary>
		/// <returns>The ID of the starting State.</returns>
		UUID get_starting_state_id() const
		{
			return m_startingStateId;
		}

		/// <summary>
		/// Gets the starting state.
		/// </summary>
		/// <returns>The State.</returns>
		State& get_starting_state()
		{
			MINTY_ASSERT(m_states.contains(m_startingStateId), F("No state found with ID {}.", m_startingStateId));
			return m_states.at(m_startingStateId);
		}

		/// <summary>
		/// Gets the starting state.
		/// </summary>
		/// <returns>The State.</returns>
		State const& get_starting_state() const
		{
			MINTY_ASSERT(m_states.contains(m_startingStateId), F("No state found with ID {}.", m_startingStateId));
			return m_states.at(m_startingStateId);
		}

		/// <summary>
		/// Checks if this FSM has a starting State.
		/// </summary>
		/// <returns>True if there is a starting State, otherwise false.</returns>
		Bool has_starting_state() const
		{
			return m_startingStateId.is_valid();
		}

		/// <summary>
		/// Sets the value of the variable with the given ID.
		/// </summary>
		/// <param name="id">The ID of the variable.</param>
		/// <param name="value">The value of the variable.</param>
		void set_variable(UUID const id, Int const value)
		{
			m_scope.set(id, value);
		}

		/// <summary>
		/// Gets the value of the variable with the given ID.
		/// </summary>
		/// <param name="id">The ID of the variable.</param>
		/// <returns>The value of the variable.</returns>
		Int get_variable(UUID const id) const
		{
			return m_scope.get_value(id);
		}

		/// <summary>
		/// Gets the name of the variable with the given ID.
		/// </summary>
		/// <param name="id">The ID of the variable.</param>
		/// <returns>The name of the variable.</returns>
		String const& get_variable_name(UUID const id) const
		{
			return m_scope.get_name(id);
		}

		/// <summary>
		/// Gets the name of the State with the given ID.
		/// </summary>
		/// <param name="id">The ID of the State.</param>
		/// <returns>The name of the State.</returns>
		String const& get_state_name(UUID const id) const
		{
			return m_states.get_string(id);
		}

#pragma endregion


#pragma region Methods

	public:
		/// <summary>
		/// Creates a new State with the given name and value.
		/// </summary>
		/// <param name="name">The name of the State.</param>
		/// <param name="value">The initial value of the State.</param>
		/// <returns>The ID of the new State.</returns>
		UUID create_state(String const& name, Variable const& value = Variable());

		/// <summary>
		/// Adds the given State to this FSM.
		/// </summary>
		/// <param name="name">The name of the State.</param>
		/// <param name="state">The State.</param>
		/// <returns>The ID of the State.</returns>
		UUID add_state(String const& name, State const& state);

		/// <summary>
		/// Creates a new variable with the given name and value.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="value">The initial value of the variable.</param>
		/// <returns>The ID of the new variable.</returns>
		UUID create_variable(String const& name, Int const value = 0);

		/// <summary>
		/// Gets the ID of the variable with the given name.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <returns>The ID of the variable.</returns>
		UUID find_variable(String const& name) const
		{
			return m_scope.find(name);
		}

		/// <summary>
		/// Evaluates this FSM.
		/// The current state will attempt to transition to another State based on its Transitions and values stored within this FSM's Scope.
		/// </summary>
		/// <returns>True if the FSM transitioned to a new State, otherwise false.</returns>
		Bool evaluate();

		/// <summary>
		/// Clears all States and variables from this FSM.
		/// </summary>
		void clear();

		/// <summary>
		/// Resets this FSM to its starting state.
		/// </summary>
		void reset();

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}