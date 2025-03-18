#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Serialization/Serializable.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

namespace Minty
{
	class UUID
		: public Serializable
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

		/// <summary>
		/// Write this object's data to the writer.
		/// </summary>
		/// <param name="writer">The Writer to write to.</param>
		/// <param name="name">The name of this object.</param>
		void serialize(Writer& writer, String const& name) const override;

		/// <summary>
		/// Read this object's data from the reader.
		/// </summary>
		/// <param name="reader">The Reader to read from.</param>
		/// <param name="index">The index of this object.</param>
		/// <returns>True on success.</returns>
		Bool deserialize(Reader& reader, Int const index) override;

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

	String to_string(UUID const value);
}