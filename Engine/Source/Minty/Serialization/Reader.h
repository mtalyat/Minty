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
#include "Minty/Memory/DefaultAllocator.h"
#include "Minty/Stream/Stream.h"

namespace Minty
{
    class StringBuilder;

    class Reader
    {
#pragma region Constructors

    public:
        Reader(Unique<Stream>&& stream);

#pragma endregion

#pragma region Methods

    public:
        template<typename T>
        Bool read(StringView const key, T& value)
        {
            // Check key- if not present or does not match, return false
            if(!check_key(key))
            {
                return false;
            }

            // Read the value
            return read<T>(value);
        }

        template<typename T>
        Bool read_next(String& key, T& value)
        {
            if(!get_next_key(key))
            {
                return false;
            }
            return read(key.get_view(), value);
        }

        virtual Bool indent() = 0;

        virtual void outdent() = 0;

    protected:
        virtual Bool read(Any data, Size const size) = 0;
        virtual Bool read_bool(Bool& value) = 0;
        virtual Bool read_byte(Byte& value) = 0;
        virtual Bool read_char(Char& value) = 0;
        virtual Bool read_int32(Int32& value) = 0;
        virtual Bool read_uint32(UInt32& value) = 0;
        virtual Bool read_float32(Float32& value) = 0;
        virtual Bool read_int64(Int64& value) = 0;
        virtual Bool read_uint64(UInt64& value) = 0;
        virtual Bool read_float64(Float64& value) = 0;
        virtual Bool read_string(String& value) = 0;

        virtual Bool get_next_key(String& key) = 0;
        virtual Bool check_key(StringView const key) = 0;

    private:
        template<typename T>
        Bool read(T& value)
        {
            return false;
        }

        template<>
        inline Bool read<Bool>(Bool& value) { return read_bool(value); }

        template<>
        inline Bool read<Byte>(Byte& value) { return read_byte(value); }

        template<>
        inline Bool read<Char>(Char& value) { return read_char(value); }

        template<>
        inline Bool read<Int32>(Int32& value) { return read_int32(value); }

        template<>
        inline Bool read<UInt32>(UInt32& value) { return read_uint32(value); }

        template<>
        inline Bool read<Float32>(Float32& value) { return read_float32(value); }

        template<>
        inline Bool read<Int64>(Int64& value) { return read_int64(value); }

        template<>
        inline Bool read<UInt64>(UInt64& value) { return read_uint64(value); }

        template<>
        inline Bool read<Float64>(Float64& value) { return read_float64(value); }

        template<>
        inline Bool read<String>(String& value) { return read_string(value); }

#pragma endregion

#pragma region Variables

    protected:
        Unique<Stream> m_stream;

#pragma endregion
    };

    class TextReader : public Reader
    {
#pragma region Constructors

    public:
        TextReader(Unique<Stream>&& stream);

#pragma endregion

#pragma region Methods

    public:
        Bool indent() override;

        void outdent() override;

    protected:
        Bool read(Any data, Size const size) override;
        Bool read_bool(Bool& value) override;
        Bool read_byte(Byte& value) override;
        Bool read_char(Char& value) override;
        Bool read_int32(Int32& value) override;
        Bool read_uint32(UInt32& value) override;
        Bool read_float32(Float32& value) override;
        Bool read_int64(Int64& value) override;
        Bool read_uint64(UInt64& value) override;
        Bool read_float64(Float64& value) override;
        Bool read_string(String& value) override;

        Bool get_next_key(String& key) override;
        Bool check_key(StringView const key) override;

    private:
        void read_digits(StringBuilder& builder);
        inline Bool has_next() { return !m_nextKey.is_empty(); }

#pragma endregion

#pragma region Variables

    private:
        String m_nextKey;
        UInt m_nextIndent;
        UInt m_currentIndent;

#pragma endregion
    };
}

#endif // MINTY_SOURCE_SERIALIZE_READER_H