#include "pch.h"
#include "Camera.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Camera::Camera(CameraInfo const& info)
	: Asset(info.id)
	, m_perspective(info.perspective)
	, m_fov(info.fov)
	, m_nearPlane(info.nearPlane)
	, m_farPlane(info.farPlane)
	, m_color(info.color)
	, m_aspectRatio(info.aspectRatio)
	, m_size(info.size)
	, m_layer(info.layer)
	, m_renderTarget(info.renderTarget)
{
	MINTY_ASSERT(info.perspective != Perspective::Undefined, "Camera perspective cannot be undefined.");
	MINTY_ASSERT(info.fov > 0.0f && info.fov < 180.0f, "Camera Field of View must be between 0 and 180 degrees.");
	MINTY_ASSERT(info.nearPlane > 0.0f, "Camera near plane must be greater than 0.");
	MINTY_ASSERT(info.farPlane > info.nearPlane, "Camera far plane must be greater than near plane.");
	MINTY_ASSERT(info.size > 0.0f, "Camera size must be greater than 0.");
}

void Minty::Camera::serialize(Writer& writer) const
{
	writer.write("Perspective", m_perspective);
	writer.write("FOV", m_fov * Math::RAD2DEG); // stored as radians, write as degrees
	writer.write("Near", m_nearPlane);
	writer.write("Far", m_farPlane);
	writer.write("Color", m_color);
	writer.write("AspectRatio", m_aspectRatio);
	writer.write("Size", m_size);
	writer.write("LayerMask", m_layer);
}

Bool Minty::Camera::deserialize(Reader& reader)
{
	reader.read("Perspective", m_perspective);
	// read as degrees, store as radians
	if (reader.read("FOV", m_fov))
	{
		m_fov *= Math::DEG2RAD;
	}
	reader.read("Near", m_nearPlane);
	reader.read("Far", m_farPlane);
	reader.read("Color", m_color);
	reader.read("AspectRatio", m_aspectRatio);
	reader.read("Size", m_size);
	reader.read("LayerMask", m_layer);

	return true;
}

Owner<Camera> Minty::Camera::create(CameraInfo const& info)
{
	return Owner<Camera>(info);
}
