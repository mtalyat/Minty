#pragma once

#include "M_Main.h"
#include <string>
#include <vector>

namespace minty
{
	/// <summary>
	/// Gets all of the text from the file at the given path.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	MINTY_API std::string* file_readAllText(std::string const& path);

	/// <summary>
	/// Gets all of the lines of text from the file at the given path.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	MINTY_API std::vector<std::string>* file_readAllLines(std::string const& path);

	/// <summary>
	/// Reads all of the data from the CSV file at the given path.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	MINTY_API std::vector<std::vector<std::string>>* file_readAllCSV(std::string const& path);

	/// <summary>
	/// Checks if there is a file at the given path.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	MINTY_API bool file_exists(std::string const& path);
}