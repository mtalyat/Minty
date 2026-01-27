#ifndef MINTY_SERIALIZATION_EVALUATOR_H
#define MINTY_SERIALIZATION_EVALUATOR_H

/**
 * @file Evaluator.h
 * @brief Header file defining expression evaluation utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Data/StringView.h"

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

#endif // MINTY_SERIALIZATION_EVALUATOR_H