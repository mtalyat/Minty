#include "pch.h"
#include "Evaluate.h"
#include "Minty/Data/Set.h"
#include <regex>
#include <string>

using namespace Minty;

// checks if the given string is the name of a function
Bool Minty::Internal::is_function(String const& str)
{
	// TODO: implement a list of functions
	return false;
}

Int Minty::Internal::operator_precedence(String const& str)
{
	static Map<String, Int> const precedence =
	{
		{"~", 5}, // Bitwise NOT
		{"**", 4}, // Exponent
		{"*", 3}, // Multiply
		{"/", 3}, // Divide
		{"%", 3}, // Modulo
		{"+", 2}, // Add
		{"-", 2}, // Subtract
		{"<<", 1}, // Bitwise Left Shift
		{">>", 1}, // Bitwise Right Shift
		{"&", 0}, // Bitwise AND
		{"|", 0}, // Bitwise OR
		{"^", 0}, // Bitwise XOR
	};

	auto found = precedence.find(str);

	if (found == precedence.end())
	{
		return 0; // not an operator
	}
	else
	{
		return found->get_second();
	}
}

Int Minty::Internal::operator_count(String const& str)
{
	static Map<String, Int> const precedence =
	{
		{"~", 1}, // Bitwise NOT
		{"**", 2}, // Exponent
		{"*", 2}, // Multiply
		{"/", 2}, // Divide
		{"%", 2}, // Modulo
		{"+", 2}, // Add
		{"-", 2}, // Subtract
		{"<<", 2}, // Bitwise Left Shift
		{">>", 2}, // Bitwise Right Shift
		{"&", 2}, // Bitwise AND
		{"|", 2}, // Bitwise OR
		{"^", 2}, // Bitwise XOR
	};

	auto found = precedence.find(str);

	if (found == precedence.end())
	{
		return 0; // not an operator
	}
	else
	{
		return found->get_second();
	}
}

Bool Minty::Internal::operator_left_to_right(String const& str)
{
	static Set<String> rightToLeft
	{
		"**", // Exponent
	};

	return !rightToLeft.contains(str);
}

template<>
Float Minty::Internal::evaluate_operator(String const& token, Float const left, Float const right)
{
	// operator
	if (token == "**")
	{
		return Math::pow(left, right);
	}
	if (token == "*")
	{
		return left * right;
	}
	else if (token == "/")
	{
		MINTY_ASSERT(right != 0.0f, "Attempt to divide by zero.");
		return left / right;
	}
	else if (token == "%")
	{
		MINTY_ASSERT(right != 0.0f, "Attempt to divide by zero.");
		return Math::mod(left, right);
	}
	else if (token == "+")
	{
		return left + right;
	}
	else if (token == "-")
	{
		return left - right;
	}
	else
	{
		MINTY_ABORT(F("Invalid operator: {}", token));
	}
}

template<>
Double Minty::Internal::evaluate_operator(String const& token, Double const left, Double const right)
{
	// operator
	if (token == "**")
	{
		return Math::pow(left, right);
	}
	if (token == "*")
	{
		return left * right;
	}
	else if (token == "/")
	{
		MINTY_ASSERT(right != 0.0f, "Attempt to divide by zero.");
		return left / right;
	}
	else if (token == "%")
	{
		MINTY_ASSERT(right != 0.0f, "Attempt to divide by zero.");
		return Math::mod(left, right);
	}
	else if (token == "+")
	{
		return left + right;
	}
	else if (token == "-")
	{
		return left - right;
	}
	else
	{
		MINTY_ABORT(F("Invalid operator: {}", token));
	}
}

// splits the expression into String tokens
Vector<String> Minty::Internal::split_into_tokens(String const& expression) {
	std::regex tokenRegex(R"(0[xX][a-fA-F0-9]+|0[bB][01]+|-?\d+(\.\d+)?|[a-zA-Z]+|\+|\-|\*\*|\*|\/|\%|\&|\||\^|\~|\(|\))");
	Vector<String> tokens;

	std::string stdExpression = expression.get_data();
	auto words_begin = std::sregex_iterator(stdExpression.begin(), stdExpression.end(), tokenRegex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		tokens.add((*i).str().c_str());
	}

	return tokens;
}

Vector<String> Minty::Internal::split_into_args(String const& expression)
{
	MINTY_ASSERT(!expression.is_empty(), "Expression is empty.");
	MINTY_ASSERT(expression.front() == '(', "Expression must start with '('.");
	MINTY_ASSERT(expression.back() == ')', "Expression must end with ')'.");

	// remove ()
	String text = expression.sub(1, expression.get_size() - 2);

	// split by commas, but ignore commas inside parentheses
	return text.split_smart(',', "(", ")");
}
