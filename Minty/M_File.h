#pragma once

#include "M_Main.h"
#include <string>
#include <vector>
#include <map>

namespace minty
{
	/// <summary>
	/// Gets all of the text from the file at the given path.
	/// </summary>
	/// <param name="path">The path to read the file from.</param>
	/// <returns>The text from the file.</returns>
	MINTY_API std::string* file_readAllText(std::string const& path);

	/// <summary>
	/// Gets all of the lines of text from the file at the given path.
	/// </summary>
	/// <param name="path">The path to read the file from.</param>
	/// <returns>The lines from the file.</returns>
	MINTY_API std::vector<std::string>* file_readAllLines(std::string const& path);

	/// <summary>
	/// Reads all of the data from the CSV file at the given path.
	/// </summary>
	/// <param name="path">The path to read the file from.</param>
	/// <returns>The CSV data from the file.</returns>
	MINTY_API std::vector<std::vector<std::string>>* file_readAllCSV(std::string const& path);

	/// <summary>
	/// Checks if there is a file at the given path.
	/// </summary>
	/// <param name="path">The path to read the file from.</param>
	/// <returns>True if the file exists.</returns>
	MINTY_API bool file_exists(std::string const& path);

	/// <summary>
	/// Writes all of the given text to a file at the given path.
	/// </summary>
	/// <param name="path">The path to write the data to.</param>
	/// <param name="text">The text to write.</param>
	/// <returns>True if the file was written to.</returns>
	MINTY_API bool file_writeAllText(std::string const& path, std::string const& text);

	/// <summary>
	/// Writes all of the given lines to a file at the given path.
	/// </summary>
	/// <param name="path">The path to write the data to.</param>
	/// <param name="lines"></param>
	/// <returns>True if the file was written to.</returns>
	MINTY_API bool file_writeAllLines(std::string const& path, std::vector<std::string>* const lines);
}