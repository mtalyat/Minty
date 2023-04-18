#pragma once

#include "M_Main.h"
#include "M_Saveable.h"

namespace minty
{
	void serialize_json(Saveable* const obj, std::string& text, bool const pretty);

	void deserialize_json(std::string const& text, Saveable* const obj);
}