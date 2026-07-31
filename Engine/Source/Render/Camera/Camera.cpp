#include "pch.hpp"
#include "Camera.hpp"

using namespace Minty;

Minty::Camera::Camera()
    : m_perspective(CameraPerspectiveEnum::Default),
      m_fov(45.0f),
      m_nearPlane(0.1f),
      m_farPlane(100.0f),
      m_aspectRatio(16.0f / 9.0f),
      m_size(5.0f)
{
}

void Minty::Serializer<Camera>::serialize(Writer &writer, Camera const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Camera>::deserialize(Reader &reader, Camera &value)
{
    // Position and direction updated by the TransformComponent, so we don't need to read them here.
    reader.read("Perspective", value.m_perspective);
    reader.read("FOV", value.m_fov);
    reader.read("NearPlane", value.m_nearPlane);
    reader.read("FarPlane", value.m_farPlane);
    reader.read("AspectRatio", value.m_aspectRatio);
    reader.read("Size", value.m_size);

    return true;
}
