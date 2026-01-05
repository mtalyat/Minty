#ifndef MINTY_FSM_CONDITION_H
#define MINTY_FSM_CONDITION_H

/**
 * @file Condition.h
 * @brief Header file for FSM Condition class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Scope.h"
#include "Minty/Data/UUID.h"
#include "Minty/FSM/Conditional.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief A single condition that must be met in order for a transition to occur.
	 */
	class Condition
	{
		friend struct ItemSerializer<Condition>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Condition.
		 */
		Condition()
			: m_variableId(UUID())
			, m_conditional(Conditional::Equal)
			, m_value(0)
		{
		}

		/**
		 * @brief Creates a Condition with the given variable ID, conditional, and value.
		 * @param variableId The ID of the Variable to use.
		 * @param conditional The conditional.
		 * @param value The value to check against.
		 */
		Condition(UUID const variableId, Conditional const conditional, Int const value)
			: m_variableId(variableId)
			, m_conditional(conditional)
			, m_value(value)
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Evaluates this Condition given the Scope.
		 * @param scope The Scope to use.
		 * @return True if this Condition is met, otherwise false.
		 */
		Bool evaluate(Scope const& scope) const;

#pragma endregion

#pragma region Variables

	private:
		UUID m_variableId;
		Conditional m_conditional;
		Int m_value;

#pragma endregion
	};

	template<>
	struct ItemSerializer<Condition>
	{
		static void serialize_item(Writer& writer, StringView const name, Condition const& value);
        static void deserialize_item(Reader& reader, StringView const name, Condition& value);
	};
}

#endif // MINTY_FSM_CONDITION_H