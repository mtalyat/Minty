#include "pch.h"
#include "AudioSourceComponent.h"
#include "Minty/Audio/AudioClip.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<AudioSourceComponent>::serialize(Writer &writer, AudioSourceComponent const &value)
{
	writer.write("AudioClip", value.audioClip);
	writer.write("Play", value.play);
	writer.write("Volume", value.volume);
	writer.write("Attenuation", value.attenuation);
	writer.write("AttenuationRollOff", value.attenuationRollOff);
	writer.write("Min", value.minDistance);
	writer.write("Max", value.maxDistance);
}

void Minty::Serializer<AudioSourceComponent>::deserialize(Reader &reader, AudioSourceComponent &value)
{
	reader.read("AudioClip", value.audioClip);
	reader.read("Play", value.play);
	reader.read("Volume", value.volume);
	reader.read("Attenuation", value.attenuation);
	reader.read("AttenuationRollOff", value.attenuationRollOff);
	reader.read("Min", value.minDistance);
	reader.read("Max", value.maxDistance);
}
