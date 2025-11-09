#include "pch.h"
#include "StencilMode.h"

using namespace Minty;

String Minty::to_string(StencilMode const obj)
{
    switch (obj)
    {
    case StencilMode::None: return "None";
    case StencilMode::Write: return "Write";
    case StencilMode::Test: return "Test";
    default: return "Unknown";
	}
}

StencilMode Minty::parse_to_stencil_mode(String const& string)
{
    if (string == "None") return StencilMode::None;
    if (string == "Write") return StencilMode::Write;
    if (string == "Test") return StencilMode::Test;
    return StencilMode::None;
}

Bool Minty::parse_try_stencil_mode(String const& string, StencilMode& value)
{
    if (string == "None") { value = StencilMode::None; return true; }
    if (string == "Write") { value = StencilMode::Write; return true; }
    if (string == "Test") { value = StencilMode::Test; return true; }
    value = StencilMode::None;
    return false;
}
