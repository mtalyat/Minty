#include "pch.h"
#include "AudioSourceComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AudioSourceComponent::serialize(Writer& writer) const
{
	writer.write("AudioClip", audioClip);
	writer.write("Play", play);
	writer.write("Volume", volume);
	writer.write("Attenuation", attenuation);
	writer.write("AttenuationRollOff", attenuationRollOff);
	writer.write("Min", minDistance);
	writer.write("Max", maxDistance);
}

Bool Minty::AudioSourceComponent::deserialize(Reader& reader)
{
	reader.read("AudioClip", audioClip);
	reader.read("Play", play);
	reader.read("Volume", volume);
	reader.read("Attenuation", attenuation);
	reader.read("AttenuationRollOff", attenuationRollOff);
	reader.read("Min", minDistance);
	reader.read("Max", maxDistance);

	return true;
}
