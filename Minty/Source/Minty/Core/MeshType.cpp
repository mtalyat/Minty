#include "pch.h"
#include "MeshType.h"

using namespace Minty;

String Minty::to_string(MeshType const obj)
{
	switch (obj)
	{
	case MeshType::Empty: return "Empty";
	case MeshType::Custom: return "Custom";
	case MeshType::Quad: return "Quad";
	case MeshType::Cube: return "Cube";

	default: return "";
	}
}

MeshType Minty::parse_to_mesh_type(String const& string)
{
	if (string == "Empty") return MeshType::Empty;
	if (string == "Custom") return MeshType::Custom;
	if (string == "Quad") return MeshType::Quad;
	if (string == "Cube") return MeshType::Cube;

	return MeshType();
}

Bool Minty::parse_try_mesh_type(String const& string, MeshType& value)
{
	value = parse_to_mesh_type(string);
	return value != MeshType() || string == "Empty";
}