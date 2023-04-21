#pragma once

#include "M_Main.h"
#include "M_Saveable.h"

namespace minty
{ 
	/// <summary>
	/// Serializes the given object into a json string.
	/// </summary>
	/// <param name="obj">The object to serialize.</param>
	/// <param name="text">The json text.</param>
	/// <param name="pretty">Should the json text be formatted in a more readable way?</param>
	void serialize_json(Saveable* const obj, std::string& text, bool const pretty);

	/// <summary>
	/// Deserializes the given json string into the given object.
	/// </summary>
	/// <param name="text">The json text.</param>
	/// <param name="obj">The object to load values into.</param>
	void deserialize_json(std::string const& text, Saveable* const obj);
}