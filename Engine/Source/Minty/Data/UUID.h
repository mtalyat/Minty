#ifndef MINTY_DATA_UUID_H
#define MINTY_DATA_UUID_H

/**
 * @file UUID.h
 * @brief Header file for the UUID class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"
#include "Minty/Data/StringView.h"

namespace Minty
{
	/**
	 * @class UUID
	 * @brief A Universally Unique Identifier (UUID) class.
	 */
	class UUID
	{
#pragma region Constructors

	public:
		/**
		 * @brief Create an empty UUID.
		 */
		UUID();

		/**
		 * @brief Create a UUID from a byte array.
		 * @param id The byte array representing the UUID.
		 */
		UUID(Byte const (&id)[UUID_BYTE_SIZE]);

		/**
		 * @brief Create a UUID from two 64-bit integers.
		 * @param id_high The high 64 bits.
		 * @param id_low The low 64 bits.
		 */
		UUID(UInt64 const id_high, UInt64 const id_low = 0);

		/**
		 * @brief Create a UUID from a string representation.
		 * @param string The string representation of the UUID.
		 */
		UUID(StringView const& string);

#pragma endregion

#pragma region Operators

	public:
		inline Bool operator==(UUID const other) const { return std::memcmp(m_data, other.m_data, UUID_BYTE_SIZE) == 0; }
		inline Bool operator!=(UUID const other) const { return !(*this == other); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the raw data of the UUID.
		 * @returns A pointer to the raw byte data of the UUID.
		 */
		inline Byte const* get_data() const noexcept { return m_data; }
		
		/**
		 * @brief Gets the raw data of the UUID.
		 * @returns A pointer to the raw byte data of the UUID.
		 */
		inline Bool is_valid() const { return *this != UUID(); }

#pragma endregion

#pragma region Methods

	public:
		
		/**
		 * @brief Creates a new UUID with a random value.
		 * @returns The newly created UUID.
		 */
		static UUID create();

		/**
		 * @brief Generates a new UUID with a random value.
		 * @note This is an alias for UUID::create().
		 * @returns The newly generated UUID.
		 */
		inline static UUID generate() { return create(); }

#pragma endregion

#pragma region Variables

	private:
		Byte m_data[UUID_BYTE_SIZE];

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
			Minty::Byte const* const data = value.get_data();
			std::size_t hash = 0;
			for (std::size_t i = 0; i < Minty::UUID_BYTE_SIZE; ++i)
			{
				hash ^= std::hash<Minty::Byte>()(data[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			}
			return hash;
		}
	};
}

#endif // MINTY_DATA_UUID_H