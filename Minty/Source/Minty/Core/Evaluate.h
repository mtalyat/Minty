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
	// forward declaration so this can be used internally
	namespace Math
	{
		template<typename T>
		T evaluate(String const&);
	}

	namespace Internal
	{
		// attempts to get a constant value from the given string
		template<typename T>
		Bool try_get_constant(String const& str, T& value)
		{
			static Map<String, T> const constants =
			{
				{"PI", static_cast<T>(Math::PI)},
				{"BYTE", static_cast<T>(sizeof(Byte))},
				{"CHAR", static_cast<T>(sizeof(Char))},
				{"SHORT", static_cast<T>(sizeof(Short))},
				{"USHORT", static_cast<T>(sizeof(UShort))},
				{"INT", static_cast<T>(sizeof(Int))},
				{"INT2", static_cast<T>(sizeof(Int2))},
				{"INT3", static_cast<T>(sizeof(Int3))},
				{"INT4", static_cast<T>(sizeof(Int4))},
				{"UINT", static_cast<T>(sizeof(UInt))},
				{"UINT2", static_cast<T>(sizeof(UInt2))},
				{"UINT3", static_cast<T>(sizeof(UInt3))},
				{"UINT4", static_cast<T>(sizeof(UInt4))},
				{"LONG", static_cast<T>(sizeof(Long))},
				{"LONG2", static_cast<T>(sizeof(Long2))},
				{"LONG3", static_cast<T>(sizeof(Long3))},
				{"LONG4", static_cast<T>(sizeof(Long4))},
				{"ULONG", static_cast<T>(sizeof(ULong))},
				{"ULONG2", static_cast<T>(sizeof(ULong2))},
				{"ULONG3", static_cast<T>(sizeof(ULong3))},
				{"ULONG4", static_cast<T>(sizeof(ULong4))},
				{"SIZE", static_cast<T>(sizeof(Size))},
				{"FLOAT", static_cast<T>(sizeof(Float))},
				{"FLOAT2", static_cast<T>(sizeof(Float2))},
				{"FLOAT3", static_cast<T>(sizeof(Float3))},
				{"FLOAT4", static_cast<T>(sizeof(Float4))},
				{"DOUBLE", static_cast<T>(sizeof(Double))},
				{"DOUBLE2", static_cast<T>(sizeof(Double2))},
				{"DOUBLE3", static_cast<T>(sizeof(Double3))},
				{"DOUBLE4", static_cast<T>(sizeof(Double4))},
				{"MATRIX2", static_cast<T>(sizeof(Matrix2))},
				{"MATRIX3", static_cast<T>(sizeof(Matrix3))},
				{"MATRIX4", static_cast<T>(sizeof(Matrix4))},
				{"QUATERNION", static_cast<T>(sizeof(Quaternion))},
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
		Bool is_function(String const& str);

		// returns the precedence of the given operator as an Int
		// https://en.cppreference.com/w/c/language/operator_precedence
		Int operator_precedence(String const& str);

		// returns the number of operators in the given expression for the given operation
		Int operator_count(String const& str);

		// checks if the operator is left to right associative
		Bool operator_left_to_right(String const& str);

		template<typename T>
		T evaluate_operator(String const& token, T const left, T const right)
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
			else if (token == "<<")
			{
				return left << right;
			}
			else if (token == ">>")
			{
				return left >> right;
			}
			else if (token == "&")
			{
				return left & right;
			}
			else if (token == "|")
			{
				return left | right;
			}
			else if (token == "^")
			{
				return left ^ right;
			}
			else if (token == "~")
			{
				return ~left; // unary operator, only left operand
			}
			else
			{
				MINTY_ABORT(F("Invalid operator: {}", token));
			}
		}

		template<>
		Float evaluate_operator(String const& token, Float const left, Float const right);

		template<>
		Double evaluate_operator(String const& token, Double const left, Double const right);

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
						while (!operators.is_empty() && operators.peek() != "(" && (operatorPrecedence > tokenPrecedence || (operatorPrecedence == tokenPrecedence && operator_left_to_right(token))))
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

		// splits the expression (arg0, arg1, ...) into a Vector of arguments
		Vector<String> split_into_args(String const& expression);

		template<typename T, typename SubT>
		T evaluate_2(String const& expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT(args.get_size() == 2, F("Expected 2 arguments, got {}: {}", args.get_size(), expression));
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1))
			};
		}

		template<typename T, typename SubT>
		T evaluate_3(String const& expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT(args.get_size() == 3, F("Expected 3 arguments, got {}: {}", args.get_size(), expression));
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1)),
				Minty::Math::evaluate<SubT>(args.at(2))
			};
		}

		template<typename T, typename SubT>
		T evaluate_4(String const& expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT(args.get_size() == 4, F("Expected 4 arguments, got {}: {}", args.get_size(), expression));
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1)),
				Minty::Math::evaluate<SubT>(args.at(2)),
				Minty::Math::evaluate<SubT>(args.at(3))
			};
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

			T left = {};
			T right = {};
			Int operationCount;
			for (String const& token : tokens)
			{
				if (parse_try(token, left) || Internal::try_get_constant<T>(token, left))
				{
					// operand, push value onto stack
					stack.push(left);
				}
				else if (operationCount = Internal::operator_count(token))
				{
					if (operationCount >= 2)
					{
						right = stack.pop();
					}
					if (operationCount >= 1)
					{
						left = stack.pop();
					}

					stack.push(Internal::evaluate_operator(token, left, right));
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

		template<>
		inline Int2 evaluate(String const& expression)
		{
			return Internal::evaluate_2<Int2, Int>(expression);
		}
		template<>
		inline Int3 evaluate(String const& expression)
		{
			return Internal::evaluate_3<Int3, Int>(expression);
		}
		template<>
		inline Int4 evaluate(String const& expression)
		{
			return Internal::evaluate_4<Int4, Int>(expression);
		}

		template<>
		inline UInt2 evaluate(String const& expression)
		{
			return Internal::evaluate_2<UInt2, UInt>(expression);
		}
		template<>
		inline UInt3 evaluate(String const& expression)
		{
			return Internal::evaluate_3<UInt3, UInt>(expression);
		}
		template<>
		inline UInt4 evaluate(String const& expression)
		{
			return Internal::evaluate_4<UInt4, UInt>(expression);
		}

		template<>
		inline Long2 evaluate(String const& expression)
		{
			return Internal::evaluate_2<Long2, Long>(expression);
		}
		template<>
		inline Long3 evaluate(String const& expression)
		{
			return Internal::evaluate_3<Long3, Long>(expression);
		}
		template<>
		inline Long4 evaluate(String const& expression)
		{
			return Internal::evaluate_4<Long4, Long>(expression);
		}

		template<>
		inline ULong2 evaluate(String const& expression)
		{
			return Internal::evaluate_2<ULong2, ULong>(expression);
		}
		template<>
		inline ULong3 evaluate(String const& expression)
		{
			return Internal::evaluate_3<ULong3, ULong>(expression);
		}
		template<>
		inline ULong4 evaluate(String const& expression)
		{
			return Internal::evaluate_4<ULong4, ULong>(expression);
		}

		template<>
		inline Float2 evaluate(String const& expression)
		{
			return Internal::evaluate_2<Float2, Float>(expression);
		}
		template<>
		inline Float3 evaluate(String const& expression)
		{
			return Internal::evaluate_3<Float3, Float>(expression);
		}
		template<>
		inline Float4 evaluate(String const& expression)
		{
			return Internal::evaluate_4<Float4, Float>(expression);
		}

		template<>
		inline Double2 evaluate(String const& expression)
		{
			return Internal::evaluate_2<Double2, Double>(expression);
		}
		template<>
		inline Double3 evaluate(String const& expression)
		{
			return Internal::evaluate_3<Double3, Double>(expression);
		}
		template<>
		inline Double4 evaluate(String const& expression)
		{
			return Internal::evaluate_4<Double4, Double>(expression);
		}
	}
}