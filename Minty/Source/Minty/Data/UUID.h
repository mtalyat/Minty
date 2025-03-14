#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	class UUID
	{
#pragma region Variables

	private:
		ID m_id;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Create an empty UUID.
		/// </summary>
		constexpr UUID()
			: m_id(0)
		{
		}

		/// <summary>
		/// Create an UUID with the given ID.
		/// </summary>
		/// <param name="id">The ID value to use.</param>
		constexpr UUID(ID const id)
			: m_id(id)
		{
		}		

#pragma endregion

#pragma region Operators

	public:
		operator ID() const { return m_id; }

		constexpr Bool operator==(UUID const other) const
		{
			return m_id == other.m_id;
		}

		constexpr Bool operator!=(UUID const other) const
		{
			return m_id != other.m_id;
		}

		constexpr Bool operator==(ID const other) const
		{
			return m_id == other;
		}

		constexpr Bool operator!=(ID const other) const
		{
			return m_id != other;
		}

#pragma endregion


#pragma region Get Set

	public:
		constexpr ID get_data() const
		{
			return m_id;
		}

#pragma endregion

#pragma region Methods

	public:
		constexpr Bool is_valid() const
		{
			return m_id != 0;
		}

#pragma endregion

#pragma region Statics

	public:
		static UUID create();

#pragma endregion
	};
}