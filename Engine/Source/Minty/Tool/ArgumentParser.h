#ifndef MINTY_TOOL_ARGUMENTPARSER_H
#define MINTY_TOOL_ARGUMENTPARSER_H

/**
 * @file ArgumentParser.h
 * @brief Header file defining the ArgumentParser class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/**
	 * @brief Handles parsing the command line.
	 */
	class ArgumentParser
	{
#pragma region Types

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

#pragma region Constructors

	public:
		/**
		 * @brief Creates an ArgumentParser.
		 */
		ArgumentParser()
			: m_positionalParams()
			, m_flagParams()
			, m_flagIndices()
			, m_args()
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Adds a positional parameter to the list of parameters to parse for.
		 * @param name The name of the parameter.
		 * @param argc The maximum number of string arguments to capture. Set to zero to be optional Must be at least 0.
		 */
		void add_parameter(String const& name, Int const argc = 1);

		/**
		 * @brief Adds a flag parameter to the list of parameters to parse for. Flag parameters are denoted by either "-name" or "-flag".
		 * @param name The name of the parameter.
		 * @param flag The flag identifier. Optional.
		 * @param argc The number of following arguments after the flag. Must be at least 0.
		 */
		void add_parameter(String const& name, String const& flag, Int const argc = 1);

		/**
		 * @brief Parses the loaded parameters.
		 * @param argc The number of args to parse.
		 * @param argv The arguments to parse.
		 */
		void parse(Int const argc, Char const* argv[]);

		/**
		 * @brief Gets the argument by name, if the argument was provided.
		 * @param name The name of the parameter.
		 * @param arg The argument to fill with the values.
		 * @return True if the argument was found.
		 */
		Vector<String> const& get_argument(String const& name) const;

		/**
		 * @brief Checks if the argument was provided.
		 * @param name The name of the parameter.
		 * @return True if there was an argument provided with the name of the given parameter.
		 */
		inline Bool has_argument(String const& name) const { return m_args.contains(name); }

#pragma endregion

#pragma region Variables

	private:
		Vector<Parameter> m_positionalParams;
		Vector<Parameter> m_flagParams;
		Map<String, Int> m_flagIndices;
		Map<String, Argument> m_args;

#pragma endregion
	};
}

#endif // MINTY_TOOL_ARGUMENTPARSER_H