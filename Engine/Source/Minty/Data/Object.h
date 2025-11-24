#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"
#include "Minty/Data/ConstantContainer.h"

namespace Minty
{
	/// <summary>
	/// A collection of named Variables.
	/// </summary>
	class Object
	{
#pragma region Variables

	private:
		Vector<Tuple<String, Variable>> m_variables;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Object.
		/// </summary>
		Object()
			: m_variables()
		{
		}

		/// <summary>
		/// Creates an empty Object with the given name and capacity.
		/// </summary>
		/// <param name="capcity">The Variable capacity.</param>
		Object(Size const capcity)
			: m_variables(capcity)
		{
		}

		/// <summary>
		/// Creates an Object with the given name and list of Variables.
		/// </summary>
		/// <param name="list">A list of names and Variables.</param>
		Object(std::initializer_list<Tuple<String, Variable>> const& list)
			: m_variables(list)
		{
		}

		/// <summary>
		/// Creates an Object with the given name and list of Variables.
		/// </summary>
		/// <param name="variables">The Variables.</param>
		Object(Vector<Tuple<String, Variable>> const& variables)
			: m_variables(variables)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets a Vector of all the Variables in this Object.
		/// </summary>
		/// <returns>The list.</returns>
		Vector<Tuple<String, Variable>> const& get_variables() const { return m_variables; }

		/// <summary>
		/// Gets the number of Variables in this Object.
		/// </summary>
		/// <returns>The size.</returns>
		Size get_size() const { return m_variables.get_size(); }

		/// <summary>
		/// Checks if this Object is empty.
		/// </summary>
		/// <returns>True if no Variables are in this Object.</returns>
		Bool is_empty() const { return m_variables.is_empty(); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if this Object has a Variable with the given name.
		/// </summary>
		/// <param name="name">The name of the Variable.</param>
		/// <returns>True if a Variable with the given name exists.</returns>
		Bool contains(String const& name) const;

		/// <summary>
		/// Gets the Variable with the given name.
		/// </summary>
		/// <param name="name">The name of the Variable.</param>
		/// <returns>A const reference to the Variable.</returns>
		Variable const& at(String const& name) const;

		/// <summary>
		/// Gets the Variable with the given name.
		/// </summary>
		/// <param name="name">The name of the Variable.</param>
		/// <returns>A const reference to the Variable.</returns>
		Variable& at(String const& name);

		/// <summary>
		/// Adds a Variable to this Object.
		/// </summary>
		/// <param name="name">The name of the Variable.</param>
		/// <param name="variable">The Variable.</param>
		void add(String const& name, Variable const& variable);

		/// <summary>
		/// Sets the Variable with the given name.
		/// </summary>
		/// <param name="name">The name of the Variable.</param>
		/// <param name="variable">The Variable.</param>
		void set(String const& name, Variable const& variable);

		/// <summary>
		/// Removes the Variable with the given name.
		/// </summary>
		/// <param name="name">The name of the Variable.</param>
		/// <returns>True if a Variable with the given name was removed.</returns>
		Bool remove(String const& name);

		/// <summary>
		/// Packs the data within this Cargo into a byte array.
		/// </summary>
		/// <returns>A ConstContainer containing the byte data.</returns>
		ConstantContainer pack() const;

#pragma endregion

	};
}