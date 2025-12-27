#include "pch.h"
#include "Reader.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Stream/Stream.h"
#include "Minty/Serialization/Parser.h"

using namespace Minty;

Minty::TextReader::TextReader(Unique<Stream>&& stream)
    : Reader(std::move(stream))
    , m_nextKey()
    , m_nextIndent(0)
    , m_currentIndent(0)
{
}

Bool Minty::TextReader::indent()
{
    // Get the next key and indent level
    if(!has_next())
    {
        if(!get_next_key(m_nextKey))
        {
            return false;
        }
    }

    // If the next indent is greater than the current, indent
    if(m_nextIndent > m_currentIndent)
    {
        MINTY_ASSERT(m_nextIndent == m_currentIndent + 1, ErrorCode::Serialization_InvalidFormat); // Cannot indent more than one level at a time
        m_currentIndent = m_nextIndent;
        return true;
    }
    return false;
}

void Minty::TextReader::outdent()
{
    MINTY_ASSERT(m_currentIndent > 0, ErrorCode::Serialization_InvalidFormat); // Cannot outdent past root level
    m_currentIndent--;
}

Bool Minty::TextReader::read(Any data, Size const size)
{
    return m_stream->read(data, size);
}

Bool Minty::TextReader::read_bool(Bool &value)
{
    Char buffer;
    if(!read_char(buffer))
    {
        return false;
    }
    value = buffer != 0 && buffer != '0' && buffer != 'f' && buffer != 'F';
    return true;
}

Bool Minty::TextReader::read_byte(Byte &value)
{
    UInt64 temp;
    if(!read_uint64(temp))
    {
        return false;
    }
    value = static_cast<Byte>(temp);
    return true;
}

Bool Minty::TextReader::read_char(Char &value)
{
    return read(&value, sizeof(Char));
}

Bool Minty::TextReader::read_int32(Int32 &value)
{
    Int64 temp;
    if(!read_int64(temp))
    {
        return false;
    }
    value = static_cast<Int32>(temp);
    return true;
}

Bool Minty::TextReader::read_uint32(UInt32 &value)
{
    UInt64 temp;
    if(!read_uint64(temp))
    {
        return false;
    }
    value = static_cast<UInt32>(temp);
    return true;
}

Bool Minty::TextReader::read_float32(Float32 &value)
{
    Float64 temp;
    if(!read_float64(temp))
    {
        return false;
    }
    value = static_cast<Float32>(temp);
    return true;
}

Bool Minty::TextReader::read_int64(Int64 &value)
{
    if(m_stream->end_of_stream())
    {
        return false;
    }

    StringBuilder builder;
    Char ch = m_stream->peek();
    if(ch == '-' || ch == '+')
    {
        builder.append(ch);
        m_stream->read(&ch, sizeof(Char));
    }

    read_digits(builder);

    if(builder.get_length() == 0)
    {
        return false;
    }

    return Parser<Int64>::parse(builder.GetView(), value);
}

Bool Minty::TextReader::read_uint64(UInt64 &value)
{
    if(m_stream->end_of_stream())
    {
        return false;
    }

    StringBuilder builder;
    Char ch = m_stream->peek();
    if(ch == '-' || ch == '+')
    {
        builder.append(ch);
        m_stream->read(&ch, sizeof(Char));
    }

    read_digits(builder);

    if(builder.get_length() == 0)
    {
        return false;
    }

    return Parser<UInt64>::parse(builder.GetView(), value);
}

Bool Minty::TextReader::read_float64(Float64 &value)
{
    if(m_stream->end_of_stream())
    {
        return false;
    }

    StringBuilder builder;
    Char ch = m_stream->peek();

    if(ch == '-' || ch == '+')
    {
        builder.append(ch);
        m_stream->read(&ch, sizeof(Char));
    }

    read_digits(builder);

    ch = m_stream->peek();
    if(ch == '.')
    {
        builder.append(ch);
        m_stream->read(&ch, sizeof(Char));
        read_digits(builder);
    }

    if(builder.get_length() == 0)
    {
        return false;
    }

    return Parser<Float64>::parse(builder.GetView(), value);
}

Bool Minty::TextReader::read_string(String &value)
{
    StringBuilder builder;
    Char ch = m_stream->peek();
    if (ch != '\"')
    {
        return false;
    }
    
    // Consume the opening quote
    m_stream->read(&ch, sizeof(Char));

    // Read the string until the closing quote
    while (true)
    {
        m_stream->read(&ch, sizeof(Char));

        MINTY_ASSERT(!m_stream->end_of_stream(), ErrorCode::Serialization_UnexpectedEndOfData);
        MINTY_ASSERT(ch != '\0', ErrorCode::Serialization_InvalidFormat);

        if (ch == '\\')
        {
            // Handle escape sequences
            m_stream->read(&ch, sizeof(Char));
            switch (ch)
            {
                case 'n':
                    builder.append('\n');
                    break;
                case 't':
                    builder.append('\t');
                    break;
                case 'r':
                    builder.append('\r');
                    break;
                case '\\':
                    builder.append('\\');
                    break;
                case '\"':
                    builder.append('\"');
                    break;
                default:
                    // Unknown escape sequence
                    MINTY_ABORT(ErrorCode::Serialization_InvalidFormat);
                    return false;
            }
        } else if (ch == '\"')
        {
            break;
        }
        else
        {
            builder.append(ch);
        }
    }

    value = builder.ToString();
    return true;
}

Bool Minty::TextReader::get_next_key(String &key)
{
    // If we already have a next key, return it
    if(!m_nextKey.IsEmpty())
    {
        key = m_nextKey;
        return true;
    }

    // Read the next indent and key
    StringBuilder builder;
    Char ch;
    while(!m_stream->end_of_stream())
    {
        m_stream->read(&ch, sizeof(Char));
        if(ch == ':')
        {
            m_stream->read(&ch, sizeof(Char)); // Consume the space after the colon
            MINTY_ASSERT(ch == ' ', ErrorCode::Serialization_InvalidFormat);
            break;
        } else if (ch == '\n' || ch == '\r')
        {
            ch = m_stream->peek();
            if(ch == '\n' || ch == '\r')
            {
                m_stream->read(&ch, sizeof(Char)); // Consume the second newline character
            }
            break;
        }
        else
        {
            builder.append(ch);
            break;
        }
    }
    m_nextKey = builder.ToString();
    return true;
}

Bool Minty::TextReader::check_key(StringView const key)
{
    // If no key, get the next key
    if(!has_next())
    {
        if(!get_next_key(m_nextKey))
        {
            return false;
        }
    }

    // Check if the keys match
    if(m_nextKey.GetView() != key)
    {
        return false;
    }

    // Clear the next key since it has been matched
    m_nextKey.Clear();
    return true;
}

void Minty::TextReader::read_digits(StringBuilder &builder)
{
    Size const startLength = builder.get_length();
    Char ch;
    while (!m_stream->end_of_stream())
    {
        ch = m_stream->peek();
        if (ch >= '0' && ch <= '9')
        {
            builder.append(ch);
            m_stream->read(&ch, sizeof(Char));
        }
        else
        {
            break;
        }
    }
}

Minty::Reader::Reader(Unique<Stream> &&stream)
    : m_stream(std::move(stream))
{
}
