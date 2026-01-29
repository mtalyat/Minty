#ifndef MINTY_TOOL_UTIL_H
#define MINTY_TOOL_UTIL_H

/**
 * @file Util.h
 * @brief Header file for utility functions used in the Minty Tool module.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Data/Path.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
    class String;
}

namespace Minty::Tool
{
    /**
     * @brief Gets the files within the directory at the given Path.
     * @param path The path to the directory.
     * @param recursive If true, get the sub-directory files as well.
     * @returns A Vector of Paths to the Files within directory at the given Path.
     */
    static Vector<Path> get_files(Path const &path, Bool const recursive = false);

    /**
     * @brief Gets the directories within the directory at the given Path.
     * @param path The path to the directory.
     * @param recursive If true, get the sub-directory directories as well.
     * @returns A Vector of Paths to the directories within directory at the given Path.
     */
    static Vector<Path> get_directories(Path const &path, Bool const recursive = false);

    /**
     * @brief Gets all of the files and directories within the directory at the given Path.
     * @param path The path to the directory.
     * @param recursive If true, get the sub-directory files and directories as well.
     * @returns A Vector of Paths to the files and directories within directory at the given Path.
     */
    static Vector<Path> get_contents(Path const &path, Bool const recursive = false);
}

#endif // MINTY_TOOL_UTIL_H