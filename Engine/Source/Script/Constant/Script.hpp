#pragma once

namespace Minty
{
    // "namespace" below just means the logical grouping of related constants within the Minty engine.

    // LOCAL CONTEXT
    constexpr const char* SCRIPT_NAMESPACE_LOCAL = "this";
    constexpr const char* SCRIPT_VAR_LOCAL_ENTITY = "entity";

    // GLOBAL CONTEXT

    // Minty namespace
    constexpr const char* SCRIPT_NAMESPACE_GLOBAL = "Minty";
    
    // Time namespace
    constexpr const char* SCRIPT_NAMESPACE_TIME = "Time";
    constexpr const char* SCRIPT_VAR_TIME_FRAME_DELTA = "frameDelta";
    constexpr const char* SCRIPT_VAR_TIME_FRAME = "frame";
    constexpr const char* SCRIPT_VAR_TIME_FIXED_DELTA = "fixedDelta";
    constexpr const char* SCRIPT_VAR_TIME_TOTAL = "total";

    // Input namespace
    constexpr const char* SCRIPT_NAMESPACE_INPUT = "Input";
    constexpr const char* SCRIPT_ENUM_INPUT_KEY = "Key"; // Programmatically populated with key codes
    constexpr const char* SCRIPT_ENUM_INPUT_KEY_ACTION = "KeyAction"; // Programmatically populated with action codes
    constexpr const char* SCRIPT_ENUM_INPUT_KEY_MODIFIER = "KeyModifier"; // Programmatically populated with key modifier codes
    constexpr const char* SCRIPT_ENUM_INPUT_MOUSE_BUTTON = "MouseButton"; // Programmatically populated with mouse button codes
    constexpr const char* SCRIPT_ENUM_INPUT_MOUSE = "MouseAction"; // Programmatically populated with mouse action codes
    constexpr const char* SCRIPT_FUNC_INPUT_REGISTER_KEY_PRESS = "registerKeyPress";
    constexpr const char* SCRIPT_FUNC_INPUT_REGISTER_KEY_RELEASE = "registerKeyRelease";
}