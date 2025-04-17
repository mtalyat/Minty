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

	private:
		struct Parameter
		{
			String name = "";
			Int argc = 0;
		};

		struct Argument
		{
			Vector<String> args;
		};

#pragma endregion

#pragma region Variables

	private:
		Vector<Parameter> m_positionalParams;
		Vector<Parameter> m_flagParams;
		Map<String, Int> m_flagIndices;
		Map<String, Argument> m_args;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Adds a positional parameter to the list of parameters to parse for.
		/// </summary>
		/// <param name="name">The name of the parameter.</param>
		/// <param name="argc">The maximum number of string arguments to capture. Set to zero to be optional Must be at least 0.</param>
		void add_parameter(String const& name, Int const argc = 1);

		/// <summary>
		/// Adds a flag parameter to the list of parameters to parse for. Flag parameters are denoted by either "-name" or "-flag".
		/// </summary>
		/// <param name="name">The name of the parameter.</param>
		/// <param name="flag">The flag identifier. Optional.</param>
		/// <param name="argc">The number of following arguments after the flag. Must be at least 0.</param>
		void add_parameter(String const& name, String const& flag, Int const argc = 1);

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
		Vector<String> const& get_argument(String const& name);

		/// <summary>
		/// Checks if the argument was provided.
		/// </summary>
		/// <param name="name">The name of the parameter.</param>
		/// <returns>True if there was an argument provided with the name of the given parameter.</returns>
		inline Bool has_argument(String const& name) const
		{
			return m_args.contains(name);
		}

#pragma endregion
	};
}