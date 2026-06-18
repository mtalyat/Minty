#include "pch.h"
#include "AudioSourceComponent.h"
#include "Minty/Audio/AudioClip.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<AudioSourceComponent>::serialize(Writer &writer, AudioSourceComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<AudioSourceComponent>::deserialize(Reader &reader, AudioSourceComponent &value)
{
	reader.read_primary("AudioClip", value.audioClip);
	reader.read("Play", value.play);
	reader.read("Volume", value.volume);
	reader.read("Attenuation", value.attenuation);
	reader.read("AttenuationRollOff", value.attenuationRollOff);
	reader.read("Min", value.minDistance);
	reader.read("Max", value.maxDistance);
	return true;
}
