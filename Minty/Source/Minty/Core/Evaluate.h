#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	namespace Internal
	{
		// attempts to get a constant value from the given string
		template<typename T>
		Bool try_get_constant(String const& str, T& value)
		{
			static Map<String, T> const constants =
			{
				{"PI", Minty::Math::PI},
				{"FLOAT", static_cast<T>(sizeof(Float))},
				{"DOUBLE", static_cast<T>(sizeof(Double))},
				{"INT", static_cast<T>(sizeof(Int))},
				{"SIZE", static_cast<T>(sizeof(Size))},
				{"BYTE", static_cast<T>(sizeof(Byte))},
				{"CHAR", static_cast<T>(sizeof(Char))},
				{"SHORT", static_cast<T>(sizeof(Short))},
				{"LONG", static_cast<T>(sizeof(Long))},
				{"FLOAT2", static_cast<T>(sizeof(Minty::Float2))},
				{"FLOAT3", static_cast<T>(sizeof(Minty::Float3))},
				{"FLOAT4", static_cast<T>(sizeof(Minty::Float4))},
				{"INT2", static_cast<T>(sizeof(Minty::Int2))},
				{"INT3", static_cast<T>(sizeof(Minty::Int3))},
				{"INT4", static_cast<T>(sizeof(Minty::Int4))},
				{"MATRIX2", static_cast<T>(sizeof(Minty::Matrix2))},
				{"MATRIX3", static_cast<T>(sizeof(Minty::Matrix3))},
				{"MATRIX4", static_cast<T>(sizeof(Minty::Matrix4))},
				{"QUATERNION", static_cast<T>(sizeof(Minty::Quaternion))},
				{"B", static_cast<T>(B)},
				{"KB", static_cast<T>(KB)},
				{"MB", static_cast<T>(MB)},
				{"GB", static_cast<T>(GB)},
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
		Bool is_function(String const& str)
		{
			// TODO: implement a list of functions
			return false;
		}

		// returns the precedence of the given operator as an Int
		// https://en.cppreference.com/w/c/language/operator_precedence
		Int operator_precedence(String const& str);

		// splits the expression into String tokens
		Vector<String> split_into_tokens(String const& expression);

		// https://en.wikipedia.org/wiki/Shunting_yard_algorithm
		template<typename T>
		void sort_infix_to_postfix(Vector<String>& tokens)
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
				T t;
				if (parse_try<T>(token, t) || try_get_constant(token, value))
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

		Vector<String> split_into_args(String const& expression)
		{
			MINTY_ASSERT(!expression.is_empty(), "Expression is empty.");
			MINTY_ASSERT(expression.front() == '(', "Expression must start with '('.");
			MINTY_ASSERT(expression.back() == ')', "Expression must end with ')'.");

			// remove ()
			String text = expression.sub(1, expression.get_size() - 2);

			// split by commas, but ignore commas inside parentheses
			return text.split_smart(',', "(", ")");
		}
	}

	namespace Math
	{
		/// <summary>
		/// Evaluates the given expression and returns the result.
		/// </summary>
		/// <typeparam name="T">The type to use to evaluate.</typeparam>
		/// <param name="expression">The string to evaluate. Expects a math expression in infix notation.</param>
		/// <returns>The result.</returns>
		template<typename T>
		T evaluate(String const& expression)
		{
			// get tokens
			Vector<String> tokens = Internal::split_into_tokens(expression);

			// sort into postfix
			Internal::sort_infix_to_postfix<T>(tokens);

			// evaluate
			Stack<T> stack;

			T left, right;
			for (String const& token : tokens)
			{
				if (parse_try(token, left) || Internal::try_get_constant<T>(token, left))
				{
					// operand, push value onto stack
					stack.push(left);
				}
				else if (Internal::operator_precedence(token))
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
				else if (Internal::is_function(token))
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

		template<typename T, typename SubT>
		T evaluate_2(String const& expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT(args.get_size() == 2, F("Expected 2 arguments, got {}: {}", args.get_size(), expression));
			return T{
				evaluate<SubT>(args.at(0)),
				evaluate<SubT>(args.at(1))
			};
		}

		template<typename T, typename SubT>
		T evaluate_3(String const& expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT(args.get_size() == 3, F("Expected 3 arguments, got {}: {}", args.get_size(), expression));
			return T{
				evaluate<SubT>(args.at(0)),
				evaluate<SubT>(args.at(1)),
				evaluate<SubT>(args.at(2))
			};
		}

		template<typename T, typename SubT>
		T evaluate_4(String const& expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT(args.get_size() == 4, F("Expected 4 arguments, got {}: {}", args.get_size(), expression));
			return T{
				evaluate<SubT>(args.at(0)),
				evaluate<SubT>(args.at(1)),
				evaluate<SubT>(args.at(2)),
				evaluate<SubT>(args.at(3))
			};
		}

		template<>
		Float2 evaluate(String const& expression)
		{
			return evaluate_2<Float2, Float>(expression);
		}
		template<>
		Float3 evaluate(String const& expression)
		{
			return evaluate_3<Float3, Float>(expression);
		}
		template<>
		Float4 evaluate(String const& expression)
		{
			return evaluate_4<Float4, Float>(expression);
		}

		template<>
		Int2 evaluate(String const& expression)
		{
			return evaluate_2<Int2, Int>(expression);
		}
		template<>
		Int3 evaluate(String const& expression)
		{
			return evaluate_3<Int3, Int>(expression);
		}
		template<>
		Int4 evaluate(String const& expression)
		{
			return evaluate_4<Int4, Int>(expression);
		}

		template<>
		UInt2 evaluate(String const& expression)
		{
			return evaluate_2<UInt2, UInt>(expression);
		}
		template<>
		UInt3 evaluate(String const& expression)
		{
			return evaluate_3<UInt3, UInt>(expression);
		}
		template<>
		UInt4 evaluate(String const& expression)
		{
			return evaluate_4<UInt4, UInt>(expression);
		}
	}
}