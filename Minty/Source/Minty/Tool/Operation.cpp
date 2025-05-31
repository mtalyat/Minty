#include "pch.h"
#include "Operation.h"
#include "Minty/Core/Format.h"
#include <filesystem>
#include <cstdlib>
#ifdef MINTY_WINDOWS
#include <windows.h>
#endif // MINTY_WINDOWS

namespace fs = std::filesystem;
using namespace Minty;

// gets the directory of the path
// if the path is a directory, it returns it, otherwise it gets the directory of the item
Path get_directory(Path const& path)
{
	if (path.is_empty()) return path;

	if (Path::is_directory(path))
	{
		// return this path since it is a directory
		return path;
	}
	else if (path.has_parent())
	{
		// return parent of file
		return path.get_parent();
	}
	else
	{
		// no parent, so use empty path
		return Path();
	}
}

int Minty::Operation::system_command(String const& command)
{
	return system(command.get_data());
}

void Minty::Operation::open_directory(Path const& path)
{
	Path directory = get_directory(path);

	String pathString = directory.get_string();
#ifdef MINTY_WINDOWS
	std::replace(pathString.begin(), pathString.end(), '/', '\\');
	system_command(F("start explorer \"{}\"", pathString).get_data());
#endif
}

void Minty::Operation::open(Path const& path)
{
	String pathString = path.get_string();
#ifdef MINTY_WINDOWS
	std::replace(pathString.begin(), pathString.end(), '/', '\\');
	system_command(F("start explorer \"{}\"", pathString).get_data());
#endif
}

Bool Minty::Operation::copy(Path const& from, Path const& to)
{
	Path dest;
	if (to.has_extension())
	{
		dest = to;
	}
	else
	{
		dest = to / from.get_file_name();
	}

	try {
		fs::copy(from.get_string().get_data(), dest.get_string().get_data(), std::filesystem::copy_options::overwrite_existing);
	}
	catch (std::filesystem::filesystem_error& e)
	{
		MINTY_ERROR(F("Failed to copy \"{}\" to \"{}\": \"{}\"", from.get_string(), dest.get_string(), e.what()));
		return false;
	}

	return true;
}

Bool Minty::Operation::copy_files(Path const& from, Path const& extension, Path const& to, Bool const recursive)
{
	for (auto const& entry : Path::get_directories(from, recursive))
	{
		if (extension.is_empty() || (entry.has_extension() && entry.get_extension() == extension))
		{
			if (!Operation::copy(entry, to))
			{
				return false;
			}
		}
	}

	return true;
}

Bool Minty::Operation::copy_all(Path const& from, Path const& to)
{
	try
	{
		if (!Path::exists(from))
		{
			MINTY_ERROR(F("Failed to copy_all, from \"{}\": Path does not exist.", from.get_string()));
			return false;
		}
		else if (!Path::is_directory(from))
		{
			MINTY_ERROR(F("Failed to copy_all, from \"{}\": Path is not a directory.", from.get_string()));
			return false;
		}

		// create dest if needed
		if (!Path::exists(to))
		{
			Path::create(to.get_string().get_data());
		}

		// copy over all of the files
		for (auto const& entry : Path::get_directories(from, true))
		{
			// skip non-files
			if (!Path::is_file(entry)) continue;

			Path destination = to / entry.get_relative_to(from);

			// create directory if needed
			Path directory = destination.get_parent();
			if (!Path::exists(directory))
			{
				Path::create(directory);
			}

			std::filesystem::copy(entry.get_string().get_data(), destination.get_string().get_data(), std::filesystem::copy_options::overwrite_existing);
		}
	}
	catch (std::filesystem::filesystem_error& e)
	{
		MINTY_ERROR(F("Failed to copy_all \"{}\" to \"{}\": \"{}\"", from.get_string(), to.get_string(), e.what()));
		return false;
	}
	catch (std::exception& e)
	{
		MINTY_ERROR(F("Failed to copy_all \"{}\" to \"{}\": \"{}\"", from.get_string(), to.get_string(), e.what()));
		return false;
	}

	return true;
}

Bool Minty::Operation::copy_some(Path const& from, Path const& to, Set<String> const& names)
{
	try
	{
		if (!Path::exists(from))
		{
			MINTY_ERROR(F("Failed to copy_some, from \"{}\": Path does not exist.", from.get_string()));
			return false;
		}
		else if (!Path::is_directory(from))
		{
			MINTY_ERROR(F("Failed to copy_some, from \"{}\": Path is not a directory.", from.get_string()));
			return false;
		}

		// create dest if needed
		if (!Path::exists(to))
		{
			Path::create(to);
		}

		// copy over all of the files
		for (auto const& entry : Path::get_directories(from, true))
		{
			// skip non-files
			if (!Path::is_file(entry)) continue;

			// skip any files not in names set
			if (!names.contains(entry.get_name().get_string()))
			{
				continue;
			}

			Path destination = to / entry.get_relative_to(from);

			// create directory if needed
			Path directory = destination.get_parent();
			if (!Path::exists(directory))
			{
				Path::create(directory);
			}

			std::filesystem::copy(entry.get_string().get_data(), destination.get_string().get_data(), std::filesystem::copy_options::overwrite_existing);
		}
	}
	catch (std::filesystem::filesystem_error& e)
	{
		MINTY_ERROR(F("Failed to copy_some \"{}\" to \"{}\": \"{}\"", from.get_string(), to.get_string(), e.what()));
		return false;
	}
	catch (std::exception& e)
	{
		MINTY_ERROR(F("Failed to copy_some \"{}\" to \"{}\": \"{}\"", from.get_string(), to.get_string(), e.what()));
		return false;
	}

	return true;
}

String Minty::Operation::get_environment_variable(String const& name)
{
	char* buffer = nullptr;
	Size bufferSize = 0;

	errno_t err = _dupenv_s(&buffer, &bufferSize, name.get_data());

	if (err)
	{
		MINTY_ERROR(F("Error retrieving \"{}\" environment variable.", name));

		return "";
	}
	else if (buffer == nullptr)
	{
		MINTY_ERROR(F("\"{}\" environment variable has not been set.", name));

		return "";
	}
	else {
		// variable set
		String result(buffer);

		free(buffer);

		return result;
	}
}

void Minty::Operation::set_environment_variable(String const& name, String const& value)
{
#if defined(MINTY_WINDOWS)
	String temp = F("{}={}", name, value);
	_putenv(temp.get_data());
#else
	MINTY_NOT_IMPLEMENTED();
#endif
}

Path Minty::Operation::get_minty_path()
{
	return get_environment_variable("MINTY_PATH");
}

String Minty::Operation::get_clipboard_text()
{
#if defined(MINTY_WINDOWS)
	if (!OpenClipboard(nullptr)) {
		return "";
	}

	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr) {
		CloseClipboard();
		return "";
	}

	Char* pszText = static_cast<Char*>(GlobalLock(hData));
	if (pszText == nullptr) {
		CloseClipboard();
		return "";
	}

	String text(pszText);
	GlobalUnlock(hData);
	CloseClipboard();

	return text;
#else
	MINTY_NOT_IMPLEMENTED();
#endif
}

void Minty::Operation::set_clipboard_text(String const& text)
{
#if defined(MINTY_WINDOWS)
	if (!OpenClipboard(nullptr)) {
		return;
	}

	// Empty the clipboard before setting new data
	EmptyClipboard();

	// Allocate global memory for the text
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.get_size() + 1);
	if (hMem) {
		Char* pMem = static_cast<Char*>(GlobalLock(hMem));
		if (pMem) {
			memcpy(pMem, text.get_data(), text.get_size() + 1);
			GlobalUnlock(hMem);
		}

		// Set the clipboard data
		SetClipboardData(CF_TEXT, hMem);
	}

	CloseClipboard();
#else
	MINTY_NOT_IMPLEMENTED();
#endif
}
