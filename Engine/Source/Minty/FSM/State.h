#ifndef MINTY_FSM_STATE_H
#define MINTY_FSM_STATE_H

/**
 * @file State.h
 * @brief Header file for FSM State class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/UUID.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"
#include "Minty/FSM/Transition.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/**
	 * @brief A State is a single state in a Finite State Machine (FSM).
	 * Each state holds a single Variable value.
	 */
	class State
		: public SerializableObject
	{	
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty State.
		 */
		State()
			: m_value()
			, m_transitions()
		{
		}

		/**
		 * @brief Creates a State with the given Variable value.
		 * @param value The initial value.
		 */
		State(Variable const& value)
			: m_value(value)
			, m_transitions()
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the value this State holds.
		 * @return The Variable value.
		 */
		Variable& get_value() { return m_value; }

		/**
		 * @brief Gets the value this State holds.
		 * @return The Variable value.
		 */
		Variable const& get_value() const { return m_value; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Adds a Transition to this State.
		 * @param transition The Transition.
		 */
		void add_transition(Transition const& transition);

		/**
		 * @brief Evaluates this State given the Scope. 
		 * If the conditions are met to transition to a new state, that State's ID is returned.
		 * Otherwise, UUID() is returned.
		 * @param scope The Scope to use.
		 * @return The UUID of the new State, or UUID() if no new State.
		 */
		UUID evaluate(Scope const& scope) const;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Variables

	private:
		Variable m_value;
		Vector<Transition> m_transitions;

#pragma endregion
	};
}

#endif // MINTY_FSM_STATE_H