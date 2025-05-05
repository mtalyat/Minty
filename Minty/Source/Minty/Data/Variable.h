#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Serialization/Serializable.h"

namespace Minty
{
	/// <summary>
	/// A Container with a Type.
	/// </summary>
	class Variable
		: public Serializable
	{
#pragma region Variables

	private:
		Type m_type;
		DynamicContainer m_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Variable.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		Variable(Allocator const allocator = Allocator::Default)
			: m_type(Type::Undefined)
			, m_data(allocator)
		{
		}

		/// <summary>
		/// Creates an empty Variable with the given Type.
		/// </summary>
		/// <param name="type">The Type of variable.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Variable(Type const type, Allocator const allocator = Allocator::Default)
			: m_type(type)
			, m_data(allocator)
		{
		}

		/// <summary>
		/// Creates a Variable with the given data.
		/// </summary>
		/// <param name="type">The Type of Variable.</param>
		/// <param name="data">The data to set in bytes.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Variable(Type const type, void const* const data, Allocator const allocator = Allocator::Default)
			: m_type(type)
			, m_data(data, sizeof_type(type), allocator)
		{
		}

		/// <summary>
		/// Creates a Variable with the given value.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <param name="value">The value.</param>
		/// <param name="allocator">The Allocator to use.</param>
		template<typename T>
		Variable(T const& value, Allocator const allocator = Allocator::Default)
			: m_type(type_typeid(typeid(T)))
			, m_data(&value, sizeof_type(m_type), allocator)
		{
		}

		~Variable()
		{
		}

#pragma endregion

#pragma region Operators

	public:
		template<typename T>
		operator T() const
		{
			T* value = try_get<T>();
			MINTY_ASSERT(value, "Variable is empty.");
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

		Bool operator!=(Variable const& other) const { return !(*this == other); }

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
		Bool operator!=(T const& value) const
		{
			T* data = try_get<T>();
			if (data == nullptr)
			{
				return typeid(T) != typeid(nullptr);
			}

			return *data != value;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Type of this Variable.
		/// </summary>
		/// <returns>The Type.</returns>
		Type get_type() const { return m_type; }

		/// <summary>
		/// Sets the Type of this Variable.
		/// </summary>
		/// <param name="type">The Type.</param>
		void set_type(Type const type);

		/// <summary>
		/// Gets the data of this Variable.
		/// </summary>
		/// <returns>The DynamicContainer with the data.</returns>
		DynamicContainer const& get_data() const { return m_data; }

		/// <summary>
		/// Sets the data of this Variable.
		/// </summary>
		/// <param name="type">The new Type for this Variable.</param>
		/// <param name="data">The data of this Variable.</param>
		void set_data(Type const type, void const* const data)
		{
			set_type(type);
			set_data(data);
		}

		/// <summary>
		/// Sets the data of this Variable.
		/// </summary>
		/// <param name="data">The data of this Variable.</param>
		void set_data(void const* const data);

		/// <summary>
		/// Get the data of this Variable.
		/// </summary>
		/// <typeparam name="T">The type associated with this Variable.</typeparam>
		/// <returns>The value.</returns>
		template<typename T>
		T* try_get() const
		{
			if (m_type == Type::Undefined || m_type != type_typeid(typeid(T)) || is_empty())
			{
				return nullptr;
			}

			return static_cast<T*>(m_data.get_data());
		}

		/// <summary>
		/// Get the data of this Variable.
		/// </summary>
		/// <typeparam name="T">The type associated with this Variable.</typeparam>
		/// <returns>The value.</returns>
		template<typename T>
		T& get() const
		{
			MINTY_ASSERT(m_type != Type::Undefined, "Variable is undefined.");
			MINTY_ASSERT(m_type == type_typeid(typeid(T)), "Variable type does not match requested type.");
			MINTY_ASSERT(!is_empty(), "Variable is empty.");

			return *static_cast<T*>(m_data.get_data());
		}

		/// <summary>
		/// Sets the data of this Variable.
		/// </summary>
		/// <typeparam name="T">The type associated with this Variable.</typeparam>
		/// <param name="value">The value.</param>
		template<typename T>
		void set(T const& value)
		{
			Type newType = type_typeid(typeid(T));

			MINTY_ASSERT(newType < Type::Object, "Cannot set Variable type to an object.");

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
		/// <summary>
		/// Checks if this Variable is empty.
		/// </summary>
		/// <returns>True if there is no data set.</returns>
		Bool is_empty() const { return m_data.get_size() == 0; }

		/// <summary>
		/// Clears the data from this Variable.
		/// </summary>
		void clear()
		{
			m_data.clear();
		}

		void serialize(Writer& writer, String const& name) const override;
		Bool deserialize(Reader& reader, Size const index) override;

#pragma endregion
	};
}