#ifndef MINTY_FSM_TRANSITION_H
#define MINTY_FSM_TRANSITION_H

/**
 * @file Transition.h
 * @brief Header file for FSM Transition class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/FSM/Condition.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief A Transition is a set of conditions that must be met in order for a State to transition to another State.
	 */
	class Transition
	{
		friend struct Serializer<Transition>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Transition.
		 */
		Transition();

		/**
		 * @brief Creates a Transition with the given state ID and conditions.
		 * @param stateId The ID of the State to transition to.
		 * @param conditions The conditions to check.
		 */
		Transition(UUID const stateId, Vector<Condition> const& conditions);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the ID of the State to transition to.
		 * @return The ID of the State to transition to.
		 */
		UUID get_state_id() const { return m_stateId; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Adds a condition to this Transition.
		 * @param condition The condition to add.
		 */
		void add_condition(Condition const& condition);

		/**
		 * @brief Evaluates this Transition given the Scope.
		 * @param scope The Scope to use.
		 * @return True if this Transition is valid, otherwise false.
		 */
		Bool evaluate(Scope const& scope) const;

#pragma endregion

#pragma region Variables

	private:
		UUID m_stateId;
		Vector<Condition> m_conditions;

#pragma endregion
	};

	template<>
    struct Serializer<Transition>
    {
		static void serialize(Writer& writer, Transition const& value);
		static Bool deserialize(Reader& reader, Transition& value);
    };
}

#endif // MINTY_FSM_TRANSITION_H