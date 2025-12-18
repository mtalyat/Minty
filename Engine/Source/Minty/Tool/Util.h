#ifndef MINTY_TOOL_UTIL_H
#define MINTY_TOOL_UTIL_H

/**
 * @file Util.h
 * @brief Header file for utility functions used in the Minty Tool module.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/String.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
    class String;
}

namespace Minty::Util
{
    Tuple<Size, Size> find_group(String const &str, Char const open, Char const close, Size const index = 0);

    Vector<Tuple<Size, Size>> find_groups(String const &str, Char const open, Char const close, Size const index = 0);

    Vector<String> split_by_indices(String const &str, Vector<Size> const &indices, Size delimiterSize);

    Vector<String> split(String const &str, Char const delimiter);

    Vector<String> split_smart(String const &str, Char const delimiter, String const &open = TEXT_OPEN, String const &close = TEXT_CLOSE);

    Vector<String> split(String const &str, String const &delimiter);

    Vector<String> split_smart(String const &str, String const &delimiter, String const &open = TEXT_OPEN, String const &close = TEXT_CLOSE);

    Vector<String> split(String const &str);

    Vector<String> split_lines(String const &str);

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