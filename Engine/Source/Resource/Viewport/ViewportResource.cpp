#include "pch.hpp"
#include "ViewportResource.hpp"

using namespace Minty;

Bool Minty::Serializer<ViewportResource>::serialize(Writer &writer, ViewportResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<ViewportResource>::deserialize(Reader &reader, ViewportResource &value)
{
    Bool dynamic = value.dynamic;
    Float2 viewPosition = value.viewPosition;
    Float2 viewSize = value.viewSize;
    Float minDepth = value.minDepth;
    Float maxDepth = value.maxDepth;
    Int2 scissorPosition = value.scissorPosition;
    UInt2 scissorSize = value.scissorSize;

    reader.read("Dynamic", dynamic);
    reader.read("ViewPosition", viewPosition);
    reader.read("ViewSize", viewSize);
    reader.read("MinDepth", minDepth);
    reader.read("MaxDepth", maxDepth);
    reader.read("ScissorPosition", scissorPosition);
    reader.read("ScissorSize", scissorSize);

    value.dynamic = dynamic;
    value.viewPosition = viewPosition;
    value.viewSize = viewSize;
    value.minDepth = minDepth;
    value.maxDepth = maxDepth;
    value.scissorPosition = scissorPosition;
    value.scissorSize = scissorSize;
    return true;
}