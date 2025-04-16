#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/// <summary>
	/// Handles parsing the command line.
	/// </summary>
	class ArgumentParser
	{
#pragma region Classes

	public:
		/// <summary>
		/// Defines a command line parameter.
		/// </summary>
		struct Parameter
		{
			/// <summary>
			/// The type of parameter.
			/// </summary>
			enum Type
			{
				/// <summary>
				/// The parameter is identified by its position in the order of the parameters.
				/// </summary>
				POSITIONAL,

				/// <summary>
				/// The parameter is identified by a preceeding flag, such as "-f".
				/// </summary>
				FLAG,
			};

			Type type;
			String name;
			String flag;
			Int index;
			Int argc;

			/// <summary>
			/// Creates an empty Parameter.
			/// </summary>
			Parameter()
				: type(Type::POSITIONAL)
				, name("")
				, flag("")
				, index(0)
				, argc(0)
			{
			}

			/// <summary>
			/// Creates a new positional parameter.
			/// </summary>
			/// <param name="name">The name of the parameter, to get the argument values later.</param>
			/// <param name="index">The index of the parameter, including the name of the program.</param>
			/// <param name="argc">The maximum number of string arguments to capture.</param>
			Parameter(String const& name, Int const index, Int const argc = 1)
				: type(Type::POSITIONAL)
				, name(name)
				, flag("")
				, index(index)
				, argc(argc)
			{
			}

			/// <summary>
			/// Creates a new flag parameter.
			/// </summary>
			/// <param name="name">The name of the parameter, to get the argument values later.</param>
			/// <param name="flag">The index of the parameter, including the name of the program.</param>
			/// <param name="argc">The maximum number of string arguments to capture.</param>
			Parameter(String const& name, String const& flag, Int const argc = 1)
				: type(Type::FLAG)
				, name(name)
				, flag(flag)
				, index(-1)
				, argc(argc)
			{
			}
		};

		/// <summary>
		/// Defines an command line argument given in place of a command line parameter.
		/// </summary>
		struct Argument
		{
			Vector<String> args;
		};

#pragma endregion

#pragma region Variables

	private:
		Map<Int, Parameter> m_positionalParams;
		Map<String, Parameter> m_flagParams;
		Map<String, Argument> m_args;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Adds the parameter to the list of parameters to parse for.
		/// </summary>
		/// <param name="param">The paramter to add.</param>
		void add_parameter(Parameter const& param);

		/// <summary>
		/// Parses the loaded parameters.
		/// </summary>
		/// <param name="argc">The number of args to parse.</param>
		/// <param name="argv">The arguments to parse.</param>
		void parse(Int const argc, Char const* argv[]);

		/// <summary>
		/// Gets the argument by name, if the argument was provided.
		/// </summary>
		/// <param name="name">The name of the parameter.</param>
		/// <param name="arg">The argument to fill with the values.</param>
		/// <returns>True if the argument was found.</returns>
		Bool get_argument(String const& name, Argument& arg);

		/// <summary>
		/// Checks if the argument was provided, using the given parameter name.
		/// </summary>
		/// <param name="name">The name of the parameter to check if it exists.</param>
		/// <returns>True if the argument was given.</returns>
		Bool get_argument(String const& name);

#pragma endregion
	};
}