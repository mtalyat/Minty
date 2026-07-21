#pragma once

/**
 * @file Comparable.hpp
 * @brief Header file defining the Comparable concept for types that can be compared using standard comparison operators.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include <concepts>

namespace Minty
{
    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a == b } -> std::convertible_to<Bool>;
        { a != b } -> std::convertible_to<Bool>;
        { a < b } -> std::convertible_to<Bool>;
        { a > b } -> std::convertible_to<Bool>;
        { a <= b } -> std::convertible_to<Bool>;
        { a >= b } -> std::convertible_to<Bool>;
    };
}