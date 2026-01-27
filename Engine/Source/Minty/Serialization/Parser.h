#ifndef MINTY_SERIALIZATION_PARSER_H
#define MINTY_SERIALIZATION_PARSER_H

/**
 * @file Parser.h
 * @brief Header file defining the Parser class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringView.h"
#include <concepts>

namespace Minty
{
    /*
    
    template<>
    struct Parser<NAME>
    {
        static Bool parse(StringView const str, NAME &value);
        static String to_string(NAME const &value);
    };

    */

    /**
     * @brief Template struct for parsing different data types during serialization.
     */
    template <typename T>
    struct Parser;

    template<typename T>
    concept Parsable = requires(StringView const str, T& value)
    {
        { Parser<T>::parse(str, value) } -> std::same_as<Bool>;
        { Parser<T>::to_string(value) } -> std::same_as<String>;
    };
};

#endif // MINTY_SERIALIZATION_PARSER_H