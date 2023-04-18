#pragma once

#include "M_Object.h"
#include <boost/property_tree/ptree.hpp>

namespace minty
{
	class MINTY_API Saveable
		: public Object
	{
	public:
		virtual void serialize(boost::property_tree::ptree& ptree) = 0;

		virtual void deserialize(boost::property_tree::ptree const& ptree) = 0;
	};
}