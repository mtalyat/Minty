#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Script/Type/Function.hpp"

namespace Minty
{
    struct Script
    {
        Pointer data = nullptr;

        ScriptFunction load = nullptr;
        ScriptFunction unload = nullptr;
        ScriptFunction enable = nullptr;
        ScriptFunction disable = nullptr;
        ScriptFunction frameUpdate = nullptr;
        ScriptFunction fixedUpdate = nullptr;
        ScriptFunction finalize = nullptr;
        ScriptFunction render = nullptr;
        ScriptFunction event = nullptr;
    };
}