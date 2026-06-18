#include "pch.h"
#include "Enum.h"
#include "String.h"
#include "Core/Data/Vector.h"
#include "Core/Data/StringBuilder.h"

using namespace Minty;

Size Minty::Internal::parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount)
{
    for (Size i = 0; i < enumCount; ++i)
    {
        if (view == enumStrings[i])
        {
            return i;
        }
    }
    return enumCount;
}

Bool Minty::Internal::try_parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount, Size &outValue)
{
    Size const result = parse_enum(view, enumStrings, enumCount);
    if (result < enumCount)
    {
        outValue = result;
        return true;
    }
    return false;
}

Size Minty::Internal::parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount)
{
    Vector<StringView> parts = Tool::split(view, '|');
    Size result = 0;

    for (StringView const &part : parts)
    {
        String trimmedPart = String(part).trim();
        for (Size i = 1; i < enumCount; ++i)
        {
            if (trimmedPart == enumStrings[i])
            {
                result |= (1ull << (i - 1)); // add 1 to skip "Undefined" entry
                break;
            }
        }
    }

    return result;
}

Bool Minty::Internal::try_parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount, Size &outValue)
{
    Size result = 0;
    Size index = 0;
    Size i;

    // iterate until a part is found
    while (index < view.get_size())
    {
        for (i = index; i < view.get_size(); ++i)
        {
            Char const c = view[i];

            if (i > index)
            {
                // break on delimiter
                if (c == ' ' || c == '|' || isupper(c))
                {
                    break;
                }
            }
            else
            {
                // skip leading spaces or delimiters
                if (c == ' ' || c == '|')
                {
                    ++index;
                    continue;
                }
            }
        }

        // get the part
        StringView const part = view.sub(index, i - index);
        
        // move on to the next part
        index = i;

        // find the matching enum value
        for (i = 1; i < enumCount; ++i)
        {
            if (part == enumStrings[i])
            {
                result |= (1ull << (i - 1)); // add 1 to skip "Undefined" entry
                break;
            }
        }

        // if no match was found, return false
        if (i == enumCount)
        {
            return false;
        }
    }

    outValue = result;
    return true;
}

String Minty::Internal::to_string_enum(Size const value, Char const *const *const enumStrings, Size const enumCount)
{
    if (value < enumCount)
    {
        return String(enumStrings[value]);
    }
    return String();
}

String Minty::Internal::to_string_enum_flags(Size const value, Char const *const *const enumStrings, Size const enumCount)
{
    StringBuilder builder;

    for (Size i = 0; i < enumCount; ++i)
    {
        if (value & (1ull << i))
        {
            if (!builder.is_empty())
            {
                builder.append('|');
            }
            builder.append(enumStrings[i + 1]); // add 1 to skip "Undefined" entry
        }
    }

    return builder.get_string();
}
