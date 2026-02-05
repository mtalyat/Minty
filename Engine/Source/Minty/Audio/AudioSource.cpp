#include "pch.h"
#include "AudioSource.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<AudioSource>::serialize(Writer &writer, AudioSource const &value)
{
	writer.write("Position", value.m_position);
	writer.write("Velocity", value.m_velocity);
	writer.write("Attenuation", value.m_attenuation);
	writer.write("AttenuationRolloff", value.m_attenuationRolloff);
	writer.write("Min", value.m_minDistance);
	writer.write("Max", value.m_maxDistance);
}

Bool Minty::Serializer<AudioSource>::deserialize(Reader &reader, AudioSource &value)
{
	reader.read("Position", value.m_position);
	reader.read("Velocity", value.m_velocity);
	reader.read("Attenuation", value.m_attenuation);
	reader.read("AttenuationRolloff", value.m_attenuationRolloff);
	reader.read("Min", value.m_minDistance);
	reader.read("Max", value.m_maxDistance);
	return true;
}
