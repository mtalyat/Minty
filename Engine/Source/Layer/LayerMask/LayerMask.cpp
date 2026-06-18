#include "pch.h"
#include "LayerMask.h"
#include "Core/Serialize/ParsedTypes.h"

using namespace Minty;

Bool Minty::Parser<Layer>::parse(StringView const str, Layer &value)
{
    return Parser<LayerType>::parse(str, value.value);
}

String Minty::Parser<Layer>::to_string(Layer const &value)
{
    return Parser<LayerType>::to_string(value.value);
}

Bool Minty::Parser<Mask>::parse(StringView const str, Mask &value)
{
    return Parser<MaskType>::parse(str, value.value);
}

String Minty::Parser<Mask>::to_string(Mask const &value)
{
    return Parser<MaskType>::to_string(value.value);
}
