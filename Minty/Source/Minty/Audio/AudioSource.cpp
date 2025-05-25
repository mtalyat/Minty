#include "pch.h"
#include "AudioSource.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AudioSource::serialize(Writer& writer) const
{
	writer.write("position", m_position);
	writer.write("velocity", m_velocity);
	writer.write("attenuation", m_attenuation);
	writer.write("attenuationRolloff", m_attenuationRolloff);
	writer.write("minDistance", m_minDistance);
	writer.write("maxDistance", m_maxDistance);
}

Bool Minty::AudioSource::deserialize(Reader& reader)
{
	reader.read("position", m_position);
	reader.read("velocity", m_velocity);
	reader.read("attenuation", m_attenuation);
	reader.read("attenuationRolloff", m_attenuationRolloff);
	reader.read("minDistance", m_minDistance);
	reader.read("maxDistance", m_maxDistance);

	return true;
}
