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

	/// <summary>
	/// Reads each line as an element of a map.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="separator"></param>
	/// <returns></returns>
	MINTY_API std::map<std::string, std::string>* file_readMap(std::string const& path, char const separator = ':');

	/// <summary>
	/// Writes all of the given text to a file at the given path.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="text"></param>
	/// <returns></returns>
	MINTY_API bool file_writeAllText(std::string const& path, std::string const& text);

	/// <summary>
	/// Writes all of the given lines to a file at the given path.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="lines"></param>
	/// <returns></returns>
	MINTY_API bool file_writeAllLines(std::string const& path, std::vector<std::string>* const lines);

	/// <summary>
	/// Writes each key value pair in the given map to a line of a file.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="map"></param>
	/// <param name="separator"></param>
	/// <returns></returns>
	MINTY_API bool file_writeMap(std::string const& path, std::map<std::string, std::string>* map, char const separator = ':');
}