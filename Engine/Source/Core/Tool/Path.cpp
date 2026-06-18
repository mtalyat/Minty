#include "pch.h"
#include "Path.h"
#include "Core/Data/Queue.h"
#include "Core/Debug/DebugF.h"

using namespace Minty;

Vector<Path> Minty::Tool::get_files(Path const &path, Bool const recursive)
{
    MINTY_ASSERT_B(Path::exists(path), ErrorCodeEnum::File_NotFound, path);
	MINTY_ASSERT_B(Path::is_directory(path), ErrorCodeEnum::File_NotADirectory, path);

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : current.get_directory_iterator())
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

Vector<Path> Minty::Tool::get_directories(Path const &path, Bool const recursive)
{
    MINTY_ASSERT_B(Path::exists(path), ErrorCodeEnum::File_NotFound, path);
	MINTY_ASSERT_B(Path::is_directory(path), ErrorCodeEnum::File_NotADirectory, path);

	Vector<Path> paths;
	Queue<Path> directoriesToCheck;
	directoriesToCheck.push(path);

	while (!directoriesToCheck.is_empty())
	{
		Path current = directoriesToCheck.pop();
		for (auto const& entry : current.get_directory_iterator())
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
