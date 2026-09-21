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
}