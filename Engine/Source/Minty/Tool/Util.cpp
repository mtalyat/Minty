#include "Util.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Queue.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;
using namespace Minty::Util;

Tuple<Size, Size> Minty::Util::find_group(String const &str, Char const open, Char const close, Size const index)
{
	Size depth = 0;
	Size start = INVALID_INDEX;
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
	return {INVALID_INDEX, INVALID_INDEX};
}

Vector<Tuple<Size, Size>> Minty::Util::find_groups(String const &str, Char const open, Char const close, Size const index)
{
	Vector<Tuple<Size, Size>> result;
	Size i = index;
	Tuple<Size, Size> found;
	do
	{
		found = find_group(str, open, close, i);
		if (found.get_first() != INVALID_INDEX)
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

Vector<String> Minty::Util::split_by_indices(String const &str, Vector<Size> const &indices, Size delimiterSize)
{
	Vector<String> result;

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

Vector<String> Minty::Util::split(String const &str, Char const delimiter)
{
	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find_first(delimiter, index);
		if (index == INVALID_INDEX)
		{
			break;
		}
		indices.add(index);
		index += 1;
	}

	return split_by_indices(str, indices, 1);
}

Vector<String> Minty::Util::split_smart(String const &str, Char const delimiter, String const &open, String const &close)
{
	MINTY_ASSERT_F(open.get_size() == close.get_size(), ErrorCode::Argument_InvalidSize, open.get_size(), close.get_size());

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		Size groupIndex = INVALID_INDEX;
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
				if (groupIndex != INVALID_INDEX)
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

Vector<String> Minty::Util::split(String const &str, String const &delimiter)
{
	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = str.find_first(delimiter, index);
		if (index == INVALID_INDEX)
		{
			break;
		}
		indices.add(index);
		index += delimiter.get_size();
	}

	return split_by_indices(str, indices, delimiter.get_size());
}

Vector<String> Minty::Util::split_smart(String const &str, String const &delimiter, String const &open, String const &close)
{
	MINTY_ASSERT_F(open.get_size() == close.get_size(), ErrorCode::Argument_InvalidSize, open.get_size(), close.get_size());

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		Size groupIndex = INVALID_INDEX;
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
				if (groupIndex != INVALID_INDEX)
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

Vector<String> Minty::Util::split(String const &str)
{
	String copy = str.replace("\r\n", "\n");

	// find all occurances of the delimiter
	Vector<Size> indices;
	Size index = 0;
	while (true)
	{
		index = copy.find_first_of(TEXT_WHITESPACE, index);
		if (index == INVALID_INDEX)
		{
			break;
		}
		indices.add(index);
		index += 1; // 1 character delimiter
	}

	return split_by_indices(copy, indices, 1);
}

Vector<String> Minty::Util::split_lines(String const &str)
{
	return split(str.replace("\r\n", "\n"), '\n');
}

String Minty::Util::to_safe_string(StringView const str)
{
	StringBuilder builder(str);

	// escape special characters
	builder.replace("\\", "\\\\");
	builder.replace("\n", "\\n");
	builder.replace("\r", "\\r");
	builder.replace("\t", "\\t");

    return builder.get_string();
}

String Minty::Util::to_unsafe_string(StringView const str)
{
	StringBuilder builder(str);

	// unescape special characters
	builder.replace("\\n", "\n");
	builder.replace("\\r", "\r");
	builder.replace("\\t", "\t");
	builder.replace("\\\\", "\\");

	return builder.get_string();
}

Vector<Path> Minty::Util::get_files(Path const& path, Bool const recursive)
{
	MINTY_ASSERT(Path::exists(path), ErrorCode::File_NotFound);
	MINTY_ASSERT(Path::is_directory(path), ErrorCode::File_NotADirectory);

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : std::filesystem::directory_iterator(std::filesystem::path(current.get_string().get_data())))
		{
			if (entry.is_regular_file())
			{
				paths.add(Path(entry.path().string().data()));
			}
			else if (recursive && entry.is_directory())
			{
				directoriesToCheck.push(Path(entry.path().string().data()));
			}
		}
	}
	
	return paths;
}

Vector<Path> Minty::Util::get_directories(Path const& path, Bool const recursive)
{
	MINTY_ASSERT(Path::exists(path), ErrorCode::File_NotFound);
	MINTY_ASSERT(Path::is_directory(path), ErrorCode::File_NotADirectory);

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : std::filesystem::directory_iterator(std::filesystem::path(current.get_string().get_data())))
		{
			if (entry.is_directory())
			{
				Path entryPath = Path(entry.path().string().data());
				paths.add(entryPath);

				if (recursive)
				{
					directoriesToCheck.push(entryPath);
				}
			}
		}
	}

	return paths;
}

Vector<Path> Minty::Util::get_contents(Path const& path, Bool const recursive)
{
	MINTY_ASSERT(Path::exists(path), ErrorCode::File_NotFound);
	MINTY_ASSERT(Path::is_directory(path), ErrorCode::File_NotADirectory);

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : std::filesystem::directory_iterator(std::filesystem::path(current.get_string().get_data())))
		{
			if (entry.is_regular_file())
			{
				paths.add(Path(entry.path().string().data()));
			}
			else if (entry.is_directory())
			{
				Path entryPath = Path(entry.path().string().data());
				paths.add(entryPath);

				if (recursive)
				{
					directoriesToCheck.push(entryPath);
				}
			}
		}
	}

	return paths;
}

