#include "Path.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Queue.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;
using namespace Minty::Tool;

Vector<Path> Minty::Tool::get_files(Path const& path, Bool const recursive)
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

Vector<Path> Minty::Tool::get_directories(Path const& path, Bool const recursive)
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

Vector<Path> Minty::Tool::get_contents(Path const& path, Bool const recursive)
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

