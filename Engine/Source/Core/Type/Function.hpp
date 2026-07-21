#pragma once

/**
 * @file Function.hpp
 * @brief Header file defining the Function type for the Minty engine.
 * @author Mitchell Talyat
 */

#include <functional>

namespace Minty
{
	template<typename T>
	using Function = std::function<T>;
}