#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Float3.hpp"
#include "Render/Camera/CameraPerspective.hpp"
#include "Core/Type/Color.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct CameraInfo;

    struct Camera
    {
        friend struct Serializer<Camera>;

#pragma region Constructor

    public:
        Camera();

        Camera(CameraInfo const &info);

#pragma endregion

#pragma region Accessor

    public:
        inline CameraPerspective const &get_perspective() const { return m_perspective; }
        inline Float get_fov() const { return m_fov; }
        inline Float get_near_plane() const { return m_nearPlane; }
        inline Float get_far_plane() const { return m_farPlane; }
        inline Float get_aspect_ratio() const { return m_aspectRatio; }
        inline Float get_size() const { return m_size; }

#pragma endregion

#pragma region Variables

    private:
        CameraPerspective m_perspective;
        Float m_fov;
        Float m_nearPlane;
        Float m_farPlane;
        Float m_aspectRatio;
        Float m_size;

#pragma endregion
    };

    template <>
    struct Serializer<Camera>
    {
        static void serialize(Writer &writer, Camera const &value);
        static Bool deserialize(Reader &reader, Camera &value);
    };
}