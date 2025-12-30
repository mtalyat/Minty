#include "pch.h"
#include "TextReader.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Tool/Util.h"

using namespace Minty;

Minty::TextReader::TextReader(Shared<Stream> const &stream)
    : Reader(stream), m_nextKey(), m_nextIndent(0), m_currentIndent(0)
{
}

Bool Minty::TextReader::indent()
{
    // Get the next key and indent level
    if (!has_next())
    {
        if (!get_next_key(m_nextKey))
        {
            return false;
        }
    }

    // If the next indent is greater than the current, indent
    if (m_nextIndent > m_currentIndent)
    {
        MINTY_ASSERT(m_nextIndent == m_currentIndent + 1, ErrorCode::Serialization_InvalidFormat); // Cannot indent more than one level at a time
        m_currentIndent = m_nextIndent;
        return true;
    }
    return false;
}

Bool Minty::TextReader::indent(StringView const key)
{
    // Get the next key and indent level
    if (!has_next())
    {
        if (!get_next_key(m_nextKey))
        {
            return false;
        }
    }

    // If the keys match and the next indent is greater than the current, indent
    if (m_nextKey.get_view() == key && m_nextIndent > m_currentIndent)
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

    // when outdenting in debug mode, warn if there are unread keys at the current level
    // those unread keys either need to be read, or should be removed
#ifdef MINTY_DEBUG

    if (has_next() && m_nextIndent == m_currentIndent)
    {
        do
        {
            MINTY_LOG_WARNING_F("TextReader ignoring key \"{}\" at indentation level {}.", m_nextKey, m_currentIndent);
            m_nextKey = String();
        } while (get_next_key(m_nextKey));
    }

#endif // MINTY_DEBUG

    m_currentIndent--;
}

Handle Minty::TextReader::save_bookmark()
{
    StreamPosition const position = get_stream()->get_position();
    Handle const bookmark = static_cast<Handle>(m_bookmarks.get_size());
    m_bookmarks.add(bookmark, { position, m_currentIndent });
    return bookmark;
}

void Minty::TextReader::load_bookmark(Handle const bookmark)
{
    MINTY_ASSERT_F(m_bookmarks.contains(bookmark), ErrorCode::Serialization_InvalidBookmark, bookmark);
    Tuple<StreamPosition, UInt> const &data = m_bookmarks[bookmark];
    get_stream()->set_position(data.get_first());
    m_currentIndent = data.get_second();

    // invalidate the next key, so it will be read again
    m_nextKey = String();
    m_nextIndent = 0;
}

Bool Minty::TextReader::read_bool(Bool &value)
{
    Char buffer;
    if (!read_char(buffer))
    {
        return false;
    }
    value = buffer != 0 && buffer != '0' && buffer != 'f' && buffer != 'F';
    return true;
}

Bool Minty::TextReader::read_byte(Byte &value)
{
    UInt64 temp;
    if (!read_uint64(temp))
    {
        return false;
    }
    value = static_cast<Byte>(temp);
    return true;
}

Bool Minty::TextReader::read_char(Char &value)
{
    return read_from_stream(&value, sizeof(Char));
}

Bool Minty::TextReader::read_int32(Int32 &value)
{
    Int64 temp;
    if (!read_int64(temp))
    {
        return false;
    }
    value = static_cast<Int32>(temp);
    return true;
}

Bool Minty::TextReader::read_uint32(UInt32 &value)
{
    UInt64 temp;
    if (!read_uint64(temp))
    {
        return false;
    }
    value = static_cast<UInt32>(temp);
    return true;
}

Bool Minty::TextReader::read_float32(Float32 &value)
{
    Float64 temp;
    if (!read_float64(temp))
    {
        return false;
    }
    value = static_cast<Float32>(temp);
    return true;
}

Bool Minty::TextReader::read_int64(Int64 &value)
{
    StringBuilder builder;
    Char ch;
    if (peek(ch) && (ch == '-' || ch == '+'))
    {
        builder.append(ch);
        read_from_stream(&ch, sizeof(Char));
    }

    read_digits(builder);

    if (builder.get_length() == 0)
    {
        return false;
    }

    return Parser<Int64>::parse(builder.get_view(), value);
}

Bool Minty::TextReader::read_uint64(UInt64 &value)
{
    StringBuilder builder;
    Char ch;
    if (peek(ch) && (ch == '-' || ch == '+'))
    {
        builder.append(ch);
        read_from_stream(&ch, sizeof(Char));
    }

    read_digits(builder);

    if (builder.get_length() == 0)
    {
        return false;
    }

    return Parser<UInt64>::parse(builder.get_view(), value);
}

Bool Minty::TextReader::read_float64(Float64 &value)
{
    StringBuilder builder;
    Char ch;
    if (peek(ch) && (ch == '-' || ch == '+'))
    {
        builder.append(ch);
        read_from_stream(&ch, sizeof(Char));
    }

    read_digits(builder);

    if (peek(ch) && ch == '.')
    {
        builder.append(ch);
        read_from_stream(&ch, sizeof(Char));
        read_digits(builder);
    }

    if (builder.get_length() == 0)
    {
        return false;
    }

    return Parser<Float64>::parse(builder.get_view(), value);
}

Bool Minty::TextReader::read_string(String &value)
{
    StringBuilder builder;
    Char ch;
    if (!peek(ch) || ch != '\"')
    {
        return false;
    }

    // Consume the opening quote
    read_from_stream(&ch, sizeof(Char));

    // Read the string until the closing quote
    while (true)
    {
        if (!read_from_stream(&ch, sizeof(Char)))
        {
            return false;
        }

        MINTY_ASSERT(ch != '\0', ErrorCode::Serialization_UnexpectedEndOfData);

        if (ch == '\"')
        {
            // found the closing quote
            break;
        }
        else
        {
            // keep building the string
            builder.append(ch);
        }
    }

    value = Util::to_unsafe_string(builder.get_view());
    return true;
}

Bool Minty::TextReader::read_type_value_pair(Type &type, Any data)
{
    StringBuilder builder;

    // Read the type until we hit a colon or unexpected whitespace
    Char ch;
    while (peek(ch) && ch != ':' && ch != '\t' && ch != '\n' && ch != '\r')
    {
        builder.append(ch);
        read_from_stream(&ch, sizeof(Char));
    }

    StringView const typeString = builder.get_view();
    if (!Parser<Type>::parse(typeString, type))
    {
        return false;
    }

    // Consume the separator
    if (!peek(ch) || ch != ':')
    {
        return false;
    }
    read_from_stream(&ch, sizeof(Char));
    if (!peek(ch) || ch != ' ')
    {
        return false;
    }
    read_from_stream(&ch, sizeof(Char));

    // Read the value
    return read_typed_value(type, data);
}

Bool Minty::TextReader::get_next_key(String &key)
{
    // If we already have a next key, return it
    if (!m_nextKey.is_empty())
    {
        key = m_nextKey;
        return true;
    }

    // Read until we find a key on the same indentation level
    // If higher: skip
    // If lower: return false (no more keys at this level)
    while (true)
    {
        StringBuilder builder;
        Char ch;
        UInt indentLevel = 0;

        // Count indentation
        while (peek(ch) && (ch == ' ' || ch == '\t'))
        {
            indentLevel++;
            read_from_stream(&ch, sizeof(Char));
        }

        // If we reached end of stream, return false
        if (!peek(ch))
        {
            return false;
        }

        // If we reached a newline, skip it
        if (ch == '\n' || ch == '\r')
        {
            read_from_stream(&ch, sizeof(Char));
            continue;
        }

        // If the indent level is equal to the current, we have a key
        if (indentLevel <= m_currentIndent)
        {
            // Read the key until we hit a colon or unexpected whitespace
            while (peek(ch) && ch != ':' && ch != '\t' && ch != '\n' && ch != '\r')
            {
                builder.append(ch);
                read_from_stream(&ch, sizeof(Char));
            }

            key = builder.get_string();
            m_nextKey = key;
            m_nextIndent = indentLevel;
            return indentLevel == m_currentIndent;
        }
        else
        {
            // Skip this line
            // This is child data, but since indent wasn't called, this data is ignored
            while (read_from_stream(&ch, sizeof(Char)) && ch != '\n' && ch != '\r')
            {
                // skip
            }
        }
    }
}

Bool Minty::TextReader::check_key(StringView const key)
{
    // If no key, get the next key
    if (!has_next())
    {
        if (!get_next_key(m_nextKey))
        {
            // No next key
            return false;
        }
    }

    // Check if the keys match
    if (m_nextKey.get_view() != key)
    {
        return false;
    }

    // Consume (clear) the next key since it has been matched
    m_nextKey = String();
    return true;
}

void Minty::TextReader::read_digits(StringBuilder &builder)
{
    Size const startLength = builder.get_length();
    Char ch;
    while (peek(ch))
    {
        if (ch >= '0' && ch <= '9')
        {
            builder.append(ch);
            read_from_stream(&ch, sizeof(Char));
        }
        else
        {
            break;
        }
    }
}
