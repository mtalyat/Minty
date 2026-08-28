#include "pch.hpp"
#include "CollisionMask.hpp"
#include "Core/Serialize/ParsedTypes.hpp"

using namespace Minty;

Bool Minty::Parser<Collision>::parse(StringView const str, Collision &value)
{
    return Parser<CollisionType>::parse(str, value.value);
}

String Minty::Parser<Collision>::to_string(Collision const &value)
{
    return Parser<CollisionType>::to_string(value.value);
}

Bool Minty::Parser<CollisionMask>::parse(StringView const str, CollisionMask &value)
{
    return Parser<MaskType>::parse(str, value.value);
}

String Minty::Parser<CollisionMask>::to_string(CollisionMask const &value)
{
    return Parser<MaskType>::to_string(value.value);
}
