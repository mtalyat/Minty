#pragma once

/**
 * @file Evaluate.h
 * @brief Header file defining expression evaluation utilities.
 * @author Mitchell Talyat
 */

#include "Math.hpp"
#include "Random.hpp"
#include "Core/Tool/Format.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/Stack.hpp"
#include "Core/Data/String.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Serialize/Parser.hpp"

#include "Core/Type/__Type.hpp"
#include "Core/Math/Matrix2x2.hpp"
#include "Core/Math/Matrix3x3.hpp"
#include "Core/Math/Matrix4x4.hpp"
#include "Core/Math/Quaternion.hpp"
#include "Core/Constant/Convert.hpp"

namespace Minty
{
	// forward declaration so this can be used internally
	namespace Math
	{
		template <typename T>
		T evaluate(StringView const);
	}

	namespace Internal
	{
		// attempts to get a constant value from the given string
		template <typename T>
		Bool try_get_constant(StringView const str, T &value)
		{
			static Map<StringView, T> const constants =
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
					{"WUINT", static_cast<T>(sizeof(WUInt))},
					{"WUINT2", static_cast<T>(sizeof(WUInt2))},
					{"WUINT3", static_cast<T>(sizeof(WUInt3))},
					{"WUINT4", static_cast<T>(sizeof(WUInt4))},
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

			if (str == "RANDOM")
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

			auto found = constants.find(str);
			if (found == constants.end())
			{
				return false;
			}

			value = found->get_second();
			return true;
		}

		// checks if the given string is the name of a function
		Bool is_function(StringView const str);

		// returns the precedence of the given operator as an Int
		// https://en.cppreference.com/w/c/language/operator_precedence
		Int operator_precedence(StringView const str);

		// returns the number of operators in the given expression for the given operation
		Int operator_count(StringView const str);

		// checks if the operator is left to right associative
		Bool operator_left_to_right(StringView const str);

		template <typename T>
		T evaluate_operator(StringView const token, T const left, T const right)
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
				MINTY_ABORT_A(ErrorCodeEnum::Math_InvalidToken, token.get_data());
			}
		}

		template <>
		Float evaluate_operator(StringView const token, Float const left, Float const right);

		template <>
		WFloat evaluate_operator(StringView const token, WFloat const left, WFloat const right);

		// splits the expression into String tokens
		Vector<StringView> split_into_tokens(StringView const expression);

		// https://en.wikipedia.org/wiki/Shunting_yard_algorithm
		template <typename T>
		void sort_infix_to_postfix(Vector<StringView> &tokens)
		{
			// copy over to new Vector
			Vector<StringView> unsortedTokens(tokens);

			// clear output
			tokens.clear(); 

			// temp stack of operators
			Stack<StringView> operators;

			StringView token;
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

					MINTY_CHECK(!operators.is_empty(), ErrorCodeEnum::Math_MismatchedParentheses);

					operators.pop();

					if (!operators.is_empty() && is_function(operators.peek()))
					{
						tokens.add(operators.pop());
					}
				}
				else
				{
					MINTY_ERROR_A(ErrorCodeEnum::Math_InvalidToken, token.get_data());
				}
			}

			while (!operators.is_empty())
			{
				MINTY_CHECK(operators.peek() != "(", ErrorCodeEnum::Math_MismatchedParentheses);

				tokens.add(operators.pop());
			}
		}

		// splits the expression (arg0, arg1, ...) into a Vector of arguments
		Vector<StringView> split_into_args(StringView const expression);

		template <typename T, typename SubT>
		T evaluate_2(StringView const expression)
		{
			Vector<StringView> args = Internal::split_into_args(expression);
			MINTY_CHECK_A(args.get_size() == 2, ErrorCodeEnum::Argument_InvalidFormat, expression.get_data());
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1))};
		}

		template <typename T, typename SubT>
		T evaluate_3(StringView const expression)
		{
			Vector<StringView> args = Internal::split_into_args(expression);
			MINTY_CHECK_A(args.get_size() == 3, ErrorCodeEnum::Argument_InvalidFormat, expression.get_data());
			return T{
				Minty::Math::evaluate<SubT>(args.at(0)),
				Minty::Math::evaluate<SubT>(args.at(1)),
				Minty::Math::evaluate<SubT>(args.at(2))};
		}

		template <typename T, typename SubT>
		T evaluate_4(StringView const expression)
		{
			Vector<StringView> args = Internal::split_into_args(expression);
			MINTY_CHECK_A(args.get_size() == 4, ErrorCodeEnum::Argument_InvalidFormat, expression.get_data());
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
		T evaluate(StringView const expression)
		{
			// if empty, return default value
			if (expression.is_empty())
			{
				return T{};
			}
			
			// get tokens
			Vector<StringView> tokens = Internal::split_into_tokens(expression);

			// sort into postfix
			Internal::sort_infix_to_postfix<T>(tokens);

			// evaluate
			Stack<T> stack;

			T left = {};
			T right = {};
			Int operationCount;
			for (StringView const token : tokens)
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
					// TODO: functions
					MINTY_NOT_IMPLEMENTED();
				}
				else
				{
					// something else
					MINTY_ABORT_A(ErrorCodeEnum::Math_InvalidToken, token.get_data());
				}
			}

			if(stack.get_size() != 1)
			{
				MINTY_ERROR_A(ErrorCodeEnum::Math_EvaluationFailed, expression.get_data());
				
				// return default value for safety
				return T{};
			}

			// last value left on stack should be the result
			return stack.peek();
		}

		/**
		 * @brief Evaluates an expression into an Int2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Int2 result.
		 */
		template <>
		inline Int2 evaluate(StringView const expression)
		{
			return Internal::evaluate_2<Int2, Int>(expression);
		}
		/**
		 * @brief Evaluates an expression into an Int3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Int3 result.
		 */
		template <>
		inline Int3 evaluate(StringView const expression)
		{
			return Internal::evaluate_3<Int3, Int>(expression);
		}
		/**
		 * @brief Evaluates an expression into an Int4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Int4 result.
		 */
		template <>
		inline Int4 evaluate(StringView const expression)
		{
			return Internal::evaluate_4<Int4, Int>(expression);
		}

		/**
		 * @brief Evaluates an expression into a UInt2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated UInt2 result.
		 */
		template <>
		inline UInt2 evaluate(StringView const expression)
		{
			return Internal::evaluate_2<UInt2, UInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a UInt3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated UInt3 result.
		 */
		template <>
		inline UInt3 evaluate(StringView const expression)
		{
			return Internal::evaluate_3<UInt3, UInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a UInt4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated UInt4 result.
		 */
		template <>
		inline UInt4 evaluate(StringView const expression)
		{
			return Internal::evaluate_4<UInt4, UInt>(expression);
		}

		/**
		 * @brief Evaluates an expression into a WInt2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WInt2 result.
		 */
		template <>
		inline WInt2 evaluate(StringView const expression)
		{
			return Internal::evaluate_2<WInt2, WInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WInt3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WInt3 result.
		 */
		template <>
		inline WInt3 evaluate(StringView const expression)
		{
			return Internal::evaluate_3<WInt3, WInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WInt4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WInt4 result.
		 */
		template <>
		inline WInt4 evaluate(StringView const expression)
		{
			return Internal::evaluate_4<WInt4, WInt>(expression);
		}

		/**
		 * @brief Evaluates an expression into a ULong2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated ULong2 result.
		 */
		template <>
		inline WUInt2 evaluate(StringView const expression)
		{
			return Internal::evaluate_2<WUInt2, WUInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a ULong3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated ULong3 result.
		 */
		template <>
		inline WUInt3 evaluate(StringView const expression)
		{
			return Internal::evaluate_3<WUInt3, WUInt>(expression);
		}
		/**
		 * @brief Evaluates an expression into a ULong4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated ULong4 result.
		 */
		template <>
		inline WUInt4 evaluate(StringView const expression)
		{
			return Internal::evaluate_4<WUInt4, WUInt>(expression);
		}

		/**
		 * @brief Evaluates an expression into a Float2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Float2 result.
		 */
		template <>
		inline Float2 evaluate(StringView const expression)
		{
			return Internal::evaluate_2<Float2, Float>(expression);
		}
		/**
		 * @brief Evaluates an expression into a Float3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Float3 result.
		 */
		template <>
		inline Float3 evaluate(StringView const expression)
		{
			return Internal::evaluate_3<Float3, Float>(expression);
		}
		/**
		 * @brief Evaluates an expression into a Float4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated Float4 result.
		 */
		template <>
		inline Float4 evaluate(StringView const expression)
		{
			return Internal::evaluate_4<Float4, Float>(expression);
		}

		/**
		 * @brief Evaluates an expression into a WFloat2.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WFloat2 result.
		 */
		template <>
		inline WFloat2 evaluate(StringView const expression)
		{
			return Internal::evaluate_2<WFloat2, WFloat>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WFloat3.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WFloat3 result.
		 */
		template <>
		inline WFloat3 evaluate(StringView const expression)
		{
			return Internal::evaluate_3<WFloat3, WFloat>(expression);
		}
		/**
		 * @brief Evaluates an expression into a WFloat4.
		 * @param expression The string expression to evaluate.
		 * @return The evaluated WFloat4 result.
		 */
		template <>
		inline WFloat4 evaluate(StringView const expression)
		{
			return Internal::evaluate_4<WFloat4, WFloat>(expression);
		}
	}
}
