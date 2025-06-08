#include "pch.h"
#include "Evaluate.h"
#include <regex>
#include <string>

using namespace Minty;

Int Minty::Internal::operator_precedence(String const& str)
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
Vector<String> Minty::Internal::split_into_tokens(String const& expression) {
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
