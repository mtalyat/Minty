#include "pch.h"
#include "AudioListener.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AudioListener::serialize(Writer& writer) const
{
	writer.write("position", position);
	writer.write("forward", forward);
	writer.write("up", up);
	writer.write("velocity", velocity);
}

Bool Minty::AudioListener::deserialize(Reader& reader)
{
	reader.read("position", position);
	reader.read("forward", forward);
	reader.read("up", up);
	reader.read("velocity", velocity);

	return true;
}
