#ifndef MINTY_SERIALIZATION_TEXTREADER_H
#define MINTY_SERIALIZATION_TEXTREADER_H

/**
 * @file TextReader.h
 * @brief Header file defining the TextReader class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Reader.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Tuple.h"

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
        TextReader(Shared<Stream> const& stream);

        ~TextReader() override = default;

#pragma endregion

#pragma region Methods

    public:
        Bool indent() override;
        Bool indent(StringView const key) override;
        void outdent() override;
        Handle save_bookmark() override;
        void load_bookmark(Handle const bookmark) override;

    protected:
        Bool read_bool(Bool &value) override;
        Bool read_byte(Byte &value) override;
        Bool read_char(Char &value) override;
        Bool read_int32(Int32 &value) override;
        Bool read_uint32(UInt32 &value) override;
        Bool read_float32(Float32 &value) override;
        Bool read_int64(Int64 &value) override;
        Bool read_uint64(UInt64 &value) override;
        Bool read_float64(Float64 &value) override;
        Bool read_string(String &value) override;
        Bool read_type_value_pair(Type &type, Any data) override;

        Bool get_next_key(String &key) override;
        Bool check_key(StringView const key) override;

    private:
        void read_digits(StringBuilder &builder);
        inline Bool has_next() { return !m_nextKey.is_empty(); }

#pragma endregion

#pragma region Variables

    private:
        String m_nextKey;
        UInt m_nextIndent;
        UInt m_currentIndent;
        Map<Handle, Tuple<StreamPosition, UInt>> m_bookmarks;

#pragma endregion
    };
}

#endif // MINTY_SERIALIZATION_TEXTREADER_H