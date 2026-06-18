#pragma once

/**
 * @file Writer.h
 * @brief Header file defining the Writer class for serialization.
 * @author Mitchell Talyat
 */

#include "Parser.h"
#include "Serializer.h"
#include "Platform/Type/Primitive.h"
#include "Core/Meta/Type.h"
#include "Core/Data/Stack.h"
#include "Core/Data/StringView.h"
#include "Core/Data/Shared.h"
#include "Core/Stream/Stream.h"
#include "Core/Constant/Limit.h"

namespace Minty
{
	/**
	 * @brief A Writer writes data to a stream.
	 */
	class Writer
	{
#pragma region Types

	protected:
		/**
		 * @brief The state of the Writer.
		 */
		enum class StateEnum
		{
			/**
			* @brief The last write was completed.
			*/
			None,

			/**
			 * @brief Unknown state.
			 */
			Unknown,

			/**
			 * @brief The last write was a key.
			 */
			Key,
			
			/**
			 * @brief The last write was an empty key.
			 */
			Empty,
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a Writer with the given stream.
		 * @param stream The stream to write to.
		 */
		Writer(Shared<Stream> const& stream);

		virtual ~Writer() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Pushes user data onto the user data stack.
		 * @param userData Pointer to the user data.
		 */
		inline void push_user_data(PointerConst const userData) { m_userStack.push(userData); }

		/**
		 * @brief Pops user data from the user data stack.
		 */
		inline void pop_user_data() { m_userStack.pop(); }

		/**
		 * @brief Gets the user data associated with the Writer.
		 * @return Pointer to the user data.
		 */
		inline PointerConst get_user_data() const { return m_userStack.peek(); }

	protected:
		inline StateEnum get_state() const { return m_state; }

		inline void set_state(StateEnum const state) { m_state = state; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Writes a value associated with the given key.
		 * @tparam T The type of the value to write.
		 * @param key The key associated with the value.
		 * @param value The value to write.
		 * @returns True if the value was written successfully, false otherwise.
		 */
		template<typename T>
		void write(StringView const key, T const& value)
		{
			write_key(key);
			set_state(key.is_empty() ? StateEnum::Empty : StateEnum::Key);
			write_kvp_separator();
			specialized_write<T>(value);
		}

		/**
		 * @brief Writes a type-value pair associated with the given key.
		 * @param key The key associated with the value.
		 * @param type The type of the value.
		 * @param value Pointer to the value to write.
		 */
		void write(StringView const key, TypeEnum const type, PointerConst const value)
		{
			write_key(key);
			set_state(key.is_empty() ? StateEnum::Empty : StateEnum::Key);
			write_kvp_separator();
			write_type_value_pair(type, value);
		}

		/**
		 * @brief Writes an optional value associated with the given key.
		 * @tparam T The type of the value to write.
		 * @param key The key associated with the value.
		 * @param value The value to write.
		 * @param defaultValue The default value to compare against.
		 */
		template<typename T>
		void write_optional(StringView const key, T const& value, T const& defaultValue)
		{
			if (value != defaultValue)
			{
				write<T>(key, value);
			}
		}

		/**
		 * @brief Writes an optional type-value pair associated with the given key.
		 * @param key The key associated with the value.
		 * @param type The type of the value.
		 * @param value Pointer to the value to write.
		 * @param defaultType The default type to compare against.
		 * @param defaultValue Pointer to the default value to compare against.
		 */
		void write_optional(StringView const key, Type const type, PointerConst const value, Type const defaultType, PointerConst const defaultValue)
		{
			if (type != defaultType)
			{
				write(key, type, value);
				return;
			}

			Size const typeSize = type.get_size();
			if (std::memcmp(value, defaultValue, typeSize) != 0)
			{
				write(key, type, value);
			}
		}

		/**
		 * @brief Writes an inline value (no key).
		 * @tparam T The type of the value to write.
		 * @param value The value to write.
		 */
		template<typename T>
		void write_inline(T const& value)
		{
			if(static_cast<Size>(get_state()) < static_cast<Size>(StateEnum::Key))
			{
				// must have written a key before writing an inline value
				MINTY_ERROR(ErrorCodeEnum::Serialization_Write);
				return;
			}
			specialized_write<T>(value);
		}

		/**
		 * @brief Writes an inline type-value pair (no key).
		 * @param type The type of the value.
		 * @param data Pointer to the value to write.
		 */
		void write_inline(TypeEnum const type, PointerConst const data)
		{
			if(static_cast<Size>(get_state()) < static_cast<Size>(StateEnum::Key))
			{
				// must have written a key before writing an inline value
				MINTY_ERROR(ErrorCodeEnum::Serialization_Write);
				return;
			}
			write_type_value_pair(type, data);
		}

		/**
		 * @brief Writes a key and increases the indentation level for writing nested structures.
		 * @param key The key to write.
		 */
		void indent(StringView const key)
		{
			write_key(key);
			set_state(key.is_empty() ? StateEnum::Empty : StateEnum::Key);
			increase_indentation();
		}

		/**
		 * @brief Writes a key-value pair and increases the indentation level for writing nested structures.
		 * @tparam T The type of the value to write.
		 * @param key The key to write.
		 * @param value The value to write.
		 */
		template<typename T>
		void indent(StringView const key, T const& value)
		{
			write_key(key);
			set_state(key.is_empty() ? StateEnum::Empty : StateEnum::Key);
			write_kvp_separator();
			specialized_write<T>(value);
			increase_indentation();
		}

		/**
		 * @brief Writes a type-value pair and increases the indentation level for writing nested structures.
		 * @param key The key to write.
		 * @param type The type of the value.
		 * @param value Pointer to the value to write.
		 */
		void indent(StringView const key, TypeEnum const type, PointerConst const value)
		{
			write_key(key);
			set_state(key.is_empty() ? StateEnum::Empty : StateEnum::Key);
			write_type_value_pair(type, value);
			increase_indentation();
		}

		/**
		 * @brief Writes an optional key-value pair and increases the indentation level for writing nested structures.
		 * @tparam T The type of the value to write.
		 * @param key The key to write.
		 * @param value The value to write.
		 * @param defaultValue The default value to compare against.
		 */
		template<typename T>
		void indent_optional(StringView const key, T const& value, T const& defaultValue)
		{
			if (value != defaultValue)
			{
				indent<T>(key, value);
			}
			else
			{
				indent(key);
			}
		}

		/**
		 * @brief Writes an optional type-value pair and increases the indentation level for writing nested structures.
		 * @param key The key to write.
		 * @param type The type of the value.
		 * @param value Pointer to the value to write.
		 * @param defaultType The default type to compare against.
		 * @param defaultValue Pointer to the default value to compare against.
		 */
		void indent_optional(StringView const key, Type const type, PointerConst const value, Type const defaultType, PointerConst const defaultValue)
		{
			if (type != defaultType)
			{
				indent(key, type, value);
				return;
			}

			Size const typeSize = type.get_size();
			if (std::memcmp(value, defaultValue, typeSize) != 0)
			{
				indent(key, type, value);
			}
			else
			{
				indent(key);
			}
		}

		/**
		 * @brief Decreases the indentation level for writing nested structures.
		 */
		inline void outdent()
		{
			decrease_indentation();
			set_state(StateEnum::Unknown);
		}

	protected:
		void write_to_stream(PointerConst const data, Size const size);
		virtual void write_key(StringView const key) = 0;
		virtual void write_break() = 0;
		virtual void write_kvp_separator() = 0;
		virtual void write_type_value_pair(TypeEnum const type, PointerConst const data) = 0;
		virtual void write_bool(Bool const value) = 0;
		virtual void write_byte(Byte const value) = 0;
		virtual void write_char(Char const value) = 0;
		virtual void write_int32(Int32 const value) = 0;
		virtual void write_uint32(UInt32 const value) = 0;
		virtual void write_float32(Float32 const value) = 0;
		virtual void write_int64(Int64 const value) = 0;
		virtual void write_uint64(UInt64 const value) = 0;
		virtual void write_float64(Float64 const value) = 0;
		virtual void write_string(StringView const value) = 0;
		virtual void write_raw_value(StringView const value) = 0;
		void write_typed_value(TypeEnum const type, PointerConst const data);

	private:
		inline void increase_indentation()
		{
			MINTY_ASSERT(m_indent < SERIALIZATION_MAX_INDENTATION, ErrorCodeEnum::Serialization_InvalidIndentation);
			++m_indent;
		}

		inline void decrease_indentation()
		{
			MINTY_ASSERT(m_indent > 0, ErrorCodeEnum::Serialization_InvalidIndentation);
			--m_indent;
		}

		template<typename T>
		Bool write_primitive(T const& value)
		{
			MINTY_ABORT_F(ErrorCodeEnum::Serialization_UnsupportedType, typeid(T).name());
			return false;
		}

		template<>
		inline Bool write_primitive<Bool>(Bool const& value) { write_bool(value); }

		template<>
		inline Bool write_primitive<Byte>(Byte const& value) { write_byte(value); }

		template<>
		inline Bool write_primitive<Char>(Char const& value) { write_char(value); }

		template<>
		inline Bool write_primitive<Int32>(Int32 const& value) { write_int32(value); }

		template<>
		inline Bool write_primitive<UInt32>(UInt32 const& value) { write_uint32(value); }

		template<>
		inline Bool write_primitive<Float32>(Float32 const& value) { write_float32(value); }

		template<>
		inline Bool write_primitive<Int64>(Int64 const& value) { write_int64(value); }

		template<>
		inline Bool write_primitive<UInt64>(UInt64 const& value) { write_uint64(value); }

		template<>
		inline Bool write_primitive<Float64>(Float64 const& value) { write_float64(value); }

		template<>
		inline Bool write_primitive<StringView>(StringView const& value) { write_string(value); }

		template<>
		inline Bool write_primitive<String>(String const& value) { write_string(value.get_view()); }

		template<typename T>
		requires(!Parsable<T> && !Serializable<T>)
		void specialized_write(T const& value)
		{
			write_primitive<T>(value);
			write_break();
			set_state(StateEnum::None);
		}

		template<typename T>
		requires(Parsable<T> && !Serializable<T>)
		void specialized_write(T const& value)
		{
			String const valueStr = Parser<T>::to_string(value);
			write_raw_value(valueStr);
			write_break();
			set_state(StateEnum::None);
		}

		template<typename T>
		requires Serializable<T>
		void specialized_write(T const& value)
		{
			increase_indentation();
			Serializer<T>::serialize(*this, value);
			decrease_indentation();
			set_state(StateEnum::None);
		}

#pragma region Variables

	private:
		Shared<Stream> m_stream;
		Stack<PointerConst> m_userStack;
		Int m_indent;
		StateEnum m_state;

#pragma endregion
	};
}
