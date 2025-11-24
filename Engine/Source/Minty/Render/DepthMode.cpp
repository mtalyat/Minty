#include "pch.h"
#include "DepthMode.h"

using namespace Minty;

String Minty::to_string(DepthMode const obj)
{
    switch (obj)
    {
    case DepthMode::None: return "None";
    case DepthMode::Write: return "Write";
    case DepthMode::Test: return "Test";
    default: return "Unknown";
    }
}

DepthMode Minty::parse_to_depth_mode(String const& string)
{
    if (string == "None") return DepthMode::None;
    if (string == "Write") return DepthMode::Write;
    if (string == "Test") return DepthMode::Test;
    return DepthMode::None;
}

Bool Minty::parse_try_depth_mode(String const& string, DepthMode& value)
{
    if (string == "None") { value = DepthMode::None; return true; }
    if (string == "Write") { value = DepthMode::Write; return true; }
    if (string == "Test") { value = DepthMode::Test; return true; }
    value = DepthMode::None;
    return false;
}
