#include "pch.h"
#include "Camera.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Camera::Camera(CameraBuilder const& builder)
	: m_perspective(builder.perspective)
	, m_fov(builder.fov)
	, m_nearPlane(builder.nearPlane)
	, m_farPlane(builder.farPlane)
	, m_color(builder.color)
	, m_aspectRatio(builder.aspectRatio)
	, m_size(builder.size)
	, m_layer(builder.layer)
	, m_renderTarget(builder.renderTarget)
{
	MINTY_ASSERT(builder.perspective != Perspective::Undefined, "Camera perspective cannot be undefined.");
	MINTY_ASSERT(builder.fov > 0.0f && builder.fov < 180.0f, "Camera Field of View must be between 0 and 180 degrees.");
	MINTY_ASSERT(builder.nearPlane > 0.0f, "Camera near plane must be greater than 0.");
	MINTY_ASSERT(builder.farPlane > builder.nearPlane, "Camera far plane must be greater than near plane.");
	MINTY_ASSERT(builder.size > 0.0f, "Camera size must be greater than 0.");
}

void Minty::Camera::serialize(Writer& writer) const
{
	writer.write("perspective", m_perspective);
	writer.write("fov", m_fov * Math::RAD2DEG); // stored as radians, write as degrees
	writer.write("near", m_nearPlane);
	writer.write("far", m_farPlane);
	writer.write("color", m_color);
	writer.write("aspectRatio", m_aspectRatio);
	writer.write("get_size", m_size);
	writer.write("layerMask", m_layer);
}

Bool Minty::Camera::deserialize(Reader& reader)
{
	reader.read("perspective", m_perspective);
	// read as degrees, store as radians
	if (reader.read("fov", m_fov))
	{
		m_fov *= Math::DEG2RAD;
	}
	reader.read("near", m_nearPlane);
	reader.read("far", m_farPlane);
	reader.read("color", m_color);
	reader.read("aspectRatio", m_aspectRatio);
	reader.read("get_size", m_size);
	reader.read("layerMask", m_layer);

	return true;
}

Owner<Camera> Minty::Camera::create(CameraBuilder const& builder)
{
	return Owner<Camera>(builder);
}
