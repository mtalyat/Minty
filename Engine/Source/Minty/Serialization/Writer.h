#ifndef MINTY_SERIALIZATION_WRITER_H
#define MINTY_SERIALIZATION_WRITER_H

/**
 * @file Writer.h
 * @brief Header file defining the Writer class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Type.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/StringView.h"
#include "Minty/Serialization/Parser.h"
#include "Minty/Serialization/Serializer.h"
#include "Minty/Stream/Stream.h"

namespace Minty
{
	/**
	 * @brief A Writer writes data to a stream.
	 */
	class Writer
	{
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
		inline void push_user_data(AnyConst const userData) { m_userStack.push(userData); }

		/**
		 * @brief Pops user data from the user data stack.
		 */
		inline void pop_user_data() { m_userStack.pop(); }

		/**
		 * @brief Gets the user data associated with the Writer.
		 * @return Pointer to the user data.
		 */
		inline AnyConst get_user_data() const { return m_userStack.peek(); }

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
			specialized_write<T>(value);
			write_break();
		}

		/**
		 * @brief Writes a type-value pair associated with the given key.
		 * @param key The key associated with the value.
		 * @param type The type of the value.
		 * @param value Pointer to the value to write.
		 */
		void write(StringView const key, Type const type, AnyConst const value)
		{
			write_key(key);
			write_type_value_pair(type, value);
			write_break();
		}

		/**
		 * @brief Writes a key and increases the indentation level for writing nested structures.
		 * @param key The key to write.
		 */
		inline void indent(StringView const key)
		{
			write_key(key);
			increase_indentation();
		}

		/**
		 * @brief Increases the indentation level for writing nested structures.
		 */
		inline void indent()
		{
			increase_indentation();
		}

		/**
		 * @brief Decreases the indentation level for writing nested structures.
		 */
		inline void outdent()
		{
			decrease_indentation();
		}

	protected:
		void write_to_stream(AnyConst const data, Size const size);
		virtual void write_key(StringView const key) = 0;
		virtual void write_break() {}
		virtual void write_type_value_pair(Type const type, AnyConst const data) = 0;
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
		void write_typed_value(Type const type, AnyConst const data);

	private:
		inline void increase_indentation()
		{
			MINTY_ASSERT(m_indent < SERIALIZATION_MAX_INDENTATION, ErrorCode::Serialization_InvalidIndentation);
			++m_indent;
		}

		inline void decrease_indentation()
		{
			MINTY_ASSERT(m_indent > 0, ErrorCode::Serialization_InvalidIndentation);
			--m_indent;
		}

		template<typename T>
		Bool write_primitive(T const& value)
		{
			MINTY_ABORT_F(ErrorCode::Serialization_UnsupportedType, typeid(T).name());
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
		}

		template<typename T>
		requires(Parsable<T> && !Serializable<T>)
		void specialized_write(T const& value)
		{
			String const valueStr = Parser<T>::to_string(value);
			write_raw_value(valueStr);
		}

		template<typename T>
		requires Serializable<T>
		void specialized_write(T const& value)
		{
			increase_indentation();
			Serializer<T>::serialize(*this, value);
			decrease_indentation();
		}

#pragma region Variables

	private:
		Shared<Stream> m_stream;
		Stack<AnyConst> m_userStack;
		Int m_indent;

#pragma endregion
	};
}

#endif // MINTY_SERIALIZATION_WRITER_H