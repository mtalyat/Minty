#ifndef MINTY_DATA_COMBINE_H
#define MINTY_DATA_COMBINE_H

/**
 * @file Combine.h
 * @brief Header file defining the Combine enum for specifying how to combine values in various contexts.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
    /**
     * @brief Specifies how to combine values in various contexts, such as blending or layering.
     */
    enum class Combine : UInt8
    {
        /**
         * @brief Do not combine values, use them as they are.
         */
        None = 0,

        /**
         * @brief Add the values together.
         */
        Add,

        /**
         * @brief Multiply the values together.
         */
        Multiply,

        /**
         * @brief Use the average of the values.
         */
        Average,

        /**
         * @brief Use the maximum of the values.
         */
        Max,

        /**
         * @brief Use the minimum of the values.
         */
        Min,
    };

    template <>
    struct Parser<Combine>
    {
        static Bool parse(StringView const str, Combine &value);
        static String to_string(Combine const &value);
    };

    /**
     * @brief Combines two values according to the specified combine mode.
     * @tparam T The type of the values to combine. Should support the necessary operations for the combine modes.
     * @param a The first value.
     * @param b The second value.
     * @param mode The combine mode to use.
     * @return The combined value.
     */
    template <typename T>
    T combine_values(T const a, T const b, Combine const mode)
    {
        switch (mode)
        {
        case Combine::None:
            return a;
        case Combine::Add:
            return a + b;
        case Combine::Multiply:
            return a * b;
        case Combine::Average:
            return (a + b) / static_cast<T>(2);
        case Combine::Max:
            return a > b ? a : b;
        case Combine::Min:
            return a < b ? a : b;
        default:
            MINTY_NOT_IMPLEMENTED();
            return a;
        }
    }
    
    /**
     * @brief Combines two combine modes by taking the maximum of the two. This is used to determine the resulting combine mode when combining two materials or effects that each have their own combine mode.
     * @param a The first combine mode.
     * @param b The second combine mode.
     * @return The resulting combine mode.
     */
    inline Combine combine_modes(Combine const a, Combine const b)
    {
        return a > b ? a : b;
    }
}

#endif // MINTY_DATA_COMBINE_H