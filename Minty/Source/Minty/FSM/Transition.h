#pragma once
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/FSM/Condition.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// A Transition is a set of conditions that must be met in order for a State to transition to another State.
	/// </summary>
	class Transition
		: public SerializableObject
	{
#pragma region Variables

	private:
		UUID m_stateId;
		Vector<Condition> m_conditions;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Transition.
		/// </summary>
		Transition()
			: m_stateId(INVALID_ID)
			, m_conditions()
		{
		}

		/// <summary>
		/// Creates a Transition with the given state ID and conditions.
		/// </summary>
		/// <param name="stateId">The ID of the State to transition to.</param>
		/// <param name="conditions">The conditions to check.</param>
		Transition(UUID const stateId, Vector<Condition> const& conditions)
			: m_stateId(stateId)
			, m_conditions(conditions)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the ID of the State to transition to.
		/// </summary>
		UUID get_state_id() const { return m_stateId; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Adds a condition to this Transition.
		/// </summary>
		/// <param name="condition">The condition to add.</param>
		void add_condition(Condition const& condition);

		/// <summary>
		/// Evaluates this Transition given the Scope.
		/// </summary>
		/// <param name="scope">The Scope to use.</param>
		/// <returns>True if this Transition is valid, otherwise false.</returns>
		Bool evaluate(BasicScope const& scope) const;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}