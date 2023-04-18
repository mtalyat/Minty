#include "pch.h"
#include "M_SaveLoad.h"
#include "M_File.h"
#include "M_Serialization.h"
#include "M_Path.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>

namespace minty
{
    MINTY_API void save_object_json(std::string const& path, Saveable* const obj)
    {
        // serialize into json
        std::string text;
        serialize_json(obj, text, true);

        // ensure directory exists
        boost::filesystem::create_directories(path);

        // write to file
        file_writeAllText(path_combine(SDL_GetBasePath(), path), text);
    }

    MINTY_API void load_object_json(std::string const& path, Saveable* const obj)
    {
        // do nothing if no file
        if (!file_exists(path))
        {
            return;
        }

        // load text from file
        std::string* text = file_readAllText(path);

        // deserialize from json
        deserialize_json(*text, obj);
    }
}
