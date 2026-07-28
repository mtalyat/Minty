#include "pch.hpp"
#include "TextWriter.hpp"
#include "Core/Tool/String.hpp"
#include "Core/Serialize/ParsedTypes.hpp"
#include "Core/Data/StringBuilder.hpp"

using namespace Minty;

static constexpr Char INDENT_CHAR = '\t';
static constexpr Char BREAK_CHAR = '\n';
static constexpr Size UNNAMED_KEY_LENGTH = 2;
static constexpr Char UNNAMED_KEY[UNNAMED_KEY_LENGTH + 1] = "- ";
static constexpr Size NAMED_KEY_LENGTH = 2;
static constexpr Char NAMED_KEY[NAMED_KEY_LENGTH + 1] = ": ";

Minty::TextWriter::TextWriter(Shared<Stream> const& stream)
    : Writer(stream), m_indentLevel(0)
{
}

Bool Minty::TextWriter::write_key(StringView const key)
{
    // if the next item is a value, finish the previous line
    if(get_state() != StateEnum::None)
    {
        if(!write_break())
        {
            return false;
        }
    }

    // write indentation
    for (Size i = 0; i < m_indentLevel; i++)
    {
        if(!write_to_stream(&INDENT_CHAR, sizeof(Char)))
        {
            return false;
        }
    }

    // write key
    if (!key.is_empty())
    {
        if(!write_to_stream(key.get_data(), key.get_size()))
        {
            return false;
        }
    }

    return true;
}

Bool Minty::TextWriter::write_break()
{
    return write_to_stream(&BREAK_CHAR, sizeof(Char));
}

Bool Minty::TextWriter::write_kvp_separator()
{
    switch(get_state())
    {
        case StateEnum::Key:
            return write_to_stream(NAMED_KEY, NAMED_KEY_LENGTH);
        case StateEnum::Empty:
            return write_to_stream(UNNAMED_KEY, UNNAMED_KEY_LENGTH);
        default:
            // no key written before value
            MINTY_ERROR(ErrorCodeEnum::Serialization_Write);
            return false;
    }
}

Bool Minty::TextWriter::write_type_value_pair(TypeEnum const type, PointerConst const data)
{
    // write the type as a string
    String const temp = Parser<TypeEnum>::to_string(type);
    if(!write_to_stream(temp.get_data(), temp.get_size()))
    {
        return false;
    }

    // write a separator, similar to a key value pair
    if(!write_to_stream(NAMED_KEY, NAMED_KEY_LENGTH))
    {
        return false;
    }

    // write the value, based on type
    if(!write_typed_value(type, data))
    {
        return false;
    }

    // finish the line
    if(!write_break())
    {
        return false;
    }
    set_state(StateEnum::None);
    return true;
}

Bool Minty::TextWriter::write_bool(Bool const value)
{
    Char const buffer = value ? '1' : '0';
    return write_to_stream(&buffer, sizeof(Char));
}

Bool Minty::TextWriter::write_byte(Byte const value)
{
    String const temp = Parser<Byte>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_char(Char const value)
{
    return write_to_stream(&value, sizeof(Char));
}

Bool Minty::TextWriter::write_int32(Int32 const value)
{
    String const temp = Parser<Int32>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_uint32(UInt32 const value)
{
    String const temp = Parser<UInt32>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_float32(Float32 const value)
{
    String const temp = Parser<Float32>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_int64(Int64 const value)
{
    String const temp = Parser<Int64>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_uint64(UInt64 const value)
{
    String const temp = Parser<UInt64>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_float64(Float64 const value)
{
    String const temp = Parser<Float64>::to_string(value);
    return write_to_stream(temp.get_data(), temp.get_size());
}

Bool Minty::TextWriter::write_string(StringView const value)
{
    String const safeString = Tool::to_safe_string(value);

    StringBuilder builder;
    builder.append('"');
    builder.append(safeString);
    builder.append('"');
    return write_to_stream(builder.get_data(), builder.get_size());
}

Bool Minty::TextWriter::write_raw_value(StringView const value)
{
    return write_to_stream(value.get_data(), value.get_size());
}
