#pragma once

#include "M_Object.h"
#include <boost/property_tree/ptree.hpp>

namespace minty
{
	/// <summary>
	/// Provides an interface for serializing and deserializing an object. Each respective method will be called when the object is being (de)serialized.
	/// 
	/// This abstract class can be used with any of the serialization methods, such as Json, binary, etc.
	/// </summary>
	class MINTY_API Saveable
		: public Object
	{
	public:
		/// <summary>
		/// Serializes the object. Saves the object into the given ptree.
		/// </summary>
		/// <param name="ptree"></param>
		virtual void serialize(boost::property_tree::ptree& ptree) = 0;

		/// <summary>
		/// Deseralizes the object. Extracts object values from the given ptree.
		/// </summary>
		/// <param name="ptree"></param>
		virtual void deserialize(boost::property_tree::ptree const& ptree) = 0;
	};
}