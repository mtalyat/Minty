#pragma once

/**
 * @file TextWriter.hpp
 * @brief Header file defining the TextWriter class for serialization.
 * @author Mitchell Talyat
 */

#include "Writer.hpp"
#include "Core/Meta/Type.hpp"

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
        Bool write_key(StringView const key) override;
        Bool write_break() override;
		Bool write_kvp_separator() override;
		Bool write_type_value_pair(TypeEnum const type, PointerConst const data) override;
        Bool write_bool(Bool const value) override;
        Bool write_byte(Byte const value) override;
        Bool write_char(Char const value) override;
        Bool write_int32(Int32 const value) override;
        Bool write_uint32(UInt32 const value) override;
        Bool write_float32(Float32 const value) override;
        Bool write_int64(Int64 const value) override;
        Bool write_uint64(UInt64 const value) override;
        Bool write_float64(Float64 const value) override;
        Bool write_string(StringView const value) override;
		Bool write_raw_value(StringView const value) override;

#pragma endregion

#pragma region Variables

    private:
        Size m_indentLevel;

#pragma endregion
    };
}
