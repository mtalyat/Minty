#pragma once

/**
 * @file Converter.hpp
 * @brief Header file for conversion utilities.
 * @author Mitchell Talyat
 */

#include <concepts>

namespace Minty
{
    /*
    
    template<>
    struct Converter<MintyType, OtherType>
    {
        static MintyType to_minty(OtherType const& value);
        static OtherType from_minty(MintyType const& value);
    };

    */

    /**
     * @brief Template struct for converting between different data types.
     */
    template <typename MintyType, typename OtherType>
    struct Converter;

    template<typename MintyType, typename OtherType>
    concept Convertible = requires(MintyType const value, OtherType const otherValue)
    {
        { Converter<MintyType, OtherType>::to_minty(value) } -> std::same_as<MintyType>;
        { Converter<MintyType, OtherType>::from_minty(value) } -> std::same_as<OtherType>;
    };
}