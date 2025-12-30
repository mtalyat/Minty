#ifndef MINTY_SOURCE_SERIALIZE_READER_H
#define MINTY_SOURCE_SERIALIZE_READER_H

/**
 * @file Reader.h
 * @brief Header file defining the Reader class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/String.h"
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
        inline Shared<Stream> const& get_stream() const { return m_stream; }

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
            // Check key- if not present or does not match, return false
            if (!check_key(key))
            {
                return false;
            }

            // TODO: check if value even exists

            // Read the value
            return read<T>(value);
        }

        /**
         * @brief Reads a type-value pair associated with the given key.
         * @tparam T The type of the value to read.
         * @param key The key associated with the value.
         * @param type Reference to store the read type.
         * @param data Pointer to store the read value.
         * @returns True if the type-value pair was read successfully, false otherwise.
         */
        Bool read(StringView const key, Type& type, Any const data)
        {
            // Check key- if not present or does not match, return false
            if (!check_key(key))
            {
                return false;
            }

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

            // consume the key
            check_key(key.get_view());

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
                // there is no next key
                return false;
            }

            // read the value with that key
            return read(key.get_view(), value);
        }

        /**
         * @brief Increases the indentation level for reading nested structures.
         * @returns True if successful, false otherwise.
         */
        virtual Bool indent() = 0;

        /**
         * @brief Increases the indentation level for reading nested structures with a key. Only increases the indent if the given key is found.
         * @param key The key associated with the nested structure.
         * @returns True if successful, false otherwise.
         */
        virtual Bool indent(StringView const key) = 0;

        /**
         * @brief Decreases the indentation level for reading nested structures.
         */
        virtual void outdent() = 0;
        
        /**
         * @brief Saves the current position in the stream as a bookmark.
         * @returns The bookmark ID.
         */
        virtual Handle save_bookmark() = 0;

        /**
         * @brief Loads the position in the stream associated with the given bookmark.
         * @param bookmark The bookmark ID.
         */
        virtual void load_bookmark(Handle const bookmark) = 0;

    protected:
        Bool read_from_stream(Any data, Size const size);
        Bool peek(Char &ch);
        virtual Bool read_bool(Bool &value) = 0;
        virtual Bool read_byte(Byte &value) = 0;
        virtual Bool read_char(Char &value) = 0;
        virtual Bool read_int32(Int32 &value) = 0;
        virtual Bool read_uint32(UInt32 &value) = 0;
        virtual Bool read_float32(Float32 &value) = 0;
        virtual Bool read_int64(Int64 &value) = 0;
        virtual Bool read_uint64(UInt64 &value) = 0;
        virtual Bool read_float64(Float64 &value) = 0;
        virtual Bool read_string(String &value) = 0;
        virtual Bool read_type_value_pair(Type &type, Any data) = 0;
        Bool read_typed_value(Type const type, Any data);        

        virtual Bool get_next_key(String &key) = 0;
        virtual Bool check_key(StringView const key) = 0;

    private:
        template <typename T>
        Bool read(T &value)
        {
            return false;
        }

        template <>
        inline Bool read<Bool>(Bool &value) { return read_bool(value); }

        template <>
        inline Bool read<Byte>(Byte &value) { return read_byte(value); }

        template <>
        inline Bool read<Char>(Char &value) { return read_char(value); }

        template <>
        inline Bool read<Int32>(Int32 &value) { return read_int32(value); }

        template <>
        inline Bool read<UInt32>(UInt32 &value) { return read_uint32(value); }

        template <>
        inline Bool read<Float32>(Float32 &value) { return read_float32(value); }

        template <>
        inline Bool read<Int64>(Int64 &value) { return read_int64(value); }

        template <>
        inline Bool read<UInt64>(UInt64 &value) { return read_uint64(value); }

        template <>
        inline Bool read<Float64>(Float64 &value) { return read_float64(value); }

        template <>
        inline Bool read<String>(String &value) { return read_string(value); }

#pragma endregion

#pragma region Variables

    private:
        Shared<Stream> m_stream;
        Stack<Any> m_userStack;

#pragma endregion
    };
}

#endif // MINTY_SOURCE_SERIALIZE_READER_H