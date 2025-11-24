#include "pch.h"
#include "AudioSource.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AudioSource::serialize(Writer& writer) const
{
	writer.write("Position", m_position);
	writer.write("Velocity", m_velocity);
	writer.write("Attenuation", m_attenuation);
	writer.write("AttenuationRolloff", m_attenuationRolloff);
	writer.write("Min", m_minDistance);
	writer.write("Max", m_maxDistance);
}

Bool Minty::AudioSource::deserialize(Reader& reader)
{
	reader.read("Position", m_position);
	reader.read("Velocity", m_velocity);
	reader.read("Attenuation", m_attenuation);
	reader.read("AttenuationRolloff", m_attenuationRolloff);
	reader.read("Min", m_minDistance);
	reader.read("Max", m_maxDistance);

	return true;
}
