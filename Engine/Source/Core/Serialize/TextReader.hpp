#pragma once

/**
 * @file TextReader.h
 * @brief Header file defining the TextReader class for serialization.
 * @author Mitchell Talyat
 */

#include "Reader.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/Tuple.hpp"
#include "Core/Data/Unique.hpp"
#include "Core/Meta/Type.hpp"

namespace Minty
{
    class StringBuilder;

    /**
     * @brief A TextReader reads data from a text-based stream.
     */
    class TextReader
        : public Reader
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a TextReader with the given stream.
         * @param stream The stream to read from.
         */
        TextReader(Unique<Stream> &&stream);

        ~TextReader() override;

#pragma endregion

#pragma region Methods

    protected:
        Bool read_bool(Bool *const value) override;
        Bool read_byte(Byte *const value) override;
        Bool read_char(Char *const value) override;
        Bool read_int32(Int32 *const value) override;
        Bool read_uint32(UInt32 *const value) override;
        Bool read_float32(Float32 *const value) override;
        Bool read_int64(Int64 *const value) override;
        Bool read_uint64(UInt64 *const value) override;
        Bool read_float64(Float64 *const value) override;
        Bool read_tuple(Pointer const buffer, Size const elementSize, UInt const count, Function<Bool(Pointer)> const& readFunc) override;
        Bool read_string(String &value) override;
        Bool read_raw_value(String& value, Bool const ignoreSeparator = false) override;
        Bool read_type_value_pair(TypeEnum &type, Pointer data) override;

        Bool get_next_key(String &key) override;
        Bool check_key(StringView const key) override;
        inline Bool check_key() override { return m_hasNextKey; }
        inline Bool check_value() override { return m_hasNextValue; }
        Bool consume_next_key() override;
        Bool consume_next_value(Bool const force = false) override;
        void skip_remaining() override;

    private:
        void read_digits(StringBuilder &builder);
        Bool check_for_comment();
        Bool check_for_indentation(UInt& indentLevel);
        Bool check_for_break();
        void skip_line();

#pragma endregion

#pragma region Variables

    private:
        String m_nextKey;
        UInt m_nextIndent;
        Bool m_hasNextKey;
        Bool m_hasNextValue;

#pragma endregion
    };
}
