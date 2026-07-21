#ifndef MINTY_DATA_UUID_H
#define MINTY_DATA_UUID_H

/**
 * @file UUID.hpp
 * @brief Header file for the UUID class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Constant/Invalid.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @class UUID
	 * @brief A Universally Unique Identifier (UUID) class.
	 */
	class UUID
	{
		friend struct Parser<UUID>;

#pragma region Constants

	public:
		static constexpr Size BYTE_SIZE = 16;
		static constexpr Size BYTE_SIZE_HALF = BYTE_SIZE / 2;
		static constexpr Size HEX_SIZE_FULL = 32;
		static constexpr Size HEX_SIZE_HALF = HEX_SIZE_FULL / 2;

#pragma endregion

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
		UUID(Byte const (&id)[BYTE_SIZE]);

		/**
		 * @brief Create a UUID from two 64-bit integers.
		 * @param id_high The high 64 bits.
		 * @param id_low The low 64 bits.
		 */
		UUID(UInt64 const id_low, UInt64 const id_high = 0);

#pragma endregion

#pragma region Operators

	public:
		inline Bool operator==(UUID const other) const { return std::memcmp(m_data, other.m_data, BYTE_SIZE) == 0; }
		inline Bool operator!=(UUID const other) const { return !(*this == other); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the raw data of the UUID.
		 * @returns A pointer to the raw byte data of the UUID.
		 */
		inline Byte const *get_data() const noexcept { return m_data; }

		/**
		 * @brief Gets the raw data of the UUID.
		 * @returns A pointer to the raw byte data of the UUID.
		 */
		inline Bool is_valid() const { return *this != UUID(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Clears the UUID, setting it to an invalid state.
		 */
		void clear();

		/**
		 * @brief Creates a new UUID with a random value.
		 * @returns The newly created UUID.
		 */
		static UUID generate();

		/**
		 * @brief Creates a UUID from a string representation.
		 * @param str The string representation of the UUID.
		 * @returns The created UUID.
		 * @throws std::invalid_argument if the string is not a valid UUID format.
		 */
		static UUID from_string(StringView const str);

#pragma endregion

#pragma region Variables

	private:
		Byte m_data[BYTE_SIZE];

#pragma endregion
	};

    template<>
    struct Parser<UUID>
    {
        static Bool parse(StringView const str, UUID &value);
        static String to_string(UUID const &value);
    };
}

namespace std
{
	template <>
	struct hash<Minty::UUID>
	{
		std::size_t operator()(Minty::UUID const &value) const
		{
			Minty::Byte const *const data = value.get_data();
			std::size_t hash = 0;
			for (std::size_t i = 0; i < Minty::UUID::BYTE_SIZE; ++i)
			{
				hash ^= std::hash<Minty::Byte>()(data[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			}
			return hash;
		}
	};
}

#endif // MINTY_DATA_UUID_H