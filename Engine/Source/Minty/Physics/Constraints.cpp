#include "Constraints.h"
#include "Minty/Data/StringBuilder.h"

using namespace Minty;

static String const s_constraintStrings[] = {
    "X",
    "Y",
    "Z"
};

String Minty::to_string(Constraints const obj)
{
    if(obj == Constraints::None)
    {
        return "None";
    }

    StringBuilder output;
    Size objValue = static_cast<Size>(obj);
    Size constraint = 1;
    Size const max = static_cast<Size>(Constraints::All);
    for (Size index = 0; constraint <= max; constraint <<= 1, index++)
    {
        if (constraint & objValue)
        {
            output.append(s_constraintStrings[index]);
            output.append("|");
        }
    }
    if(output.get_size() > 0)
    {
        output.slice(0, output.get_size() - 1);
    }
    return output.to_string();
}

Constraints Minty::parse_to_constraints(String const &string)
{
    Constraints constraints = Constraints::None;
    if (string.contains("X")) constraints = constraints | Constraints::X;
    if (string.contains("Y")) constraints = constraints | Constraints::Y;
    if (string.contains("Z")) constraints = constraints | Constraints::Z;
    return constraints;
}

Bool Minty::parse_try_constraints(String const &string, Constraints &value)
{
    value = parse_to_constraints(string);
    return value != Constraints::None;
}
