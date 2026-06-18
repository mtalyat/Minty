#pragma once

/**
 * @file TextWriter.h
 * @brief Header file defining the TextWriter class for serialization.
 * @author Mitchell Talyat
 */

#include "Writer.h"
#include "Core/Meta/Type.h"

namespace Minty
{
    /**
     * @brief A TextWriter writes text data to a stream.
     */
    class TextWriter
        : public Writer
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a TextWriter with the given stream.
         * @param stream The stream to write to.
         */
        TextWriter(Shared<Stream> const& stream);

        ~TextWriter() override = default;

#pragma endregion

#pragma region Methods

    protected:
        void write_key(StringView const key) override;
        void write_break() override;
		void write_kvp_separator() override;
		void write_type_value_pair(TypeEnum const type, PointerConst const data) override;
        void write_bool(Bool const value) override;
        void write_byte(Byte const value) override;
        void write_char(Char const value) override;
        void write_int32(Int32 const value) override;
        void write_uint32(UInt32 const value) override;
        void write_float32(Float32 const value) override;
        void write_int64(Int64 const value) override;
        void write_uint64(UInt64 const value) override;
        void write_float64(Float64 const value) override;
        void write_string(StringView const value) override;
		void write_raw_value(StringView const value) override;

#pragma endregion

#pragma region Variables

    private:
        Size m_indentLevel;

#pragma endregion
    };
}
