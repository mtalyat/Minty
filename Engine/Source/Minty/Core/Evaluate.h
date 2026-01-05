#ifndef MINTY_CORE_EVALUATE_H
#define MINTY_CORE_EVALUATE_H

/**
 * @file Evaluate.h
 * @brief Header file defining expression evaluation utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	// forward declaration so this can be used internally
	namespace Math
	{
		template <typename T>
		T evaluate(String const &);
	}

	namespace Internal
	{
		// attempts to get a constant value from the given string
		template <typename T>
		Bool try_get_constant(String const &str, T &value)
		{
			static Map<String, T> const constants =
				{
					{"PI", static_cast<T>(Math::PI)},
					{"BYTE", static_cast<T>(sizeof(Byte))},
					{"CHAR", static_cast<T>(sizeof(Char))},
					{"INT8", static_cast<T>(sizeof(Int8))},
					{"INT16", static_cast<T>(sizeof(Int16))},
					{"INT32", static_cast<T>(sizeof(Int32))},
					{"INT64", static_cast<T>(sizeof(Int64))},
					{"UINT8", static_cast<T>(sizeof(UInt8))},
					{"UINT16", static_cast<T>(sizeof(UInt16))},
					{"UINT32", static_cast<T>(sizeof(UInt32))},
					{"UINT64", static_cast<T>(sizeof(UInt64))},
					{"FLOAT32", static_cast<T>(sizeof(Float32))},
					{"FLOAT64", static_cast<T>(sizeof(Float64))},
					{"BOOL", static_cast<T>(sizeof(Bool))},
					{"INT", static_cast<T>(sizeof(Int))},
					{"INT2", static_cast<T>(sizeof(Int2))},
					{"INT3", static_cast<T>(sizeof(Int3))},
					{"INT4", static_cast<T>(sizeof(Int4))},
					{"UINT", static_cast<T>(sizeof(UInt))},
					{"UINT2", static_cast<T>(sizeof(UInt2))},
					{"UINT3", static_cast<T>(sizeof(UInt3))},
					{"UINT4", static_cast<T>(sizeof(UInt4))},
					{"WINT", static_cast<T>(sizeof(WInt))},
					{"WINT2", static_cast<T>(sizeof(WInt2))},
					{"WINT3", static_cast<T>(sizeof(WInt3))},
					{"WINT4", static_cast<T>(sizeof(WInt4))},
					{"UWINT", static_cast<T>(sizeof(WUInt))},
					{"UWINT2", static_cast<T>(sizeof(UWInt2))},
					{"UWINT3", static_cast<T>(sizeof(UWInt3))},
					{"UWINT4", static_cast<T>(sizeof(UWInt4))},
					{"SIZE", static_cast<T>(sizeof(Size))},
					{"FLOAT", static_cast<T>(sizeof(Float))},
					{"FLOAT2", static_cast<T>(sizeof(Float2))},
					{"FLOAT3", static_cast<T>(sizeof(Float3))},
					{"FLOAT4", static_cast<T>(sizeof(Float4))},
					{"WFLOAT", static_cast<T>(sizeof(WFloat))},
					{"WFLOAT2", static_cast<T>(sizeof(WFloat2))},
					{"WFLOAT3", static_cast<T>(sizeof(WFloat3))},
					{"WFLOAT4", static_cast<T>(sizeof(WFloat4))},
					{"MATRIX2", static_cast<T>(sizeof(Matrix2))},
					{"MATRIX3", static_cast<T>(sizeof(Matrix3))},
					{"MATRIX4", static_cast<T>(sizeof(Matrix4))},
					{"QUATERNION", static_cast<T>(sizeof(Quaternion))},
					{"B", static_cast<T>(B)},
					{"KB", static_cast<T>(KB)},
					{"MB", static_cast<T>(MB)},
					{"GB", static_cast<T>(GB)}};

			String fixedStr = str.to_upper();

			if (fixedStr == "RANDOM")
			{
				if constexpr (std::is_same_v<T, Float>)
				{
					value = static_cast<T>(Math::random_float());
					return true;
				}
				else if constexpr (std::is_same_v<T, WFloat>)
				{
					value = static_cast<T>(Math::random_double());
					return true;
				}
				else if constexpr (std::is_same_v<T, Int>)
				{
					value = static_cast<T>(Math::random_int());
					return true;
				}
				else if constexpr (std::is_same_v<T, UInt>)
				{
					value = static_cast<T>(Math::random_uint());
					return true;
				}
				else if constexpr (std::is_same_v<T, WInt>)
				{
					value = static_cast<T>(Math::random_long());
					return true;
				}
				else if constexpr (std::is_same_v<T, WUInt>)
				{
					value = static_cast<T>(Math::random_ulong());
					return true;
				}
				else
				{
					// assume a small type
					value = static_cast<T>(Math::random_long());
					return true;
				}
			}

			auto found = constants.find(fixedStr);
			if (found == constants.end())
			{
				return false;
			}

			value = found->get_second();
			return true;
		}

		// checks if the given string is the name of a function
		Bool is_function(String const &str);

		// returns the precedence of the given operator as an Int
		// https://en.cppreference.com/w/c/language/operator_precedence
		Int operator_precedence(String const &str);

		// returns the number of operators in the given expression for the given operation
		Int operator_count(String const &str);

		// checks if the operator is left to right associative
		Bool operator_left_to_right(String const &str);

		template <typename T>
		T evaluate_operator(String const &token, T const left, T const right)
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
				MINTY_ASSERT(right != 0.0f, ErrorCode::Math_DivideByZero);
				return left / right;
			}
			else if (token == "%")
			{
				MINTY_ASSERT(right != 0.0f, ErrorCode::Math_DivideByZero);
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
				MINTY_ABORT_F(ErrorCode::Math_InvalidToken, token);
			}
		}

		template <>
		Float evaluate_operator(String const &token, Float const left, Float const right);

		template <>
		WFloat evaluate_operator(String const &token, WFloat const left, WFloat const right);

		// splits the expression into String tokens
		Vector<String> split_into_tokens(String const &expression);

		// https://en.wikipedia.org/wiki/Shunting_yard_algorithm
		template <typename T>
		void sort_infix_to_postfix(Vector<String> &tokens)
		{
			// copy over to new Vector
			Vector<String> unsortedTokens(tokens);

			// clear output
			tokens.clear();

			// temp stack of operators
			Stack<String> operators;

			String token;
			Float value;
			for (auto const &token : unsortedTokens)
			{
				T t;
				if (Parser<T>::parse(token, t) || try_get_constant(token, value))
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

					MINTY_ASSERT(!operators.is_empty(), ErrorCode::Math_MismatchedParentheses);

					operators.pop();

					if (!operators.is_empty() && is_function(operators.peek()))
					{
						tokens.add(operators.pop());
					}
				}
				else
				{
					MINTY_ABORT_F(ErrorCode::Math_InvalidToken, token);
				}
			}

			while (!operators.is_empty())
			{
				MINTY_ASSERT(operators.peek() != "(", ErrorCode::Math_MismatchedParentheses);

				tokens.add(operators.pop());
			}
		}

		// splits the expression (arg0, arg1, ...) into a Vector of arguments
		Vector<String> split_into_args(String const &expression);

		template <typename T, typename SubT>
		T evaluate_2(String const &expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT_F(args.get_size() == 2, ErrorCode::Argument_InvalidFormat, expression);
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1))};
		}

		template <typename T, typename SubT>
		T evaluate_3(String const &expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT_F(args.get_size() == 3, ErrorCode::Argument_InvalidFormat, expression);
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1)),
				Minty::Math::evaluate<SubT>(args.at(2))};
		}

		template <typename T, typename SubT>
		T evaluate_4(String const &expression)
		{
			Vector<String> args = Internal::split_into_args(expression);
			MINTY_ASSERT_F(args.get_size() == 4, ErrorCode::Argument_InvalidFormat, expression);
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1)),
				Minty::Math::evaluate<SubT>(args.at(2)),
				Minty::Math::evaluate<SubT>(args.at(3))};
		}
	}

	namespace Math
	{
		/**
		 * @brief Evaluates the given expression and returns the result.
		 * @tparam T The type to use to evaluate.
		 * @param expression The string to evaluate. Expects a math expression in infix notation.
		 * @return The result.
		 */
		template <typename T>
		T evaluate(String const &expression)
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
			for (String const &token : tokens)
			{
				if (Parser<T>::parse(token, left) || Internal::try_get_constant<T>(token, left))
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
					MINTY_ABORT_F(ErrorCode::Math_InvalidToken, token);
				}
			}

			MINTY_ASSERT_F(stack.get_size() == 1, ErrorCode::Math_EvaluationFailed, expression);

			// last value left on stack should be the result
			return stack.peek();
		}

		/**
		 * @brief Evaluates an expression into an Int2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Int2 result.
		 */
		template <>
		inline Int2 evaluate(String const &expression)
		{
			return Internal::evaluate_2<Int2, Int>(expression);
		}
		/**
		 * @brief Evaluates an expression into an Int3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Int3 result.
		 */
		template <>
		inline Int3 evaluate(String const &expression)
		{
			return Internal::evaluate_3<Int3, Int>(expression);
		}
		/**
		 * @brief Evaluates an expression into an Int4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Int4 result.
		 */
		template <>
		inline Int4 evaluate(String const &expression)
		{
			return Internal::evaluate_4<Int4, Int>(expression);
		}

		/**
		 * @brief Evaluates an expression into a UInt2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated UInt2 result.
		 */
		template <>
		inline UInt2 evaluate(String const &expression)
		{
			return Internal::evaluate_2<UInt2, UInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a UInt3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated UInt3 result.
		 */
		template <>
		inline UInt3 evaluate(String const &expression)
		{
			return Internal::evaluate_3<UInt3, UInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a UInt4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated UInt4 result.
		 */
		template <>
		inline UInt4 evaluate(String const &expression)
		{
			return Internal::evaluate_4<UInt4, UInt>(expression);
		}

		/**
		 * @brief Evaluates an expression into a WInt2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WInt2 result.
		 */
		template <>
		inline WInt2 evaluate(String const &expression)
		{
			return Internal::evaluate_2<WInt2, WInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WInt3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WInt3 result.
		 */
		template <>
		inline WInt3 evaluate(String const &expression)
		{
			return Internal::evaluate_3<WInt3, WInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WInt4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WInt4 result.
		 */
		template <>
		inline WInt4 evaluate(String const &expression)
		{
			return Internal::evaluate_4<WInt4, WInt>(expression);
		}

		/**
		 * @brief Evaluates an expression into a ULong2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated ULong2 result.
		 */
		template <>
		inline UWInt2 evaluate(String const &expression)
		{
			return Internal::evaluate_2<UWInt2, WUInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a ULong3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated ULong3 result.
		 */
		template <>
		inline UWInt3 evaluate(String const &expression)
		{
			return Internal::evaluate_3<UWInt3, WUInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a ULong4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated ULong4 result.
		 */
		template <>
		inline UWInt4 evaluate(String const &expression)
		{
			return Internal::evaluate_4<UWInt4, WUInt>(expression);
		}

		/**
		 * @brief Evaluates an expression into a Float2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Float2 result.
		 */
		template <>
		inline Float2 evaluate(String const &expression)
		{
			return Internal::evaluate_2<Float2, Float>(expression);
		}
		/**
		 * @brief Evaluates an expression into a Float3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Float3 result.
		 */
		template <>
		inline Float3 evaluate(String const &expression)
		{
			return Internal::evaluate_3<Float3, Float>(expression);
		}
		/**
		 * @brief Evaluates an expression into a Float4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Float4 result.
		 */
		template <>
		inline Float4 evaluate(String const &expression)
		{
			return Internal::evaluate_4<Float4, Float>(expression);
		}

		/**
		 * @brief Evaluates an expression into a WFloat2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WFloat2 result.
		 */
		template <>
		inline WFloat2 evaluate(String const &expression)
		{
			return Internal::evaluate_2<WFloat2, WFloat>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WFloat3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WFloat3 result.
		 */
		template <>
		inline WFloat3 evaluate(String const &expression)
		{
			return Internal::evaluate_3<WFloat3, WFloat>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WFloat4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WFloat4 result.
		 */
		template <>
		inline WFloat4 evaluate(String const &expression)
		{
			return Internal::evaluate_4<WFloat4, WFloat>(expression);
		}
	}
}

#endif // MINTY_CORE_EVALUATE_H