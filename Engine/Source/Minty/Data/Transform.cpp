#include "pch.h"
#include "Transform.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

Minty::Transform::Transform()
	: m_localPosition(0.0f, 0.0f, 0.0f), m_localRotation(Math::identity<Quaternion>()), m_localScale(1.0f, 1.0f, 1.0f), m_globalMatrix(Math::identity<Matrix4>())
{
}

Matrix4 Minty::Transform::get_local_matrix() const
{
	return glm::translate(Matrix4(1.0f), m_localPosition) * glm::mat4_cast(m_localRotation) * glm::scale(Matrix4(1.0f), m_localScale);
}

void Minty::Serializer<Transform>::serialize(Writer &writer, Transform const &value)
{
	writer.write("Position", value.m_localPosition);
	Float3 eulerAngles = Math::to_euler(value.m_localRotation);
	// convert radians to degrees
	eulerAngles *= Math::RAD2DEG;
	writer.write("Rotation", eulerAngles);
	writer.write("Scale", value.m_localScale);
}

void Minty::Serializer<Transform>::deserialize(Reader &reader, Transform &value)
{
	reader.read_default(value.m_localPosition);
	reader.read("Position", value.m_localPosition);
	Float3 eulerAngles;
	if (reader.read("Rotation", eulerAngles))
	{
		// convert degrees to radians
		eulerAngles *= Math::DEG2RAD;
		value.m_localRotation = Math::to_cartesian(eulerAngles);
	}
	reader.read("Scale", value.m_localScale);
}