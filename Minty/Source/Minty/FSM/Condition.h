#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Scope.h"
#include "Minty/Data/UUID.h"
#include "Minty/FSM/Conditional.h"
#include "Minty/Serialization/Serializable.h"

namespace Minty
{
	/// <summary>
	/// A single condition that must be met in order for a transition to occur.
	/// </summary>
	class Condition
		: public Serializable
	{
#pragma region Variables

	private:
		UUID m_variableId;
		Conditional m_conditional;
		Int m_value;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Condition.
		/// </summary>
		Condition()
			: m_variableId(INVALID_ID)
			, m_conditional(Conditional::Equal)
			, m_value(0)
		{
		}

		/// <summary>
		/// Creates a Condition with the given variable ID, conditional, and value.
		/// </summary>
		/// <param name="variableId">The ID of the Variable to use.</param>
		/// <param name="conditional">The conditional.</param>
		/// <param name="value">The value to check against.</param>
		Condition(UUID const variableId, Conditional const conditional, Int const value)
			: m_variableId(variableId)
			, m_conditional(conditional)
			, m_value(value)
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Evaluates this Condition given the Scope.
		/// </summary>
		/// <param name="scope">The Scope to use.</param>
		/// <returns>True if this Condition is met, otherwise false.</returns>
		Bool evaluate(BasicScope const& scope) const;

		void serialize(Writer& writer, String const& name) const override;
		Bool deserialize(Reader& reader, Size const index) override;

#pragma endregion
	};
}