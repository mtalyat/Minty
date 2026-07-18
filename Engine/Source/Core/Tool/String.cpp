#include "pch.hpp"
#include "String.hpp"
#include "Core/Debug/DebugF.hpp"

using namespace Minty;

Size Minty::Tool::find_first(Char const *const text, Size const length, Char const c, Size const startIndex) noexcept
{
    for (Size i = startIndex; i < length; ++i)
    {
        if (text[i] == c)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_first(Char const *const text, Size const length, StringView const str, Size const startIndex) noexcept
{
    if (str.get_size() == 0 || length == 0 || str.get_size() > length)
    {
        return INVALID_SIZE;
    }

    for (Size i = startIndex; i <= length - str.get_size(); ++i)
    {
        Bool match = true;
        for (Size j = 0; j < str.get_size(); ++j)
        {
            if (text[i + j] != str[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_last(Char const *const text, Size const length, Char const c, Size const startIndex) noexcept
{
    Size start = (startIndex == INVALID_SIZE || startIndex >= length) ? length - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        if (text[i] == c)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_last(Char const *const text, Size const length, StringView const str, Size const startIndex) noexcept
{
    if (str.get_size() == 0 || length == 0 || str.get_size() > length)
    {
        return INVALID_SIZE;
    }

    Size start = (startIndex == INVALID_SIZE || startIndex > length - str.get_size()) ? length - str.get_size() : startIndex;

    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        Bool match = true;
        for (Size j = 0; j < str.get_size(); ++j)
        {
            if (text[i + j] != str[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_first_of(Char const *const text, Size const length, StringView const chars, Size const startIndex) noexcept
{
    for (Size i = startIndex; i < length; ++i)
    {
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (text[i] == chars[j])
            {
                return i;
            }
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_last_of(Char const *const text, Size const length, StringView const chars, Size const startIndex) noexcept
{
    Size start = (startIndex == INVALID_SIZE || startIndex >= length) ? length - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (text[i] == chars[j])
            {
                return i;
            }
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_first_not_of(Char const *const text, Size const length, StringView const chars, Size const startIndex) noexcept
{
    for (Size i = startIndex; i < length; ++i)
    {
        Bool found = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (text[i] == chars[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Size Minty::Tool::find_last_not_of(Char const *const text, Size const length, StringView const chars, Size const startIndex) noexcept
{
    Size start = (startIndex == INVALID_SIZE || startIndex >= length) ? length - 1 : startIndex;
    for (Size i = start; i != static_cast<Size>(-1); --i)
    {
        Bool found = false;
        for (Size j = 0; j < chars.get_size(); ++j)
        {
            if (text[i] == chars[j])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return i;
        }
    }
    return INVALID_SIZE;
}

Bool Minty::Tool::starts_with(Char const *const text, Size const length, StringView const str) noexcept
{
    if (str.get_size() > length)
    {
        return false;
    }

    for (Size i = 0; i < str.get_size(); ++i)
    {
        if (text[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

Bool Minty::Tool::ends_with(Char const *const text, Size const length, StringView const str) noexcept
{
    if (str.get_size() > length)
    {
        return false;
    }

    Size offset = length - str.get_size();
    for (Size i = 0; i < str.get_size(); ++i)
    {
        if (text[offset + i] != str[i])
        {
            return false;
        }
    }
    return true;
}

Int Minty::Tool::compare(Char const *const text, Size const length, StringView const other) noexcept
{
    Size minSize = (length < other.get_size()) ? length : other.get_size();
    for (Size i = 0; i < minSize; ++i)
    {
        if (text[i] < other[i])
        {
            return -1;
        }
        else if (text[i] > other[i])
        {
            return 1;
        }
    }

    if (length < other.get_size())
    {
        return -1;
    }
    else if (length > other.get_size())
    {
        return 1;
    }
    return 0;
}

Tuple<Size, Size> Minty::Tool::find_group(StringView const str, Char const open, Char const close, Size const index)
{
	Size depth = 0;
	Size start = INVALID_SIZE;
	for (Size i = index; i < str.get_size(); i++)
	{
		Char c = str[i];
		if (c == '\\')
		{
			// escape character
			i++;
		}
		else if (c == open && (open != close || depth == 0))
		{
			if (depth == 0)
			{
				start = i;
			}
			depth++;
		}
		else if (c == close)
		{
			depth--;
			if (depth == 0)
			{
				return {start + 1, i - start - 1};
			}
		}
	}

	// not found
	return {INVALID_SIZE, INVALID_SIZE};
}

Vector<Tuple<Size, Size>> Minty::Tool::find_groups(StringView const str, Char const open, Char const close, Size const index)
{
	Vector<Tuple<Size, Size>> result;
	Size i = index;
	Tuple<Size, Size> found;
	do
	{
		found = find_group(str, open, close, i);
		if (found.get_first() != INVALID_SIZE)
		{
			result.add(found);
			i = found.get_second() + 1;
		}
		else
		{
			i = str.get_size();
		}
	} while (i < str.get_size());
	return result;
}

Vector<StringView> Minty::Tool::split_by_indices(StringView const str, Vector<Size> const &indices, Size delimiterSize)
{
	Vector<StringView> result;

	// calculate new size
	result.reserve(indices.get_size() + 1);

	// if no occurances, return the original string
	if (indices.is_empty())
	{
		result.add(str);
		return result;
	}

	// copy over data
	Size last = 0;
	for (Size i = 0; i < indices.get_size(); i++)
	{
		Size current = indices[i];
		Size length = current - last;
		result.add(str.sub(last, length));
		last = current + delimiterSize;
	}

	// copy over the rest of the data
	Size length = str.get_size() - last;
	if (length > 0)
	{
		result.add(str.sub(last, length));
	}
	return result;
}

Vector<StringView> Minty::Tool::split(StringView const str, Char const delimiter)
{
	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find_first(delimiter, index);
		if (index == INVALID_SIZE)
		{
			break;
		}
		indices.add(index);
		index += 1;
	}

	return split_by_indices(str, indices, 1);
}

Vector<StringView> Minty::Tool::split_smart(StringView const str, Char const delimiter, StringView const open, StringView const close)
{
	MINTY_ASSERT_B(open.get_size() == close.get_size(), ErrorCodeEnum::Argument_InvalidSize, open.get_size(), close.get_size());

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		Size groupIndex = INVALID_SIZE;
		Size depth = 0;
		for (; index < str.get_size(); index++)
		{
			Char c = str[index];
			if (c == '\\')
			{
				index++;
				continue;
			}
			if (depth == 0)
			{
				groupIndex = open.find_first(c);
				if (groupIndex != INVALID_SIZE)
				{
					depth++;
					continue;
				}

				if (c == delimiter)
				{
					// found a delimiter not in a group
					break;
				}
			}
			else
			{
				// in a group
				if (open.find_first(c) == groupIndex)
				{
					// entered a sub-group
					depth++;
				}
				else if (close.find_first(c) == groupIndex)
				{
					// left a sub-group
					depth--;
				}
			}
		}
		if (index == str.get_size())
		{
			break;
		}
		indices.add(index);
		index += 1;
	}

	return split_by_indices(str, indices, 1);
}

Vector<StringView> Minty::Tool::split(StringView const str, StringView const delimiter)
{
	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find_first(delimiter, index);
		if (index == INVALID_SIZE)
		{
			break;
		}
		indices.add(index);
		index += delimiter.get_size();
	}

	return split_by_indices(str, indices, delimiter.get_size());
}

Vector<StringView> Minty::Tool::split_smart(StringView const str, StringView const delimiter, StringView const open, StringView const close)
{
	MINTY_ASSERT_B(open.get_size() == close.get_size(), ErrorCodeEnum::Argument_InvalidSize, open.get_size(), close.get_size());

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		Size groupIndex = INVALID_SIZE;
		Size depth = 0;
		for (; index < str.get_size(); index++)
		{
			Char c = str[index];
			if (c == '\\')
			{
				index++;
				continue;
			}
			if (depth == 0)
			{
				groupIndex = open.find_first(c);
				if (groupIndex != INVALID_SIZE)
				{
					depth++;
					continue;
				}

				if (memcmp(&str.at(index), delimiter.get_data(), sizeof(Char) * delimiter.get_size()) == 0)
				{
					// found a delimiter not in a group
					break;
				}
			}
			else
			{
				// in a group
				if (open.find_first(c) == groupIndex)
				{
					// entered a sub-group
					depth++;
				}
				else if (close.find_first(c) == groupIndex)
				{
					// left a sub-group
					depth--;
				}
			}
		}
		if (index == str.get_size())
		{
			break;
		}
		indices.add(index);
		index += delimiter.get_size();
	}

	return split_by_indices(str, indices, delimiter.get_size());
}

Vector<StringView> Minty::Tool::split_lines(StringView const str)
{
	static StringView const LINE_DELIMITERS = "\r\n";
	Vector<StringView> result;

	// find all occurances of the delimiters, which could be \r, \n, or \r\n
	Char c;
	Size start, stop;
	Size index = 0;
	Size next;
	while(index < str.get_size())
	{
		// find first occurence of either \r or \n
		next = str.find_first_of(LINE_DELIMITERS, index);
		if (next == INVALID_SIZE)
		{
			// no more delimiters, add the rest of the string
			result.add(str.sub(index));
			break;
		}

		// add up to the delimiter
		result.add(str.sub(index, next - index));

		// add 1 if this is a \r followed by a \n, otherwise add 0
		if(str[next] == '\r' && next + 1 < str.get_size() && str[next + 1] == '\n')
		{
			next++;
		}

		// update the index
		index = next + 1;
	}

	return result;
}

String Minty::Tool::to_safe_string(StringView const str)
{
	StringBuilder builder(str);

	// escape special characters
	builder.replace("\\", "\\\\");
	builder.replace("\n", "\\n");
	builder.replace("\r", "\\r");
	builder.replace("\t", "\\t");

    return builder.get_string();
}

String Minty::Tool::to_unsafe_string(StringView const str)
{
	StringBuilder builder(str);

	// unescape special characters
	builder.replace("\\n", "\n");
	builder.replace("\\r", "\r");
	builder.replace("\\t", "\t");
	builder.replace("\\\\", "\\");

	return builder.get_string();
}
