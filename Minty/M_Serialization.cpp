#include "pch.h"
#include "M_Serialization.h"
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

namespace minty
{
	void serialize_json(Saveable* const obj, std::string& text, bool const pretty)
	{
		pt::ptree root;

		// populate property tree
		obj->serialize(root);

		// convert to json
		std::ostringstream buf;
		pt::write_json(buf, root, pretty);
		text = buf.str();
	}
	
	void deserialize_json(std::string const& text, Saveable* const obj)
	{
		pt::ptree root;

		// get property tree data from json
		std::istringstream buf(text);
		pt::read_json(buf, root);

		// deserialize object
		obj->deserialize(root);
	}
}
