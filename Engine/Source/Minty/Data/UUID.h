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

namespace Minty
{
	constexpr Size UUID_SIZE = 16;

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
		constexpr UUID()
			: m_id(0)
		{
		}

		constexpr UUID(Byte const (&id)[UUID_SIZE])
		{
			for (Size i = 0; i < UUID_SIZE; ++i)
			{
				m_id[i] = id[i];
			}
		}

#pragma endregion

#pragma region Operators

	public:
		inline Bool operator==(UUID const other) const
		{
			return std::memcmp(m_id, other.m_id, UUID_SIZE) == 0;
		}

		inline Bool operator!=(UUID const other) const
		{
			return std::memcmp(m_id, other.m_id, UUID_SIZE) != 0;
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Gets the raw data of the UUID.
		 * @returns A pointer to the raw byte data of the UUID.
		 */
		constexpr Bool is_valid() const
		{
			for (Size i = 0; i < UUID_SIZE; ++i)
			{
				if (m_id[i] != 0)
				{
					return true;
				}
			}
			return false;
		}

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Creates a new UUID.
		 * @returns The newly created UUID.
		 */
		static UUID create();

#pragma endregion

#pragma region Variables

	private:
		Byte m_id[UUID_SIZE];

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
			const Byte* data = reinterpret_cast<const Byte*>(&value);
			std::size_t hash = 0;
			for (Size i = 0; i < Minty::UUID_SIZE; ++i)
			{
				hash ^= std::hash<Byte>()(data[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
			}
			return hash;
		}
	};
}

#endif // MINTY_DATA_UUID_H