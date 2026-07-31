#include "pch.hpp"
#include "Camera.hpp"
#include "Render/Camera/CameraInfo.hpp"

using namespace Minty;

Minty::Camera::Camera()
    : Camera(CameraInfo{})
{
}

Minty::Camera::Camera(CameraInfo const &info)
    : m_perspective(info.perspective),
      m_fov(info.fov),
      m_nearPlane(info.nearPlane),
      m_farPlane(info.farPlane),
      m_aspectRatio(info.aspectRatio),
      m_size(info.size)
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
