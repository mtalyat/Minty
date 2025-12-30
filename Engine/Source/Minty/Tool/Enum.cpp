#include "Enum.h"
#include "Minty/Tool/Util.h"
#include "Minty/Data/Vector.h"
#include "Minty/Data/StringBuilder.h"

using namespace Minty;

Size Minty::Tool::parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount)
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

Bool Minty::Tool::try_parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount, Size &outValue)
{
    Size const result = parse_enum(view, enumStrings, enumCount);
    if (result < enumCount)
    {
        outValue = result;
        return true;
    }
    return false;
}

Size Minty::Tool::parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount)
{
    Vector<String> parts = Util::split(view, '|');
    Size result = 0;

    for (String const &part : parts)
    {
        String trimmedPart = part.trim();
        for (Size i = 0; i < enumCount; ++i)
        {
            if (trimmedPart == enumStrings[i])
            {
                result |= (1 << i);
                break;
            }
        }
    }

    return result;
}

Bool Minty::Tool::try_parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount, Size &outValue)
{
    Vector<String> parts = Util::split(view, '|');
    Size result = 0;
    Size i;

    for (String const &part : parts)
    {
        String trimmedPart = part.trim();
        for (i = 0; i < enumCount; ++i)
        {
            if (trimmedPart == enumStrings[i])
            {
                result |= (1 << i);
                break;
            }
        }
        if(i == enumCount)
        {
            // No matching enum found
            return false;
        }
    }

    outValue = result;
    return true;
}

String Minty::Tool::to_string_enum(Size const value, Char const *const *const enumStrings, Size const enumCount)
{
    if (value < enumCount)
    {
        return String(enumStrings[value]);
    }
    return String();
}

String Minty::Tool::to_string_enum_flags(Size const value, Char const *const *const enumStrings, Size const enumCount)
{
    StringBuilder builder;

    for (Size i = 0; i < enumCount; ++i)
    {
        if (value & (1 << i))
        {
            if (!builder.is_empty())
            {
                builder.append('|');
            }
            builder.append(enumStrings[i]);
        }
    }

    return builder.get_string();
}
