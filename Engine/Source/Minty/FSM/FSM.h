#ifndef MINTY_FSM_FSM_H
#define MINTY_FSM_FSM_H

/**
 * @file FSM.h
 * @brief Header file for Finite State Machine (FSM) class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Lookup.h"
#include "Minty/Data/Scope.h"
#include "Minty/Data/UUID.h"
#include "Minty/FSM/State.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief A Finite State Machine (FSM) is a model of computation that can be in one of a finite number of states at any given time.
	 */
	class FSM
	{
		friend struct Serializer<FSM>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty FSM.
		 */
		FSM()
			: m_scope()
			, m_states()
			, m_currentStateId(UUID())
			, m_startingStateId(UUID())
		{
		}

		~FSM()
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Scope of this FSM.
		 * @return The Scope.
		 */
		Scope& get_scope()
		{
			return m_scope;
		}

		/**
		 * @brief Gets the Scope of this FSM.
		 * @return The Scope.
		 */
		Scope const& get_scope() const
		{
			return m_scope;
		}

		/**
		 * @brief Gets the State with the given ID.
		 * @param id The ID.
		 * @return The State.
		 */
		State& get_state(UUID const id)
		{
			MINTY_ASSERT_F(m_states.contains(id), ErrorCode::Argument_KeyNotFound, id);
			return m_states.at(id);
		}

		/**
		 * @brief Gets the State with the given ID.
		 * @param id The ID.
		 * @return The State.
		 */
		State const& get_state(UUID const id) const
		{
			MINTY_ASSERT_F(m_states.contains(id), ErrorCode::Argument_KeyNotFound, id);
			return m_states.at(id);
		}

		/**
		 * @brief Sets the current State using the given ID.
		 * @param id The ID of the State.
		 */
		void set_current_state(UUID const id)
		{
			MINTY_ASSERT_F(m_states.contains(id), ErrorCode::Argument_KeyNotFound, id);
			m_currentStateId = id;
		}

		/**
		 * @brief Gets the ID of the current State.
		 * @return The ID of the current State.
		 */
		UUID get_current_state_id() const
		{
			return m_currentStateId;
		}

		/**
		 * @brief Gets the current State.
		 * @return The State.
		 */
		State& get_current_state()
		{
			MINTY_ASSERT_F(m_states.contains(m_currentStateId), ErrorCode::Object_InvalidState, m_currentStateId);
			return m_states.at(m_currentStateId);
		}

		/**
		 * @brief Gets the current State.
		 * @return The State.
		 */
		State const& get_current_state() const
		{
			MINTY_ASSERT_F(m_states.contains(m_currentStateId), ErrorCode::Object_InvalidState, m_currentStateId);
			return m_states.at(m_currentStateId);
		}

		/**
		 * @brief Checks if this FSM has a current State.
		 * @return True if there is a State selected currently, otherwise false.
		 */
		Bool has_current_state() const
		{
			return m_currentStateId.is_valid();
		}

		/**
		 * @brief Sets the starting state using the given ID.
		 * @param id The ID of the State.
		 */
		void set_starting_state(UUID const id)
		{
			MINTY_ASSERT_F(m_states.contains(id), ErrorCode::Argument_KeyNotFound, id);
			m_startingStateId = id;
		}

		/**
		 * @brief Gets the ID of the starting state.
		 * @return The ID of the starting State.
		 */
		UUID get_starting_state_id() const
		{
			return m_startingStateId;
		}

		/**
		 * @brief Gets the starting state.
		 * @return The State.
		 */
		State& get_starting_state()
		{
			MINTY_ASSERT_F(m_states.contains(m_startingStateId), ErrorCode::Object_InvalidState, m_startingStateId);
			return m_states.at(m_startingStateId);
		}

		/**
		 * @brief Gets the starting state.
		 * @return The State.
		 */
		State const& get_starting_state() const
		{
			MINTY_ASSERT_F(m_states.contains(m_startingStateId), ErrorCode::Object_InvalidState, m_startingStateId);
			return m_states.at(m_startingStateId);
		}

		/**
		 * @brief Checks if this FSM has a starting State.
		 * @return True if there is a starting State, otherwise false.
		 */
		Bool has_starting_state() const
		{
			return m_startingStateId.is_valid();
		}

		/**
		 * @brief Sets the value of the variable with the given ID.
		 * @param id The ID of the variable.
		 * @param value The value of the variable.
		 */
		void set_variable(UUID const id, Int const value)
		{
			m_scope.set(id, value);
		}

		/**
		 * @brief Gets the value of the variable with the given ID.
		 * @param id The ID of the variable.
		 * @return The value of the variable.
		 */
		Int get_variable(UUID const id) const
		{
			return m_scope.get_value(id);
		}

		/**
		 * @brief Gets the name of the variable with the given ID.
		 * @param id The ID of the variable.
		 * @return The name of the variable.
		 */
		String const& get_variable_name(UUID const id) const
		{
			return m_scope.get_name(id);
		}

		/**
		 * @brief Gets the name of the State with the given ID.
		 * @param id The ID of the State.
		 * @return The name of the State.
		 */
		String const& get_state_name(UUID const id) const
		{
			return m_states.get_string(id);
		}

		/**
		 * @brief Gets the States of this FSM.
		 * @return The Lookup containing all of the States.
		 */
		Lookup<UUID, State> const& get_states() const
		{
			return m_states;
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Creates a new State with the given name and value.
		 * @param name The name of the State.
		 * @param value The initial value of the State.
		 * @return The ID of the new State.
		 */
		UUID create_state(String const& name, Variable const& value = Variable());

		/**
		 * @brief Adds the given State to this FSM.
		 * @param name The name of the State.
		 * @param state The State.
		 * @return The ID of the State.
		 */
		UUID add_state(String const& name, State const& state);

		/**
		 * @brief Finds the ID of the State with the given name.
		 * @param name The name of the State.
		 * @return The ID of the State, or UUID() if none found.
		 */
		UUID find_state(String const& name) const
		{
			auto found = m_states.find(name);
			if (found == m_states.end())
			{
				return UUID();
			}
			return found->get_second();
		}

		/**
		 * @brief Creates a new variable with the given name and value.
		 * @param name The name of the variable.
		 * @param value The initial value of the variable.
		 * @return The ID of the new variable.
		 */
		UUID create_variable(String const& name, Int const value = 0);

		/**
		 * @brief Gets the ID of the variable with the given name.
		 * @param name The name of the variable.
		 * @return The ID of the variable.
		 */
		UUID find_variable(String const& name) const
		{
			return m_scope.find(name);
		}

		/**
		 * @brief Evaluates this FSM.
		 * The current state will attempt to transition to another State based on its Transitions and values stored within this FSM's Scope.
		 * @param continuous Whether to continue evaluating until no more transitions are possible.
		 * @return True if the FSM transitioned to a new State, otherwise false.
		 */
		Bool evaluate(Bool const continuous = false);

		/**
		 * @brief Clears all States and variables from this FSM.
		 */
		void clear();

		/**
		 * @brief Resets this FSM to its starting state. Clears all variable values to zero.
		 */
		void reset();

		/** 
		 * @brief Restarts this FSM to its starting state. Does not clear variable values.
		 */
		void restart();

#pragma endregion

#pragma region Variables

	private:
		Scope m_scope;
		Lookup<UUID, State> m_states;
		UUID m_currentStateId;
		UUID m_startingStateId;

#pragma endregion
	};

	template<>
	struct Serializer<FSM>
	{
		static void serialize(Writer& writer, FSM const& value);
		static Bool deserialize(Reader& reader, FSM& value);
	};
}

#endif // MINTY_FSM_FSM_H