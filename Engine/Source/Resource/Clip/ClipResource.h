#pragma once

/**
 * @file ClipResource.h
 * @brief ClipResource class definition.
 * This file defines the ClipResource class, which represents an audio clip resource in the application.
 */

#include "Platform/Type/Primitive.h"
#include "Audio/Type/Handle.h"
#include "Core/Data/ConstantContainer.h"
#include "Core/Serialize/Serializer.h"
#include "Audio/Type/Handle.h"

namespace Minty
{
    struct ClipResource
    {
        ClipHandle handle = INVALID_HANDLE;
        Vector<Byte> data = {};
        Float volume = 1.0f;
        Float loopPoint = 0.0f;
        Bool looping = false;
        Bool exclusive = false;
    };

    template<>
    struct Serializer<ClipResource>
    {
        static Bool serialize(Writer &writer, ClipResource const& value);
        static Bool deserialize(Reader &reader, ClipResource &value);
    };
}