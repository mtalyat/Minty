#include "TextWriter.h"
#include "Minty/Stream/Stream.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parser.h"
#include "Minty/Tool/Util.h"

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

Bool Minty::TextWriter::indent()
{
    m_indentLevel++;
    return true;
}

void Minty::TextWriter::outdent()
{
    if (m_indentLevel > 0)
    {
        m_indentLevel--;
    }
    else
    {
        MINTY_ERROR(ErrorCode::Serialization_InvalidIndentation);
    }
}

Bool Minty::TextWriter::write_key(StringView const key)
{
    // write indentation
    for (Size i = 0; i < m_indentLevel; i++)
    {
        if (!write_to_stream(&INDENT_CHAR, sizeof(Char)))
        {
            return false;
        }
    }

    // write key
    if (key.is_empty())
    {
        write_to_stream(UNNAMED_KEY, UNNAMED_KEY_LENGTH);
    }
    else
    {
        write_to_stream(key.get_data(), key.get_size());
        write_to_stream(NAMED_KEY, NAMED_KEY_LENGTH);
    }
}

Bool Minty::TextWriter::write_break()
{
    return write_to_stream(&BREAK_CHAR, sizeof(Char));
}

Bool Minty::TextWriter::write_type_value_pair(Type const type, AnyConst const data)
{
    // write the type as a string
    String const temp = Parser<Type>::to_string(type);
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
    return write_typed_value(type, data);
}

Bool Minty::TextWriter::write_bool(Bool const value)
{
    Char buffer = value ? '1' : '0';
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
    StringBuilder builder;
    builder.append('"');
    String const safeString = Util::to_safe_string(value);
    builder.append(safeString);
    builder.append('"');
    return write_to_stream(builder.get_data(), builder.get_size());
}
