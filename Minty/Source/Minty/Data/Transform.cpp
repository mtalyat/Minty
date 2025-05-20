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
	writer.write("position", m_localPosition);
	writer.write("rotation", Math::to_euler(m_localRotation));
	writer.write("scale", m_localScale);
}

Bool Minty::Transform::deserialize(Reader& reader)
{
	reader.read("position", m_localPosition);
	Float3 eulerAngles;
	if (reader.read("rotation", eulerAngles))
	{
		m_localRotation = Math::to_cartesian(eulerAngles);
	}
	reader.read("scale", m_localScale);

	return true;
}
