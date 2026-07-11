#include "pch.h"
#include "Evaluate.h"
#include "Core/Data/Set.h"
#include "Core/Tool/String.h"
#include <regex>
#include <string>

using namespace Minty;

// checks if the given string is the name of a function
Bool Minty::Internal::is_function(StringView const str)
{
	// TODO: implement a list of functions
	return false;
}

Int Minty::Internal::operator_precedence(StringView const str)
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

Int Minty::Internal::operator_count(StringView const str)
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

Bool Minty::Internal::operator_left_to_right(StringView const str)
{
	static Set<String> rightToLeft
	{
		"**", // Exponent
	};

	return !rightToLeft.contains(str);
}

// TODO: make generic that works for float and double together (enable if float type? like is_floating_point?)
template<>
Float Minty::Internal::evaluate_operator(StringView const token, Float const left, Float const right)
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
		MINTY_ASSERT(right != 0.0f, ErrorCodeEnum::Math_DivideByZero);
		return left / right;
	}
	else if (token == "%")
	{
		MINTY_ASSERT(right != 0.0f, ErrorCodeEnum::Math_DivideByZero);
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
		MINTY_ABORT_A(ErrorCodeEnum::Math_InvalidToken, token.get_data());
	}
}

template<>
WFloat Minty::Internal::evaluate_operator(StringView const token, WFloat const left, WFloat const right)
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
		MINTY_ASSERT(right != 0.0f, ErrorCodeEnum::Math_DivideByZero);
		return left / right;
	}
	else if (token == "%")
	{
		MINTY_ASSERT(right != 0.0f, ErrorCodeEnum::Math_DivideByZero);
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
		MINTY_ABORT_A(ErrorCodeEnum::Math_InvalidToken, token.get_data());
	}
}

// splits the expression into String tokens
Vector<StringView> Minty::Internal::split_into_tokens(StringView const expression) {
	std::regex tokenRegex(R"(0[xX][a-fA-F0-9]+|0[bB][01]+|-?\d+(\.\d+)?|[a-zA-Z]+|\+|\-|\*\*|\*|\/|\%|\&|\||\^|\~|\(|\))");
	Vector<StringView> tokens;

	std::string stdExpression = std::string(expression.get_data(), expression.get_size());
	auto words_begin = std::sregex_iterator(stdExpression.begin(), stdExpression.end(), tokenRegex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		size_t index = match.position();
		size_t size = match.length();
		StringView token = expression.sub(index, size);
		tokens.add(std::move(token));
	}

	return tokens;
}

Vector<StringView> Minty::Internal::split_into_args(StringView const expression)
{
	MINTY_ASSERT(!expression.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(expression.front() == '(', ErrorCodeEnum::Argument_InvalidFormat);
	MINTY_ASSERT(expression.back() == ')', ErrorCodeEnum::Argument_InvalidFormat);

	// remove outside ()
	StringView text = expression.sub(1, expression.get_size() - 2);

	// split by commas, but ignore commas inside parentheses
	return Tool::split_smart(text, ',', "(", ")");
}
