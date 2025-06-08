#include "pch.h"
#include "Evaluate.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/Vector.h"
#include "Minty/Serialization/Parse.h"
#include <regex>
#include <string>

using namespace Minty;

// checks if the given string is a number
static Bool is_number(String const& str)
{
	Bool decimalPointFound = false;
	for (Char c : str) {
		if (!isdigit(c)) {
			if (c == '.' && !decimalPointFound) {
				decimalPointFound = true;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

// attempts to get a constant value from the given string
Bool try_get_constant(String const& str, Float& value)
{
	static Map<String, float> const constants =
	{
		{"PI", Minty::Math::PI},
		{"FLOAT", static_cast<Float>(sizeof(Float))},
		{"DOUBLE", static_cast<Float>(sizeof(Double))},
		{"INT", static_cast<Float>(sizeof(Int))},
		{"SIZE", static_cast<Float>(sizeof(Size))},
		{"BYTE", static_cast<Float>(sizeof(Byte))},
		{"CHAR", static_cast<Float>(sizeof(Char))},
		{"SHORT", static_cast<Float>(sizeof(Short))},
		{"LONG", static_cast<Float>(sizeof(Long))},
		{"FLOAT2", static_cast<Float>(sizeof(Minty::Float2))},
		{"FLOAT3", static_cast<Float>(sizeof(Minty::Float3))},
		{"FLOAT4", static_cast<Float>(sizeof(Minty::Float4))},
		{"INT2", static_cast<Float>(sizeof(Minty::Int2))},
		{"INT3", static_cast<Float>(sizeof(Minty::Int3))},
		{"INT4", static_cast<Float>(sizeof(Minty::Int4))},
		{"MATRIX2", static_cast<Float>(sizeof(Minty::Matrix2))},
		{"MATRIX3", static_cast<Float>(sizeof(Minty::Matrix3))},
		{"MATRIX4", static_cast<Float>(sizeof(Minty::Matrix4))},
		{"QUATERNION", static_cast<Float>(sizeof(Minty::Quaternion))},
		{"B", static_cast<Float>(B)},
		{"KB", static_cast<Float>(KB)},
		{"MB", static_cast<Float>(MB)},
		{"GB", static_cast<Float>(GB)},
		//{"", static_cast<float>(sizeof())},
	};

	auto found = constants.find(str.to_upper());
	if (found == constants.end())
	{
		return false;
	}

	value = found->get_second();
	return true;
}

// checks if the given string is the name of a function
static Bool is_function(String const& str)
{
	// TODO: implement a list of functions
	return false;
}

// returns the precedence of the given operator as an Int
// https://en.cppreference.com/w/c/language/operator_precedence
static Int operator_precedence(String const& str)
{
	static Map<String, Int> const precedence =
	{
		{"^", 4},
		{"*", 3},
		{"/", 3},
		{"%", 3},
		{"+", 2},
		{"-", 2}
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

// splits the expression into String tokens
static Vector<String> split_into_tokens(String const& expression) {
	std::regex tokenRegex(R"([[:digit:]]+(\.[[:digit:]]+)?|[a-zA-Z]+|\+|\-|\*|\/|\%|\^|\(|\))");
	Vector<String> tokens;

	std::string stdExpression = expression.get_data();
	auto words_begin = std::sregex_iterator(stdExpression.begin(), stdExpression.end(), tokenRegex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		tokens.add((*i).str().c_str());
	}

	return tokens;
}

// https://en.wikipedia.org/wiki/Shunting_yard_algorithm
static void sort_infix_to_postfix(Vector<String>& tokens)
{
	// copy over to new Vector
	Vector<String> unsortedTokens(tokens);

	// clear output
	tokens.clear();

	// temp stack of operators

	Stack<String> operators;

	String token;
	float value;
	for (auto const& token : unsortedTokens)
	{
		if (is_number(token) || try_get_constant(token, value))
		{
			// push value to tokens
			tokens.add(token);
		}
		else if (Int tokenPrecedence = operator_precedence(token))
		{
			if (!operators.is_empty())
			{
				Int operatorPrecedence = operator_precedence(operators.peek());
				while (!operators.is_empty() && operators.peek() != "(" && (operatorPrecedence > tokenPrecedence || (operatorPrecedence == tokenPrecedence && token != "^")))
				{
					tokens.add(operators.pop());
				}
			}
			operators.push(token);
		}
		else if (token == ",")
		{
			while (operators.peek() != "(")
			{
				tokens.add(operators.pop());
			}
		}
		else if (token == "(")
		{
			operators.push(token);
		}
		else if (token == ")")
		{
			while (!operators.is_empty() && operators.peek() != "(")
			{
				tokens.add(operators.pop());
			}

			MINTY_ASSERT(!operators.is_empty(), "Mismatch parenthesis.");

			operators.pop();

			if (!operators.is_empty() && is_function(operators.peek()))
			{
				tokens.add(operators.pop());
			}
		}
		else
		{
			MINTY_ABORT(F("Invalid token: {}", token));
		}
	}

	while (!operators.is_empty())
	{
		MINTY_ASSERT(operators.peek() != "(", "Mismatch parenthesis.");

		tokens.add(operators.pop());
	}
}

Float Minty::Math::evaluate(String const& expression)
{
	// get tokens
	Vector<String> tokens = split_into_tokens(expression);

	// sort into postfix
	sort_infix_to_postfix(tokens);

	// evaluate
	Stack<float> stack;

	float left, right;
	for (String const& token : tokens)
	{
		if (try_float(token, left) || try_get_constant(token, left))
		{
			// operand, push value onto stack
			stack.push(left);
		}
		else if (operator_precedence(token))
		{
			right = stack.pop();
			left = stack.pop();

			// operator
			if (token == "^")
			{
				stack.push(Math::pow(left, right));
			}
			else if (token == "*")
			{
				stack.push(left * right);
			}
			else if (token == "/")
			{
				MINTY_ASSERT(right != 0.0f, "Attempt to divide by zero.");
				stack.push(left / right);
			}
			else if (token == "%")
			{
				MINTY_ASSERT(right != 0.0f, "Attempt to divide by zero.");
				stack.push(Math::mod(left, right));
			}
			else if (token == "+")
			{
				stack.push(left + right);
			}
			else if (token == "-")
			{
				stack.push(left - right);
			}
			else
			{
				MINTY_ABORT(F("Invalid operator: {}", token));
			}
		}
		else if (is_function(token))
		{

		}
		else
		{
			// something else
			MINTY_ABORT(F("Invalid token: {}", token));
		}
	}

	MINTY_ASSERT(stack.get_size() == 1, F("Invalid evaluation, resulted with {} values. (\"{}\").", stack.get_size(), expression));

	// last value left on stack should be the result
	return stack.peek();
}
