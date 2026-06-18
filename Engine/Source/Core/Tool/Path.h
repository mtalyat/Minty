#pragma once

/**
 * @file Path.h
 * @brief Header file for the Path tools.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Data/Path.h"
#include "Core/Data/Vector.h"

namespace Minty::Tool
{
    /**
     * @brief Gets the files at the given Path.
     * @param path The Path to get the files from.
     * @param recursive Whether to get files recursively.
     * @returns A Vector of Paths representing the files.
     */
    Vector<Path> get_files(Path const &path, Bool const recursive = false);

    /**
     * @brief Gets the directories at the given Path.
     * @param path The Path to get the directories from.
     * @param recursive Whether to get directories recursively.
     * @returns A Vector of Paths representing the directories.
     */
    Vector<Path> get_directories(Path const &path, Bool const recursive = false);
}