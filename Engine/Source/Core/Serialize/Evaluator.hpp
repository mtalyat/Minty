#pragma once

/**
 * @file Evaluator.hpp
 * @brief Header file defining expression evaluation utilities.
 * @author Mitchell Talyat
 */

#include "Core/Data/StringView.hpp"

namespace Minty
{
    /*
    
    template<>
    struct Evaluator<NAME>
    {
        static NAME evaluate(StringView const str);
    };

    */

    /**
     * @brief Template struct for evaluating different data types during serialization.
     */
    template <typename T>
    struct Evaluator;

    template<typename T>
    concept Evaluatable = requires(StringView const str)
    {
        { Evaluator<T>::evaluate(str) } -> std::same_as<T>;
    };
}
