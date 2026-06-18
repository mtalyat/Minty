#include "SoLoud_Convert.h"

using namespace Minty;

Attenuation Minty::Converter<Attenuation, unsigned int>::to_minty(unsigned int const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Attenuation();
}

unsigned int Minty::Converter<Attenuation, unsigned int>::from_minty(Attenuation const &value)
{
    switch(value.type)
    {
    case AttenuationEnum::None:
        return 0;
    case AttenuationEnum::InverseDistance:
        return 1;
    case AttenuationEnum::LinearDistance:
        return 2;
    case AttenuationEnum::ExponentialDistance:
        return 3;
    }

    MINTY_NOT_SUPPORTED();
    return 0;
}