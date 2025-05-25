#include "pch.h"
#include "AudioSourceComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AudioSourceComponent::serialize(Writer& writer) const
{
	writer.write("audioClip", audioClip);
	writer.write("play", play);
	writer.write("volume", volume);
	writer.write("attenuation", attenuation);
	writer.write("attenuationRollOff", attenuationRollOff);
	writer.write("min", minDistance);
	writer.write("max", maxDistance);
}

Bool Minty::AudioSourceComponent::deserialize(Reader& reader)
{
	reader.read("audioClip", audioClip);
	reader.read("play", play);
	reader.read("volume", volume);
	reader.read("attenuation", attenuation);
	reader.read("attenuationRollOff", attenuationRollOff);
	reader.read("min", minDistance);
	reader.read("max", maxDistance);

	return true;
}
