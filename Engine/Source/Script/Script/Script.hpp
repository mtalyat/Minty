#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Script/Type/Function.hpp"
#include "Core/Type/Status.hpp"

namespace Minty
{
    struct ScriptLocalContext;

    struct Script
    {
        Pointer data = nullptr;

        void (*setContext)(Script &script, ScriptLocalContext const &context) = nullptr;

        ScriptFunction create = nullptr;
        ScriptFunction destroy = nullptr;
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