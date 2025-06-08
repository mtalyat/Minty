#include "pch.h"
#include "Transform.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"

using namespace Minty;

Matrix4 Minty::Transform::get_local_matrix() const
{
    return glm::translate(Matrix4(1.0f), m_localPosition) * glm::mat4_cast(m_localRotation) * glm::scale(Matrix4(1.0f), m_localScale);
}

void Minty::Transform::serialize(Writer& writer) const
{
	writer.write("Position", m_localPosition);
	Float3 eulerAngles = Math::to_euler(m_localRotation);
	// convert radians to degrees
	eulerAngles *= Math::RAD2DEG;
	writer.write("Rotation", eulerAngles);
	writer.write("Scale", m_localScale);
}

Bool Minty::Transform::deserialize(Reader& reader)
{
	reader.read("Position", m_localPosition);
	Float3 eulerAngles;
	if (reader.read("Rotation", eulerAngles))
	{
		// convert degrees to radians
		eulerAngles *= Math::DEG2RAD;
		m_localRotation = Math::to_cartesian(eulerAngles);
	}
	reader.read("Scale", m_localScale);

	return true;
}
