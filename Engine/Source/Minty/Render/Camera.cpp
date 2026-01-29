#include "pch.h"
#include "Camera.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/CameraInfo.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Camera::Camera(CameraInfo const &info)
	: Asset(info.id), m_perspective(info.perspective), m_fov(info.fov), m_nearPlane(info.nearPlane), m_farPlane(info.farPlane), m_color(info.color), m_aspectRatio(info.aspectRatio), m_size(info.size), m_layer(info.layer), m_renderTarget(info.renderTarget)
{
	MINTY_ASSERT(info.perspective != Perspective::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.fov > 0.0f && info.fov < 180.0f, ErrorCode::Argument_OutOfRange);
	MINTY_ASSERT(info.nearPlane > 0.0f, ErrorCode::Argument_ExpectedAboveZero);
	MINTY_ASSERT(info.farPlane > info.nearPlane, ErrorCode::Argument_IncorrectOrder);
	MINTY_ASSERT(info.size > 0.0f, ErrorCode::Argument_ExpectedAboveZero);
}

Shared<Camera> Minty::Camera::create(CameraInfo const &info)
{
	return Shared<Camera>::create(info);
}

Shared<Camera> Minty::Camera::create()
{
	CameraInfo info{};
	return create(info);
}

void Minty::Serializer<Camera>::serialize(Writer &writer, Camera const &value)
{
	writer.write("Perspective", value.m_perspective);
	writer.write("FOV", value.m_fov * Math::RAD2DEG); // stored as radians, write as degrees
	writer.write("Near", value.m_nearPlane);
	writer.write("Far", value.m_farPlane);
	writer.write("Color", value.m_color);
	writer.write("AspectRatio", value.m_aspectRatio);
	writer.write("Size", value.m_size);
	writer.write("LayerMask", value.m_layer);
}

Bool Minty::Serializer<Camera>::deserialize(Reader &reader, Camera &value)
{
	reader.read("Perspective", value.m_perspective);
	// read as degrees, store as radians
	if (reader.read("FOV", value.m_fov))
	{
		value.m_fov *= Math::DEG2RAD;
	}
	reader.read("Near", value.m_nearPlane);
	reader.read("Far", value.m_farPlane);
	reader.read("Color", value.m_color);
	reader.read("AspectRatio", value.m_aspectRatio);
	reader.read("Size", value.m_size);
	reader.read("LayerMask", value.m_layer);
	return true;
}
