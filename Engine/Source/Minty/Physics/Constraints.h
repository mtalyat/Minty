#ifndef MINTY_PHYSICS_CONSTRAINTS_H
#define MINTY_PHYSICS_CONSTRAINTS_H

/**
 * @file Constraints.h
 * @brief Header file defining physics constraint classes.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Enum.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
    /**
     * @brief The constraints that can be applied to physics objects.
     */
    enum class Constraints
    {
        None = 0,
        X = 0x1,
        Y = 0x2,
        Z = 0x4,
        XY = X | Y,
        XZ = X | Z,
        YZ = Y | Z,
        All = X | Y | Z
    };

    MINTY_ENABLE_ENUM_OPERATORS(Constraints)

    String to_string(Constraints const obj);
    Constraints parse_to_constraints(String const &string);
    Bool parse_try_constraints(String const &string, Constraints &value);
    template <>
    inline Constraints parse_to<Constraints>(StringView const string) { return parse_to_constraints(string); }
    template <>
    inline Bool parse_try<Constraints>(StringView const string, Constraints &value) { return parse_try_constraints(string, value); }
}

#endif // MINTY_PHYSICS_CONSTRAINTS_H