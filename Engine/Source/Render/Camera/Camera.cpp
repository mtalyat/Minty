#include "pch.hpp"
#include "Camera.hpp"

using namespace Minty;

void Minty::Serializer<Camera>::serialize(Writer &writer, Camera const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

/*
        Float3 position;
        Float3 direction;

        CameraPerspective perspective = CameraPerspectiveEnum::Default;

        Float fov = 45.0f;
        Float nearPlane = 0.1f;
        Float farPlane = 100.0f;
        Float aspectRatio = 16.0f / 9.0f;
        Float size = 5.0f;
*/

Bool Minty::Serializer<Camera>::deserialize(Reader &reader, Camera &value)
{
    // Position and direction updated by the TransformComponent, so we don't need to read them here.
    reader.read("Perspective", value.perspective);
    reader.read("FOV", value.fov);
    reader.read("NearPlane", value.nearPlane);
    reader.read("FarPlane", value.farPlane);
    reader.read("AspectRatio", value.aspectRatio);
    reader.read("Size", value.size);

    return true;
}
