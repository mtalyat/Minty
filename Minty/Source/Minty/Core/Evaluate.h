#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Data/String.h"

namespace Minty::Math
{
	/// <summary>
	/// Evaluates the given expression and returns the result as a Float.
	/// </summary>
	/// <param name="expression">The expression to evaluate.</param>
	/// <returns>The resolved value.</returns>
	Float evaluate(String const& expression);
}