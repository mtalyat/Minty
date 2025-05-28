#include "pch.h"
#include "AudioListener.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AudioListener::serialize(Writer& writer) const
{
	writer.write("Position", position);
	writer.write("Forward", forward);
	writer.write("Up", up);
	writer.write("Velocity", velocity);
}

Bool Minty::AudioListener::deserialize(Reader& reader)
{
	reader.read("Position", position);
	reader.read("Forward", forward);
	reader.read("Up", up);
	reader.read("Velocity", velocity);

	return true;
}
