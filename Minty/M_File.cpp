#include "pch.h"
#include "M_File.h"
#include "M_Debug.h"
#include <iostream>
#include <sstream>
#include <fstream>

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
            Debug::logError("File not found at: " + path);
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
            Debug::logError("File not found at: " + path);
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
            Debug::logError("File not found at: " + path);
            return nullptr;
        }

        // read headers
        std::string line;

        if (!std::getline(file, line))
        {
            // no line to read
            Debug::logError("File was empty: " + path);
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
        // try to open the file, if it is open, it exists

        // get the file
        std::fstream file(path, std::ios::in);

        bool exists = file.is_open();

        file.close();

        return exists;
    }
}
