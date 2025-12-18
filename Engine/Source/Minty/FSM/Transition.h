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
#include "Minty/Serialization/Serializable.h"

namespace Minty
{
	/**
	 * @brief A Transition is a set of conditions that must be met in order for a State to transition to another State.
	 */
	class Transition
		: public Serializable
	{
#pragma region Variables

	private:
		UUID m_stateId;
		Vector<Condition> m_conditions;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Transition.
		 */
		Transition()
			: m_stateId(UUID())
			, m_conditions()
		{
		}

		/**
		 * @brief Creates a Transition with the given state ID and conditions.
		 * @param stateId The ID of the State to transition to.
		 * @param conditions The conditions to check.
		 */
		Transition(UUID const stateId, Vector<Condition> const& conditions)
			: m_stateId(stateId)
			, m_conditions(conditions)
		{
		}

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

		void serialize(Writer& writer, String const& name) const override;
		Bool deserialize(Reader& reader, Size const index) override;

#pragma endregion
	};
}

#endif // MINTY_FSM_TRANSITION_H