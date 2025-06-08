#include "pch.h"
#include "Shape.h"

using namespace Minty;

String Minty::to_string(Shape const obj)
{
	switch (obj)
	{
	case Shape::Empty: return "Empty";
	case Shape::Box: return "Box";
	case Shape::Sphere: return "Sphere";
	case Shape::Capsule: return "Capsule";
	case Shape::Cylinder: return "Cylinder";
	case Shape::Cone: return "Cone";
	case Shape::Custom: return "Custom";

	default: return "";
	}
}

Shape Minty::parse_to_shape(String const& string)
{
	if (string == "Empty") return Shape::Empty;
	if (string == "Box") return Shape::Box;
	if (string == "Sphere") return Shape::Sphere;
	if (string == "Capsule") return Shape::Capsule;
	if (string == "Cylinder") return Shape::Cylinder;
	if (string == "Cone") return Shape::Cone;
	if (string == "Custom") return Shape::Custom;

	return Shape();
}

Bool Minty::parse_try_shape(String const& string, Shape& value)
{
	value = parse_to_shape(string);
	return true;
}