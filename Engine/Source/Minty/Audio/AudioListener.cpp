#include "pch.h"
#include "AudioListener.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<AudioListener>::serialize(Writer &writer, AudioListener const &value)
{
	writer.write("Position", value.m_position);
	writer.write("Forward", value.m_forward);
	writer.write("Up", value.m_up);
	writer.write("Velocity", value.m_velocity);
}

Bool Minty::Serializer<AudioListener>::deserialize(Reader &reader, AudioListener &value)
{
	reader.read("Position", value.m_position);
	reader.read("Forward", value.m_forward);
	reader.read("Up", value.m_up);
	reader.read("Velocity", value.m_velocity);
	return true;
}
