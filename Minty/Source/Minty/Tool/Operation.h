#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Set.h"

namespace Minty
{
	/// <summary>
	/// Contains functions that perform various tasks on the current operating system.
	/// </summary>
	namespace Operation
	{
		/// <summary>
		/// Runs a system command and returns the result code.
		/// </summary>
		/// <param name="command">The command to run.</param>
		/// <returns>The error code from the command.</returns>
		Int system_command(String const& command);

		/// <summary>
		/// Opens the directory at the given path.
		/// </summary>
		/// <param name="path">The path to the directory to open.</param>
		void open_directory(Path const& path);

		/// <summary>
		/// Opens the file or directory at the given path.
		/// </summary>
		/// <param name="path">The path to the file or directory.</param>
		void open(Path const& path);

		/// <summary>
		/// Copies the file to the target folder/file path.
		/// </summary>
		/// <param name="from">The source path.</param>
		/// <param name="to">The destination path.</param>
		/// <returns>True on success.</returns>
		Bool copy(Path const& from, Path const& to);

		/// <summary>
		/// Copies all of the files with the given extension to the target path.
		/// </summary>
		/// <param name="from">The source path.</param>
		/// <param name="extension">The type of extension to copy.</param>
		/// <param name="to">The destination path.</param>
		/// <param name="recursive">If true, copy files recursively.</param>
		/// <returns>True on success.</returns>
		Bool copy_files(Path const& from, Path const& extension, Path const& to, Bool const recursive = false);

		/// <summary>
		/// Copies all of the files and directories to the target path.
		/// </summary>
		/// <param name="from">The source path.</param>
		/// <param name="to">The destination path.</param>
		/// <returns>True on success.</returns>
		Bool copy_all(Path const& from, Path const& to);

		/// <summary>
		/// Copies all of the files that are included in the names set.
		/// </summary>
		/// <param name="from">The source path.</param>
		/// <param name="to">The destination path.</param>
		/// <param name="names">The names of the files to copy.</param>
		/// <returns>True on success.</returns>
		Bool copy_some(Path const& from, Path const& to, Set<String> const& names);

		/// <summary>
		/// Gets the environment variable, if it has been set.
		/// </summary>
		/// <param name="name">The name of the environment variable.</param>
		/// <returns>The value of the environment variable.</returns>
		String get_environment_variable(String const& name);

		/// <summary>
		/// Sets the environment variable to the given String.
		/// </summary>
		/// <param name="name">The name of the environment variable.</param>
		/// <param name="value">The value of the environment variable./param>
		void set_environment_variable(String const& name, String const& value);

		/// <summary>
		/// Gets the MINTY_PATH environment variable.
		/// </summary>
		/// <returns>The path to the root Minty directory.</returns>
		Path get_minty_path();

		/// <summary>
		/// Gets the clipboard text.
		/// </summary>
		/// <returns>The text stored within the clipboard.</returns>
		String get_clipboard_text();

		/// <summary>
		/// Sets the clipboard text to the given String.
		/// </summary>
		/// <param name="text">The text to set the clipboard to.</param>
		void set_clipboard_text(String const& text);
	}
}