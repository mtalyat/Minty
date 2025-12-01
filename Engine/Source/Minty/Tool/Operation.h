#ifndef MINTY_TOOL_OPERATION_H
#define MINTY_TOOL_OPERATION_H

/**
 * @file Operation.h
 * @brief Header file defining the Operation namespace.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Set.h"

namespace Minty
{
	/**
	 * @brief Contains functions that perform various tasks on the current operating system.
	 */
	namespace Operation
	{
		/**
		 * @brief Runs a system command and returns the result code.
		 * @param command The command to run.
		 * @return The error code from the command.
		 */
		Int system_command(String const& command);

		/**
		 * @brief Opens the directory at the given path.
		 * @param path The path to the directory to open.
		 */
		void open_directory(Path const& path);

		/**
		 * @brief Opens the file or directory at the given path.
		 * @param path The path to the file or directory.
		 */
		void open(Path const& path);

		/**
		 * @brief Copies the file to the target folder/file path.
		 * @param from The source path.
		 * @param to The destination path.
		 * @return True on success.
		 */
		Bool copy(Path const& from, Path const& to);

		/**
		 * @brief Copies all of the files with the given extension to the target path.
		 * @param from The source path.
		 * @param extension The type of extension to copy.
		 * @param to The destination path.
		 * @param recursive If true, copy files recursively.
		 * @return True on success.
		 */
		Bool copy_files(Path const& from, Path const& extension, Path const& to, Bool const recursive = false);

		/**
		 * @brief Copies all of the files and directories to the target path.
		 * @param from The source path.
		 * @param to The destination path.
		 * @return True on success.
		 */
		Bool copy_all(Path const& from, Path const& to);

		/**
		 * @brief Copies all of the files that are included in the names set.
		 * @param from The source path.
		 * @param to The destination path.
		 * @param names The names of the files to copy.
		 * @return True on success.
		 */
		Bool copy_some(Path const& from, Path const& to, Set<String> const& names);

		/**
		 * @brief Gets the environment variable, if it has been set.
		 * @param name The name of the environment variable.
		 * @return The value of the environment variable.
		 */
		String get_environment_variable(String const& name);

		/**
		 * @brief Sets the environment variable to the given String.
		 * @param name The name of the environment variable.
		 * @param value The value of the environment variable./param>
		 */
		void set_environment_variable(String const& name, String const& value);

		/**
		 * @brief Gets the MINTY_PATH environment variable.
		 * @return The path to the root Minty directory.
		 */
		Path get_minty_path();

		/**
		 * @brief Gets the clipboard text.
		 * @return The text stored within the clipboard.
		 */
		String get_clipboard_text();

		/**
		 * @brief Sets the clipboard text to the given String.
		 * @param text The text to set the clipboard to.
		 */
		void set_clipboard_text(String const& text);
	}
}

#endif // MINTY_TOOL_OPERATION_H