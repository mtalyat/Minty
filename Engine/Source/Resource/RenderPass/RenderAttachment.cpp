#include "pch.h"
#include "RenderAttachment.h"

using namespace Minty;

Bool Minty::Serializer<RenderAttachment>::serialize(Writer &writer, RenderAttachment const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<RenderAttachment>::deserialize(Reader &reader, RenderAttachment &value)
{
    // Data to load
    ImageAspectFlags aspect;
    LoadOperation loadOperation;
    StoreOperation storeOperation;
    ImageLayout initialLayout;
    ImageLayout finalLayout;

    // Load the data from the reader
    reader.read("Aspect", aspect);
    reader.read("Load", loadOperation);
    reader.read("Store", storeOperation);
    reader.read("Initial", initialLayout);
    reader.read("Final", finalLayout);

    // Update the values
    value.aspect = aspect;
    value.loadOperation = loadOperation;
    value.storeOperation = storeOperation;
    value.initialLayout = initialLayout;
    value.finalLayout = finalLayout;

    return true;
}
