#pragma once
#include "Minty/Data/UUID.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"
#include "Minty/FSM/Transition.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// A State is a single state in a Finite State Machine (FSM).
	/// Each state holds a single Variable value.
	/// </summary>
	class State
		: public SerializableObject
	{
#pragma region Variables

	private:
		Variable m_value;
		Vector<Transition> m_transitions;

#pragma endregion
	
#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty State.
		/// </summary>
		State()
			: m_value()
			, m_transitions()
		{
		}

		/// <summary>
		/// Creates a State with the given Variable value.
		/// </summary>
		/// <param name="value">The initial value.</param>
		State(Variable const& value)
			: m_value(value)
			, m_transitions()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the value this State holds.
		/// </summary>
		/// <returns>The Variable value.</returns>
		Variable& get_value() { return m_value; }

		/// <summary>
		/// Gets the value this State holds.
		/// </summary>
		/// <returns>The Variable value.</returns>
		Variable const& get_value() const { return m_value; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Adds a Transition to this State.
		/// </summary>
		/// <param name="transition">The Transition.</param>
		void add_transition(Transition const& transition);

		/// <summary>
		/// Evaluates this State given the Scope. 
		/// If the conditions are met to transition to a new state, that State's ID is returned.
		/// Otherwise, INVALID_ID is returned.
		/// </summary>
		/// <param name="scope">The Scope to use.</param>
		/// <returns>The UUID of the new State, or INVALID_ID if no new State.</returns>
		UUID evaluate(BasicScope const& scope) const;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}