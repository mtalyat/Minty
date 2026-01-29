#include "pch.h"
#include "TextReader.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Tool/String.h"
#include "Minty/Serialization/EvaluatedTypes.h"

using namespace Minty;

Minty::TextReader::TextReader(Shared<Stream> const &stream)
    : Reader(stream), m_nextKey(), m_nextIndent(0), m_hasNextKey(false), m_hasNextValue(false)
{
}

Minty::TextReader::~TextReader()
{
    do
    {
        // skip any remaining data at the current indent level
        skip_remaining();

        // break if at root level
        if (get_indent() == 0)
        {
            break;
        }

        // check the next level down
        outdent();
    } while (true);
}

Bool Minty::TextReader::read_bool(Bool *const value)
{
    Char buffer;
    if (!read_char(&buffer))
    {
        return false;
    }
    *value = buffer != 0 && buffer != '0' && buffer != 'f' && buffer != 'F';
    return true;
}

Bool Minty::TextReader::read_byte(Byte *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<Byte>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_char(Char *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = temp.front();
    return true;
}

Bool Minty::TextReader::read_int32(Int32 *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<Int32>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_uint32(UInt32 *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<UInt32>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_float32(Float32 *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<Float32>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_int64(Int64 *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<Int64>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_uint64(UInt64 *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<UInt64>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_float64(Float64 *const value)
{
    String temp;
    if (!read_raw_value(temp))
    {
        return false;
    }
    *value = Evaluator<Float64>::evaluate(temp);
    return true;
}

Bool Minty::TextReader::read_tuple(Any const buffer, Size const elementSize, UInt const count, Function<Bool(Any)> const &readFunc)
{
    Char openingBracket;
    if (!peek(openingBracket) || (openingBracket != '[' && openingBracket != '('))
    {
        MINTY_ERROR(ErrorCode::Serialization_InvalidFormat);
        return false;
    }

    // Consume the opening bracket
    read_from_stream(&openingBracket, sizeof(Char));

    // Get the corresponding closing bracket
    Char const closingBracket = (openingBracket == '[') ? ']' : ')';

    // Read each element, separated by commas
    for (UInt i = 0; i < count; ++i)
    {
        // Skip whitespace
        Char ch;
        while (peek(ch) && (ch == ' ' || ch == '\t'))
        {
            read_from_stream(&ch, sizeof(Char));
        }

        // Read the element
        Any const elementPtr = static_cast<Byte*>(buffer) + (i * elementSize);
        if (!readFunc(elementPtr))
        {
            return false;
        }

        // If not the last element, expect a comma
        if (i < count - 1)
        {
            if (!peek(ch) || ch != ',')
            {
                MINTY_ERROR(ErrorCode::Serialization_InvalidFormat);
                return false;
            }
            // Consume the comma
            read_from_stream(&ch, sizeof(Char));
        }
    }

    // Check for the closing bracket
    Char closingChar;
    if (!peek(closingChar) || closingChar != closingBracket)
    {
        MINTY_ERROR(ErrorCode::Serialization_InvalidFormat);
        return false;
    }

    // Consume the closing bracket
    read_from_stream(&closingChar, sizeof(Char));

    return true;
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

    value = Tool::to_unsafe_string(builder.get_view());
    return true;
}

Bool Minty::TextReader::read_raw_value(String &value, Bool const ignoreSeparator)
{
    StringBuilder builder;

    // Read until the end of the line, a comment, or a separator
    Char ch;
    while (peek(ch) && ch != '\n' && ch != '\r' && (ignoreSeparator || ch != ','))
    {
        // if there is a comment here, stop reading, the line is done
        if (check_for_comment())
        {
            break;
        }

        builder.append(ch);
        read_from_stream(&ch, sizeof(Char));
    }

    // remove any trailing whitespace
    Size index = builder.find_last_not_of(" \t");
    if (index != INVALID_INDEX && index + 1 < builder.get_length())
    {
        builder.slice(0, index + 1);
    }
    value = builder.get_string();
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
    UInt const currentIndent = get_indent();

    // If we already have a next key, return it
    if (m_hasNextKey)
    {
        key = m_nextKey;
        return m_nextIndent == currentIndent;
    }

    // Unset the next key and value flags
    // Key already false due to the above check
    // Must force value consumption, since this is a new key being read
    consume_next_value(true);

    // Read until we find a key on the same indentation level
    // If higher: skip
    // If lower: return false (no more keys at this level)
    StringBuilder builder;
    Char ch;
    UInt indentLevel;
    while (true)
    {
        // Remove file UUID if found
        if(peek(ch) && ch == ':')
        {
            skip_line();
            continue;
        }
        
        // Count indentation
        if(!check_for_indentation(indentLevel))
        {
            indentLevel = 0;
        }

        // If we reached a newline, continue to the next line
        if (check_for_break())
        {
            continue;
        }

        // check for a comment, and skip it if found and move to next line
        if (check_for_comment())
        {
            continue;
        }

        // reset variables for reuse
        builder.clear();

        // If the indent level is equal to the current, we have a key
        if (indentLevel <= currentIndent)
        {
            // If the next character is a '-', the name is empty (list item)
            if (peek(ch) && ch == '-')
            {
                read_from_stream(&ch, sizeof(Char));
                if (peek(ch) && ch == ' ')
                {
                    read_from_stream(&ch, sizeof(Char));
                }

                // return empty key
                key = String();
                m_nextKey = key;
                m_nextIndent = indentLevel;
                m_hasNextKey = true;

                // we know there is a value if there is something after the '- '
                m_hasNextValue = peek(ch) && ch != '\n' && ch != '\r';

                return indentLevel == currentIndent;
            }

            // Read the key until we hit a colon or unexpected whitespace
            while (peek(ch) && ch != ':' && ch != '\t' && ch != '\n' && ch != '\r')
            {
                builder.append(ch);
                read_from_stream(&ch, sizeof(Char));
            }

            // If no key found, return false
            if (builder.is_empty())
            {
                return false;
            }

            // return the key
            key = builder.get_string();
            m_nextKey = key;
            m_nextIndent = indentLevel;
            m_hasNextKey = true;

            // consume the ": " if present, which indicates a value
            m_hasNextValue = false;
            if (peek(ch) && ch == ':')
            {
                read_from_stream(&ch, sizeof(Char));
                if (peek(ch) && ch == ' ')
                {
                    read_from_stream(&ch, sizeof(Char));
                }
                m_hasNextValue = true;
            }

            return indentLevel == currentIndent;
        }
        else
        {
            // Skip this line
            // This is child data, but since indent wasn't called, this data is ignored
            skip_line();
        }
    }
}

Bool Minty::TextReader::check_key(StringView const key)
{
    // If no key, get the next key
    if (!m_hasNextKey)
    {
        if (!get_next_key(m_nextKey))
        {
            // No next key
            return false;
        }
    }
    // Check if the keys match
    return m_nextKey.get_view() == key;
}

Bool Minty::TextReader::consume_next_key()
{
    // consume (clear) the next key since it has been processed
    Bool const consumed = m_hasNextKey;
    m_nextKey = String();
    m_hasNextKey = false;
    return consumed;
}

Bool Minty::TextReader::consume_next_value(Bool const force)
{
    // if there is a value, skip it
    // the indent must be a lesser or equal level to consume it (same level or parent level)
    if (m_hasNextValue && (force || m_nextIndent == get_indent()))
    {
        Char ch;
        while (peek(ch) && ch != '\n' && ch != '\r')
        {
            read_from_stream(&ch, sizeof(Char));
        }
        m_hasNextValue = false;
        return true;
    }
    return false;
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

Bool Minty::TextReader::check_for_comment()
{
    Char ch;
    if (peek(ch) && ch == '#')
    {
        // skip the entire line
        skip_line();
        return true;
    }
    return false;
}

Bool Minty::TextReader::check_for_indentation(UInt &indentLevel)
{
    Char ch;
    Bool usedTabs = false;
    Bool usedSpaces = false;

    if (!peek(ch))
    {
        return false;
    }

    if (ch != ' ' && ch != '\t')
    {
        return false;
    }

    indentLevel = 0;
    while (peek(ch) && (ch == ' ' || ch == '\t'))
    {
        indentLevel++;
        read_from_stream(&ch, sizeof(Char));
        if (ch == ' ')
        {
            usedSpaces = true;
        }
        else if (ch == '\t')
        {
            usedTabs = true;
        }
    }

    MINTY_CHECK(!(usedTabs && usedSpaces), ErrorCode::Serialization_InconsistentIndentation); // Cannot mix tabs and spaces for indentation
    if (usedSpaces)
    {
        // if used spaces, each indent level is 4 spaces
        MINTY_CHECK(indentLevel % 4 == 0, ErrorCode::Serialization_InconsistentIndentation); // Indentation level must be a multiple of 4 when using spaces
        indentLevel /= 4;
    }

    return true;
}

Bool Minty::TextReader::check_for_break()
{
    Char ch;
    if(peek(ch) && (ch == '\n' || ch == '\r'))
    {
        read_from_stream(&ch, sizeof(Char));
        return true;
    }
    return false;
}

void Minty::TextReader::skip_line()
{
    Char ch;
    while (peek(ch) && ch != '\n' && ch != '\r')
    {
        read_from_stream(&ch, sizeof(Char));
    }
}

void Minty::TextReader::skip_remaining()
{
    if (m_hasNextKey && m_nextIndent == get_indent())
    {
        do
        {
            // warn if there are unread keys at the current level
            // those unread keys either need to be read, or should be removed
            MINTY_WARNING_F(ErrorCode::Serialization_IgnoredData, get_indent(), m_nextKey);

            // skip the key and value (if present)
            consume_next_key();
            consume_next_value();
        } while (get_next_key(m_nextKey));
    }
}
