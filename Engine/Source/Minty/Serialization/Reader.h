#ifndef MINTY_SOURCE_SERIALIZE_READER_H
#define MINTY_SOURCE_SERIALIZE_READER_H

/**
 * @file Reader.h
 * @brief Header file defining the Reader class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Type.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Serialization/Evaluator.h"
#include "Minty/Serialization/Parser.h"
#include "Minty/Serialization/Serializer.h"
#include "Minty/Stream/Stream.h"

namespace Minty
{
    /**
     * @brief A Reader reads data from a stream.
     */
    class Reader
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a Reader with the given stream.
         * @param stream The stream to read from.
         */
        Reader(Shared<Stream> const &stream);

        virtual ~Reader() = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Pushes user data onto the user data stack.
         * @param userData Pointer to the user data.
         */
        inline void push_user_data(Any const userData) { m_userStack.push(userData); }

        /**
         * @brief Pops user data from the user data stack.
         */
        inline void pop_user_data() { m_userStack.pop(); }

        /**
         * @brief Gets the user data associated with the Reader.
         * @return Pointer to the user data.
         */
        inline Any get_user_data() const
        {
            if (m_userStack.is_empty())
            {
                return nullptr;
            }
            return m_userStack.peek();
        }

        /**
         * @brief Gets the stream associated with this Reader.
         * @return Shared pointer to the stream.
         */
        inline Shared<Stream> const &get_stream() const { return m_stream; }

        /**
         * @brief Gets the current indentation level.
         * @return The current indentation level.
         */
        inline UInt get_indent() const { return m_indent; }

        /**
         * @brief Checks whether to check for ignored data at the current indent level when reading.
         * @return True if checking for ignored data, false otherwise.
         */
        inline Bool get_validation() const { return m_validation; }

        /**
         * @brief Sets whether to check for ignored data at the current indent level when reading.
         * @param checkForIgnoredData True to check for ignored data, false to ignore it.
         */
        inline void set_validation(Bool const checkForIgnoredData) { m_validation = checkForIgnoredData; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Reads a value associated with the given key.
         * @tparam T The type of the value to read.
         * @param key The key associated with the value.
         * @param value Reference to store the read value.
         * @returns True if the value was read successfully, false otherwise.
         */
        template <typename T>
        Bool read(StringView const key, T &value)
        {
            // Check key and value- if the key does not match or the value is not present, return false
            if (!check_key(key))
            {
                return false;
            }

            // Consume the key
            consume_next_key();

            // Read the value
            return specialized_read<T>(value);
        }

        /**
         * @brief Reads a type-value pair associated with the given key.
         * @tparam T The type of the value to read.
         * @param key The key associated with the value.
         * @param type Reference to store the read type.
         * @param data Pointer to store the read value.
         * @returns True if the type-value pair was read successfully, false otherwise.
         */
        Bool read(StringView const key, Type &type, Any const data)
        {
            // Check key- if not present or does not match, return false
            if (!check_key_and_value(key))
            {
                return false;
            }

            // consume the key and value
            consume_next_key();

            // Read the type-value pair
            return read_type_value_pair(type, data);
        }

        /**
         * @brief Reads the next key.
         * @tparam T The type of the value to read.
         * @param key Reference to store the read key.
         * @returns True if the key was read successfully, false otherwise.
         */
        Bool read_next(String &key)
        {
            // get the next key
            if (!get_next_key(key))
            {
                // there is no next key
                return false;
            }

            // consume the key and value
            consume_next_key_and_value();

            return true;
        }

        /**
         * @brief Reads the next key-value pair.
         * @tparam T The type of the value to read.
         * @param key Reference to store the read key.
         * @param value Reference to store the read value.
         * @returns True if the key-value pair was read successfully, false otherwise.
         */
        template <typename T>
        Bool read_next(String &key, T &value)
        {
            // get the next key
            if (!get_next_key(key))
            {
                return false;
            }

            // consume the key
            consume_next_key();

            // read the value with that key
            return specialized_read<T>(value);
        }

        /**
         * @brief Reads the next key-type-value triplet.
         * @tparam T The type of the value to read.
         * @param key Reference to store the read key.
         * @param type Reference to store the read type.
         * @param data Pointer to store the read value.
         * @returns True if the key-type-value triplet was read successfully, false otherwise.
         */
        Bool read_next(String &key, Type &type, Any const data)
        {
            // get the next key
            if (!get_next_key(key))
            {
                return false;
            }

            // do nothing if no value
            if (!check_value())
            {
                return false;
            }

            // consume the key
            consume_next_key();

            // read the type-value pair
            return read_type_value_pair(type, data);
        }

        /**
         * @brief Reads the next optional key-value pair.
         * @tparam T The type of the value to read.
         * @param key Reference to store the read key.
         * @param value Reference to store the read value.
         * @param defaultValue The default value to use if the value is not present.
         * @returns True if the key-value pair was read successfully, false otherwise.
         */
        template<typename T>
        Bool read_next_optional(String &key, T &value, T const& defaultValue = {})
        {
            // get the next key
            if (!get_next_key(key))
            {
                return false;
            }

            // consume the key
            consume_next_key();

            // read the value with that key
            if(!specialized_read<T>(value))
            {
                value = defaultValue;
            }

            return true;
        }

        /**
         * @brief Reads an inline value (no key).
         * @tparam T The type of the value to read.
         * @param value Reference to store the read value.
         * @returns True if the value was read successfully, false otherwise.
         */
        template<typename T>
        Bool read_inline(T &value)
        {
            // There must be no key, but there must be a value
            if(check_key() || !check_value())
            {
                return false;
            }

            return specialized_read<T>(value);
        }

        /**
         * @brief Reads an inline type-value pair (no key).
         * @param type Reference to store the read type.
         * @param data Pointer to store the read value.
         * @returns True if the type-value pair was read successfully, false otherwise.
         */
        Bool read_inline(Type &type, Any const data)
        {
            // There must be no key, but there must be a value
            if(check_key() || !check_value())
            {
                return false;
            }

            return read_type_value_pair(type, data);
        }

        /**
         * @brief Reads a primary value, trying inline first, then with key.
         * @tparam T The type of the value to read.
         * @param key The key associated with the value.
         * @param value Reference to store the read value.
         * @returns True if the value was read successfully, false otherwise.
         */
        template<typename T>
        Bool read_primary(StringView const key, T &value)
        {
            // Read inline if able
            if (read_inline(value))
            {
                return true;
            }

            // Otherwise read with key
            return read(key, value);
        }

        /**
         * @brief Reads a primary type-value pair, trying inline first, then with key.
         * @param key The key associated with the value.
         * @param type Reference to store the read type.
         * @param data Pointer to store the read value.
         * @returns True if the type-value pair was read successfully, false otherwise.
         */
        Bool read_primary(StringView const key, Type &type, Any const data)
        {
            // Read inline if able
            if (read_inline(type, data))
            {
                return true;
            }

            // Otherwise read with key
            return read(key, type, data);
        }

        /**
         * @brief Increases the indentation level for reading nested structures.
         * @returns True if successful, false otherwise.
         */
        Bool indent_next(String &key)
        {
            // get the next key
            if (!get_next_key(key))
            {
                return false;
            }

            // consume the key and value
            consume_next_key();

            // indent
            increase_indentation();

            return true;
        }

        /**
         * @brief Increases the indentation level for reading nested structures with a key and reads the value.
         * @tparam T The type of the value to read.
         * @param key The key associated with the nested structure.
         * @param value Reference to store the read value.
         * @returns True if successful, false otherwise.
         */
        template <typename T>
        Bool indent_next(String &key, T &value)
        {
            // get the next key
            if (!get_next_key(key))
            {
                return false;
            }

            // read the value
            if(!specialized_read<T>(value))
            {
                return false;
            }

            // consume the key
            consume_next_key();

            // indent
            increase_indentation();

            return true;
        }

        /**
         * @brief Increases the indentation level for reading nested structures with an optional key and reads the value.
         * @tparam T The type of the value to read.
         * @param key The key associated with the nested structure.
         * @param value Reference to store the read value.
         * @param defaultValue The default value to use if the value is not present.
         * @returns True if successful, false otherwise.
         */
        template<typename T>
        Bool indent_next_optional(String &key, T &value, T const& defaultValue = {})
        {
            // get the next key
            if (!get_next_key(key))
            {
                return false;
            }

            // consume the key
            consume_next_key();

            // indent
            increase_indentation();

            // read the value
            if (!specialized_read<T>(value))
            {
                value = defaultValue;
            }

            return true;
        }

        /**
         * @brief Increases the indentation level for reading nested structures with a key. Only increases the indent if the given key is found.
         * @param key The key associated with the nested structure.
         * @returns True if successful, false otherwise.
         */
        Bool indent(StringView const key)
        {
            // Check key- if not present or does not match, return false
            if (!check_key(key))
            {
                return false;
            }

            // consume the key and value
            consume_next_key();

            // indent
            increase_indentation();

            return true;
        }

        /**
         * @brief Decreases the indentation level for reading nested structures.
         */
        inline void outdent()
        {
            decrease_indentation();
        }

        /**
         * @brief Ignores the key and its associated value, if present.
         * @param key The key to ignore.
         */
        void ignore(StringView const key)
        {
            if(check_key(key))
            {
                consume_next_key_and_value();
            }
        }

        /**
         * @brief Saves the current position in the stream as a bookmark.
         * @returns The bookmark ID.
         */
        Handle save_bookmark();

        /**
         * @brief Loads the position in the stream associated with the given bookmark.
         * @param bookmark The bookmark ID.
         */
        void load_bookmark(Handle const bookmark);

    protected:
        Bool read_from_stream(Any data, Size const size);
        Bool peek(Char &ch);
        virtual Bool read_bool(Bool *const value) = 0;
        virtual Bool read_byte(Byte *const value) = 0;
        virtual Bool read_char(Char *const value) = 0;
        virtual Bool read_int32(Int32 *const value) = 0;
        virtual Bool read_uint32(UInt32 *const value) = 0;
        virtual Bool read_float32(Float32 *const value) = 0;
        virtual Bool read_int64(Int64 *const value) = 0;
        virtual Bool read_uint64(UInt64 *const value) = 0;
        virtual Bool read_float64(Float64 *const value) = 0;
        virtual Bool read_tuple(Any const buffer, Size const elementSize, UInt const count, Function<Bool(Any)> const& readFunc) = 0;
        virtual Bool read_string(String &value) = 0;
        virtual Bool read_raw_value(String &value, Bool const ignoreSeparator = false) = 0;
        virtual Bool read_type_value_pair(Type &type, Any data) = 0;
        Bool read_typed_value(Type const type, Any data);

        // gets the next key in the stream
        virtual Bool get_next_key(String &key) = 0;
        // checks if the current key matches the given key
        virtual Bool check_key(StringView const key) = 0;
        // checks if there is a current key without consuming it
        virtual Bool check_key() = 0;
        // checks if there is a value for the current key without consuming it
        virtual Bool check_value() = 0;
        // checks both key and value
        Bool check_key_and_value(StringView const key)
        {
            if (!check_key(key))
            {
                return false;
            }

            if (!check_value())
            {
                MINTY_WARNING_F(ErrorCode::Serialization_MissingValue, key);
                return false;
            }

            return true;
        }
        virtual Bool consume_next_key() = 0;
        virtual Bool consume_next_value(Bool const force = false) = 0;
        inline void consume_next_key_and_value()
        {
            consume_next_key();
            consume_next_value();
        }
        virtual void skip_remaining() = 0;

    private:
        inline void increase_indentation()
        {
            MINTY_ASSERT(m_indent < SERIALIZATION_MAX_INDENTATION, ErrorCode::Serialization_InvalidIndentation);
            ++m_indent;
        }
        inline void decrease_indentation()
        {
            MINTY_ASSERT(m_indent > 0, ErrorCode::Serialization_InvalidIndentation);
            skip_remaining();
            --m_indent;
        }

        template <typename T>
        Bool read_primitive(T &value)
        {
            MINTY_ABORT_F(ErrorCode::Serialization_UnsupportedType, typeid(T).name());
            return false;
        }

        template <>
        inline Bool read_primitive<Bool>(Bool &value) { return read_bool(&value); }

        template <>
        inline Bool read_primitive<Byte>(Byte &value) { return read_byte(&value); }

        template <>
        inline Bool read_primitive<Char>(Char &value) { return read_char(&value); }

        template <>
        inline Bool read_primitive<Int32>(Int32 &value) { return read_int32(&value); }

        template <>
        inline Bool read_primitive<UInt32>(UInt32 &value) { return read_uint32(&value); }

        template <>
        inline Bool read_primitive<Float32>(Float32 &value) { return read_float32(&value); }

        template <>
        inline Bool read_primitive<Int64>(Int64 &value) { return read_int64(&value); }

        template <>
        inline Bool read_primitive<UInt64>(UInt64 &value) { return read_uint64(&value); }

        template <>
        inline Bool read_primitive<Float64>(Float64 &value) { return read_float64(&value); }

        template<>
        inline Bool read_primitive(Int2 &value) { return read_tuple(&value, sizeof(Int32), 2, [this](Any data) { return read_int32(static_cast<Int32*>(data)); }); }

        template<>
        inline Bool read_primitive(Int3 &value) { return read_tuple(&value, sizeof(Int32), 3, [this](Any data) { return read_int32(static_cast<Int32*>(data)); }); }

        template<>
        inline Bool read_primitive(Int4 &value) { return read_tuple(&value, sizeof(Int32), 4, [this](Any data) { return read_int32(static_cast<Int32*>(data)); }); }

        template<>
        inline Bool read_primitive(UInt2 &value) { return read_tuple(&value, sizeof(UInt32), 2, [this](Any data) { return read_uint32(static_cast<UInt32*>(data)); }); }

        template<>
        inline Bool read_primitive(UInt3 &value) { return read_tuple(&value, sizeof(UInt32), 3, [this](Any data) { return read_uint32(static_cast<UInt32*>(data)); }); }
        
        template<>
        inline Bool read_primitive(UInt4 &value) { return read_tuple(&value, sizeof(UInt32), 4, [this](Any data) { return read_uint32(static_cast<UInt32*>(data)); }); }

        template<>
        inline Bool read_primitive(Float2 &value) { return read_tuple(&value, sizeof(Float32), 2, [this](Any data) { return read_float32(static_cast<Float32*>(data)); }); }

        template<>
        inline Bool read_primitive(Float3 &value) { return read_tuple(&value, sizeof(Float32), 3, [this](Any data) { return read_float32(static_cast<Float32*>(data)); }); }

        template<>
        inline Bool read_primitive(Float4 &value) { return read_tuple(&value, sizeof(Float32), 4, [this](Any data) { return read_float32(static_cast<Float32*>(data)); }); }

        template<>
        inline Bool read_primitive(WInt2 &value) { return read_tuple(&value, sizeof(Int64), 2, [this](Any data) { return read_int64(static_cast<Int64*>(data)); }); }

        template<>
        inline Bool read_primitive(WInt3 &value) { return read_tuple(&value, sizeof(Int64), 3, [this](Any data) { return read_int64(static_cast<Int64*>(data)); }); }

        template<>
        inline Bool read_primitive(WInt4 &value) { return read_tuple(&value, sizeof(Int64), 4, [this](Any data) { return read_int64(static_cast<Int64*>(data)); }); }

        template<>
        inline Bool read_primitive(UWInt2 &value) { return read_tuple(&value, sizeof(UInt64), 2, [this](Any data) { return read_uint64(static_cast<UInt64*>(data)); }); }

        template<>
        inline Bool read_primitive(UWInt3 &value) { return read_tuple(&value, sizeof(UInt64), 3, [this](Any data) { return read_uint64(static_cast<UInt64*>(data)); }); }

        template<>
        inline Bool read_primitive(UWInt4 &value) { return read_tuple(&value, sizeof(UInt64), 4, [this](Any data) { return read_uint64(static_cast<UInt64*>(data)); }); }

        template<>
        inline Bool read_primitive(WFloat2 &value) { return read_tuple(&value, sizeof(Float64), 2, [this](Any data) { return read_float64(static_cast<Float64*>(data)); }); }

        template<>
        inline Bool read_primitive(WFloat3 &value) { return read_tuple(&value, sizeof(Float64), 3, [this](Any data) { return read_float64(static_cast<Float64*>(data)); }); }

        template<>
        inline Bool read_primitive(WFloat4 &value) { return read_tuple(&value, sizeof(Float64), 4, [this](Any data) { return read_float64(static_cast<Float64*>(data)); }); }

        template <>
        inline Bool read_primitive<String>(String &value) { return read_string(value); }
        
        // Specialized Read for primitive types.
        template <typename T>
            requires(!Evaluatable<T> && !Parsable<T> && !Serializable<T>)
        Bool specialized_read(T &value)
        {
            if(!check_value())
            {
                return false;
            }
            Bool const result = read_primitive<T>(value);
            consume_next_value();
            return result;
        }

        // Specialzied Read for Evaluatable types.
        template <typename T>
            requires(Evaluatable<T> && !Serializable<T>)
        Bool specialized_read(T &value)
        {
            if(!check_value())
            {
                return false;
            }
            String valueStr;
            if (!read_raw_value(valueStr, true))
            {
                return false;
            }
            consume_next_value();
            value = Evaluator<T>::evaluate(valueStr.get_view());
            return true;
        }

        // Specialized Read for Parsable types.
        template <typename T>
            requires(Parsable<T> && !Evaluatable<T> && !Serializable<T>)
        Bool specialized_read(T &value)
        {
            if(!check_value())
            {
                return false;
            }
            String valueStr;
            if (!read_raw_value(valueStr, true))
            {
                return false;
            }
            consume_next_value();
            return Parser<T>::parse(valueStr.get_view(), value);
        }

        // Specialized Read for Serializable types.
        template <typename T>
            requires Serializable<T>
        Bool specialized_read(T &value)
        {
            // Step into and read the value
            increase_indentation();
            Bool const result = Serializer<T>::deserialize(*this, value);
            consume_next_value();
            decrease_indentation();
            return result;
        }

#pragma endregion

#pragma region Variables

    private:
        Shared<Stream> m_stream;
        Stack<Any> m_userStack;
        Map<Handle, Tuple<StreamPosition, UInt>> m_bookmarks;
        UInt m_indent;
        Bool m_validation; // when validating, check for ignored data and warn if found

#pragma endregion
    };
}

#endif // MINTY_SOURCE_SERIALIZE_READER_H