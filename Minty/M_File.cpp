#include "pch.h"
#include "M_File.h"
#include "M_Debug.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>

namespace minty
{
    /// <summary>
    /// Gets all of the text from the file at the given path.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::string* file_readAllText(std::string const& path)
    {
        std::string output = "";

        // get the file to read from
        std::fstream file(path, std::ios::in);

        // if the file exists and is open
        if (file.is_open()) {
            std::string line;

            // while there are lines, add to output
            while (std::getline(file, line)) {
                output += line + "\n";
            }

            // done with file, close it
            file.close();
        }
        else {
            Debug::logError(15, "File not found at: " + path);
            return nullptr;
        }

        // return string
        return new std::string(output);
    }

    std::vector<std::string>* file_readAllLines(std::string const& path)
    {
        std::vector<std::string>* lines = new std::vector<std::string>();

        // get the file to read from
        std::fstream file(path, std::ios::in);

        // if the file exists and is open
        if (file.is_open()) {
            std::string line;

            // while there are lines, add to output
            while (std::getline(file, line)) {
                lines->push_back(line);
            }

            // done with file, close it
            file.close();
        }
        else {
            Debug::logError(16, "File not found at: " + path);
            return nullptr;
        }

        // return list, regardless of size
        return lines;
    }

    std::vector<std::string>* file_readCSV(std::string const& line)
    {
        std::istringstream iss(line);

        std::string field;

        std::vector<std::string>* fields = new std::vector<std::string>();

        while (std::getline(iss, field, ','))
        {
            fields->push_back(field);
        }

        return fields;
    }

    std::vector<std::vector<std::string>>* file_readAllCSV(std::string const& path)
    {
        // get the file
        std::fstream file(path, std::ios::in);

        // check if file does not exist
        if (!file.is_open())
        {
            Debug::logError(17, "File not found at: " + path);
            return nullptr;
        }

        // read headers
        std::string line;

        if (!std::getline(file, line))
        {
            // no line to read
            Debug::logError(18, "File was empty: " + path);
            return nullptr;
        }

        // read all of the data
        std::vector<std::vector<std::string>>* rows = new std::vector<std::vector<std::string>>();

        // headers
        rows->push_back(*file_readCSV(line));

        // data
        while (std::getline(file, line))
        {
            rows->push_back(*file_readCSV(line));
        }

        file.close();

        return rows;
    }

    bool file_exists(std::string const& path)
    {
        return boost::filesystem::exists(path);
    }
    
    std::map<std::string, std::string>* file_readMap(std::string const& path, char const separator)
    {
        // if no file, null
        if (!file_exists(path))
        {
            return nullptr;
        }

        // get all lines
        auto lines = file_readAllLines(path);

        std::map<std::string, std::string>* output = new std::map<std::string, std::string>();

        // split each line
        for (auto const& line : *lines)
        {
            size_t index = line.find_first_of(separator);

            // if separator found
            if (index != line.size())
            {
                // add key and value, ignore separator and following space
                output->emplace(line.substr(0, index), line.substr(index + 2, line.size() - index - 2));
            }
        }
    }

    MINTY_API bool file_writeAllText(std::string const& path, std::string const& text)
    {
        std::fstream file(path, std::ios::out);

        if (!file.is_open())
        {
            Debug::logError(-1, "File not created at " + path);
            return false;
        }

        // write text
        file << text;

        // close
        file.close();

        return true;
    }

    bool file_writeAllLines(std::string const& path, std::vector<std::string>* const lines)
    {
        std::fstream file(path, std::ios::out);

        if (!file.is_open())
        {
            Debug::logError(-1, "File not created at " + path);
            return false;
        }

        // write all lines
        for (auto const& line : *lines)
        {
            file << line << std::endl;
        }

        // close
        file.close();

        return true;
    }
    
    bool file_writeMap(std::string const& path, std::map<std::string, std::string>* map, char const separator)
    {
        if (!map)
        {
            return false;
        }

        // convert to lines
        std::vector<std::string> lines;
        lines.reserve(map->size());

        for (auto const& pair : *map)
        {
            lines.push_back(std::format("{0}{1} {2}", pair.first, separator, pair.second));
        }

        // write to file
        return file_writeAllLines(path, &lines);
    }
}
