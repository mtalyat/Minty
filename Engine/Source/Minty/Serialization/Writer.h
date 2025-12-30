#ifndef MINTY_SERIALIZATION_WRITER_H
#define MINTY_SERIALIZATION_WRITER_H

/**
 * @file Writer.h
 * @brief Header file defining the Writer class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Stream/Stream.h"
#include "Minty/Data/Stack.h"

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
		Bool write(StringView const key, T const& value)
		{
			// Write the key
			if(!write_key(key))
			{
				return false;
			}

			// Write the value
			if(!write<T>(value))
			{
				return false;
			}

			// Write a line break after the value, if necessary
			return write_break();
		}

		Bool write(StringView const key, Type const type, AnyConst const value)
		{
			// Write the key
			if (!write_key(key))
			{
				return false;
			}

			// Write the type
			if (!write_type_value_pair(type, value))
			{
				return false;
			}
			
			// Write a line break after the value, if necessary
			return write_break();
		}

		/**
		 * @brief Increases the indentation level for writing nested structures.
		 * @returns True if successful, false otherwise.
		 */
		virtual Bool indent() = 0;

		/**
		 * @brief Decreases the indentation level for writing nested structures.
		 */
		virtual void outdent() = 0;

	protected:
		Bool write_to_stream(AnyConst const data, Size const size);
		virtual Bool write_key(StringView const key) = 0;
		virtual Bool write_break() { return true; }
		virtual Bool write_type_value_pair(Type const type, AnyConst const data) = 0;
		virtual Bool write_bool(Bool const value) = 0;
		virtual Bool write_byte(Byte const value) = 0;
		virtual Bool write_char(Char const value) = 0;
		virtual Bool write_int32(Int32 const value) = 0;
		virtual Bool write_uint32(UInt32 const value) = 0;
		virtual Bool write_float32(Float32 const value) = 0;
		virtual Bool write_int64(Int64 const value) = 0;
		virtual Bool write_uint64(UInt64 const value) = 0;
		virtual Bool write_float64(Float64 const value) = 0;
		virtual Bool write_string(StringView const value) = 0;
		Bool write_typed_value(Type const type, AnyConst const data);

	private:
		template<typename T>
		Bool write(T const& value)
		{
			return false;
		}

		template<>
		inline Bool write<Bool>(Bool const& value) { return write_bool(value); }

		template<>
		inline Bool write<Byte>(Byte const& value) { return write_byte(value); }

		template<>
		inline Bool write<Char>(Char const& value) { return write_char(value); }

		template<>
		inline Bool write<Int32>(Int32 const& value) { return write_int32(value); }

		template<>
		inline Bool write<UInt32>(UInt32 const& value) { return write_uint32(value); }

		template<>
		inline Bool write<Float32>(Float32 const& value) { return write_float32(value); }

		template<>
		inline Bool write<Int64>(Int64 const& value) { return write_int64(value); }

		template<>
		inline Bool write<UInt64>(UInt64 const& value) { return write_uint64(value); }

		template<>
		inline Bool write<Float64>(Float64 const& value) { return write_float64(value); }

		template<>
		inline Bool write<StringView>(StringView const& value) { return write_string(value); }

		template<>
		inline Bool write<String>(String const& value) { return write_string(value.get_view()); }

#pragma region Variables

	private:
		Shared<Stream> m_stream;
		Stack<AnyConst> m_userStack;

#pragma endregion
	};
}

#endif // MINTY_SERIALIZATION_WRITER_H