#include "pch.h"
#include "Random.h"
#include <random>

using namespace Minty;
using namespace Minty::Math;

static std::random_device s_randomDevice;
static std::mt19937 s_randomEngine(s_randomDevice());
static std::mt19937_64 s_randomEngine64(s_randomDevice());
static std::uniform_real_distribution<Float> s_uniformDistributionFloat;
static std::uniform_int_distribution<Int> s_uniformDistributionInt;
static std::uniform_int_distribution<UInt> s_uniformDistributionUInt;
static std::uniform_real_distribution<WFloat> s_uniformDistributionDouble;
static std::uniform_int_distribution<WInt> s_uniformDistributionLong;
static std::uniform_int_distribution<WUInt> s_uniformDistributionULong;

Float Minty::Math::random_float(Float const min, Float const max)
{
	std::uniform_real_distribution<Float> dist(min, max);
	return dist(s_randomEngine);
}

Float Minty::Math::random_float()
{
	return s_uniformDistributionFloat(s_randomEngine);
}

Int Minty::Math::random_int(Int const min, Int const max)
{
	std::uniform_int_distribution<Int> dist(min, max);
	return dist(s_randomEngine);
}

Int Minty::Math::random_int()
{
	return s_uniformDistributionInt(s_randomEngine);
}

UInt Minty::Math::random_uint(UInt const min, UInt const max)
{
	std::uniform_int_distribution<UInt> dist(min, max);
	return dist(s_randomEngine);
}

UInt Minty::Math::random_uint()
{
	return s_uniformDistributionUInt(s_randomEngine);
}

WFloat Minty::Math::random_double(WFloat const min, WFloat const max)
{
	std::uniform_real_distribution<WFloat> dist(min, max);
	return dist(s_randomEngine64);
}

WFloat Minty::Math::random_double()
{
	return s_uniformDistributionDouble(s_randomEngine64);
}

WInt Minty::Math::random_long(WInt const min, WInt const max)
{
	std::uniform_int_distribution<WInt> dist(min, max);
	return dist(s_randomEngine64);
}

WInt Minty::Math::random_long()
{
	return s_uniformDistributionLong(s_randomEngine64);
}

WUInt Minty::Math::random_ulong(WUInt const min, WUInt const max)
{
	std::uniform_int_distribution<WUInt> dist(min, max);
	return dist(s_randomEngine64);
}

WUInt Minty::Math::random_ulong()
{
	return s_uniformDistributionULong(s_randomEngine64);
}
