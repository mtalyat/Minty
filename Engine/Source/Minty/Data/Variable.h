#ifndef MINTY_DATA_VARIABLE_H
#define MINTY_DATA_VARIABLE_H

/**
 * @file Variable.h
 * @brief Defines the Variable class for typed data storage.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @class Variable
	 * @brief A typed data storage class.
	 */
	class Variable
	{
		friend struct ItemSerializer<Variable>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Variable.
		 */
		Variable();

		/**
		 * @brief Creates a Variable with the given Type.
		 * @param type The Type of Variable.
		 */
		Variable(Type const type);

		/**
		 * @brief Creates a Variable with the given Type and data.
		 * @param type The Type of Variable.
		 */
		Variable(Type const type, AnyConst const data);

		/**
		 * @brief Creates a Variable with the given value.
		 * @tparam T The type of the value.
		 * @param value The value to store.
		 */
		template<typename T>
		Variable(T const& value)
			: m_type(type_typeid(typeid(T)))
			, m_data(&value, sizeof_type(m_type))
		{
		}

		~Variable() = default;

#pragma endregion

#pragma region Operators

	public:
		template<typename T>
		operator T() const
		{
			T* value = try_get<T>();
			MINTY_ASSERT(value != nullptr, ErrorCode::Object_InvalidState);
			return *value;
		}

		template<typename T>
		Variable& operator=(T const& value)
		{
			if (typeid(T) == typeid(nullptr))
			{
				clear();
			}
			else
			{
				set(value);
			}
			return *this;
		}

		Bool operator==(Variable const& other) const;
		inline Bool operator!=(Variable const& other) const { return !(*this == other); }

		template<typename T>
		Bool operator==(T const& value) const
		{
			T* data = try_get<T>();
			if (data == nullptr)
			{
				return typeid(T) == typeid(nullptr);
			}

			return *data == value;
		}

		template<typename T>
		inline Bool operator!=(T const& value) const { return !(*this == value); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Type of this Variable.
		 * @returns The Type.
		 */
		Type get_type() const { return m_type; }

		/**
		 * @brief Sets the Type of this Variable.
		 * @param type The new Type.
		 */
		void set_type(Type const type);

		/**
		 * @brief Gets the data of this Variable.
		 * @returns The data.
		 */
		DynamicContainer const& get_data() const { return m_data; }

		/**
		 * @brief Sets the Type and data of this Variable.
		 * @param type The new Type.
		 * @param data The new data.
		 */
		void set_data(Type const type, AnyConst const data)
		{
			set_type(type);
			set_data(data);
		}

		/**
		 * @brief Sets the data of this Variable.
		 * @param data The new data.
		 */
		void set_data(AnyConst const data);

		/**
		 * @brief Tries to get the data of this Variable.
		 * @tparam T The type associated with this Variable.
		 * @returns A pointer to the value, or nullptr if the type does not match or the Variable is empty.
		 */
		template<typename T>
		T* try_get() const
		{
			if (m_type == Type::Undefined || m_type != type_typeid(typeid(T)) || is_empty())
			{
				return nullptr;
			}

			return static_cast<T*>(m_data.get_data());
		}

		/**
		 * @brief Gets the data of this Variable.
		 * @tparam T The type associated with this Variable.
		 */
		template<typename T>
		T& get() const
		{
			MINTY_ASSERT(m_type != Type::Undefined, ErrorCode::Object_InvalidState);
			MINTY_ASSERT(m_type == type_typeid(typeid(T)), ErrorCode::Argument_InvalidType);
			MINTY_ASSERT(!is_empty(), ErrorCode::Object_EmptyContainer);

			return *static_cast<T*>(m_data.get_data());
		}

		/**
		 * @brief Sets the value of this Variable.
		 * @tparam T The type of the value.
		 * @param value The value to set.
		 */
		template<typename T>
		void set(T const& value)
		{
			Type newType = type_typeid(typeid(T));
			MINTY_ASSERT_F(newType < Type::Object, ErrorCode::Argument_InvalidType, newType);

			if (newType != m_type)
			{
				m_type = newType;
				if (newType == Type::Undefined)
				{
					clear();
					return;
				}
			}

			m_data.set(&value, sizeof_type(m_type));
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if this Variable is empty (has no data).
		 * @returns True if empty.
		 */
		inline Bool is_empty() const { return m_data.get_size() == 0; }

		/**
		 * @brief Clears the data of this Variable.
		 */
		inline void clear() { m_data.clear(); }

#pragma endregion

#pragma region Variables

	private:
		Type m_type;
		DynamicContainer m_data;

#pragma endregion
	};

	template<>
    struct ItemSerializer<Variable>
    {
		static void serialize_item(Writer& writer, StringView const name, Variable const& value);
		static void deserialize_item(Reader& reader, StringView const name, Variable& value);
    };
}

#endif // MINTY_DATA_VARIABLE_H