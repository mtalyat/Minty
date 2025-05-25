#include "pch.h"
#include "CanvasComponent.h"

using namespace Minty;

void Minty::CanvasComponent::serialize(Writer& writer) const
{
	canvas.serialize(writer);
}

Bool Minty::CanvasComponent::deserialize(Reader& reader)
{
	return canvas.deserialize(reader);
}
