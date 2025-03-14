#include "pch.h"
#include "UUID.h"
#include <random>

using namespace Minty;

static std::random_device randomDevice;
static std::mt19937_64 randomEngine(randomDevice());
static std::uniform_int_distribution<Size> uniformDistribution;

UUID Minty::UUID::create()
{
    return UUID(uniformDistribution(randomEngine));
}