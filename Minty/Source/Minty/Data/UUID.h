#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Holds an ID value that can be used to identify an object.
	/// </summary>
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
		/// Create a UUID with the given ID.
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

		inline Bool operator==(UUID const other) const
		{
			return m_id == other.m_id;
		}

		inline Bool operator!=(UUID const other) const
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
		/// <summary>
		/// Gets the ID value of this UUID.
		/// </summary>
		/// <returns>The ID value.</returns>
		constexpr ID get_data() const
		{
			return m_id;
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if this UUID is valid.
		/// </summary>
		/// <returns>True if the ID value is not zero.</returns>
		constexpr Bool is_valid() const
		{
			return m_id != 0;
		}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new, random UUID using a uniform distribution.
		/// </summary>
		/// <returns>The UUID with a randomly generated ID value.</returns>
		static UUID create();

#pragma endregion
	};

	String to_string(UUID const obj);
	UUID parse_to_uuid(String const& string);
	Bool parse_try_uuid(String const& string, UUID& value);
	template<>
	inline UUID parse_to<UUID>(String const& string) { return parse_to_uuid(string); }
	template<>
	inline Bool parse_try<UUID>(String const& string, UUID& value) { return parse_try_uuid(string, value); }
}

namespace std
{
	template<>
	struct hash<Minty::UUID>
	{
		std::size_t operator()(Minty::UUID const& value) const
		{
			return std::hash<Minty::ID>{}(value.get_data());
		}
	};
}