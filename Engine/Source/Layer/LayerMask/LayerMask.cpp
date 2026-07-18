#include "pch.hpp"
#include "LayerMask.hpp"
#include "Core/Serialize/ParsedTypes.hpp"

using namespace Minty;

Bool Minty::Parser<Layer>::parse(StringView const str, Layer &value)
{
    return Parser<LayerType>::parse(str, value.value);
}

String Minty::Parser<Layer>::to_string(Layer const &value)
{
    return Parser<LayerType>::to_string(value.value);
}

Bool Minty::Parser<LayerMask>::parse(StringView const str, LayerMask &value)
{
    return Parser<MaskType>::parse(str, value.value);
}

String Minty::Parser<LayerMask>::to_string(LayerMask const &value)
{
    return Parser<MaskType>::to_string(value.value);
}
