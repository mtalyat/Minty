#pragma once

/**
 * @file Handle.h
 * @brief Header file defining Window related handles.
 * @author Mitchell Talyat
 */

#include "Core/Type/Handle.hpp"

namespace Minty
{
    class Window;
    using WindowHandle = Handle<Window>;
}