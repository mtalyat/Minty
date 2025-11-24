#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Serialization/Parseable.h"

namespace Minty
{
	/// <summary>
	/// An EntityPath is a relational path from an Entity to another Entity.
	/// </summary>
	class EntityPath
		: public Parseable
	{
#pragma region Variables

	private:
		// the path to the (child) entity, relative to the (parent) entity
		Vector<Byte> m_path;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty EntityPath.
		/// </summary>
		EntityPath()
			: m_path()
		{
		}
		
		/// <summary>
		/// Creates an EntityPath from the given path.
		/// </summary>
		/// <param name="path">The child indices, going down the hierarchy.</param>
		EntityPath(Vector<Byte> const& path)
			: m_path(path)
		{
		}

#pragma endregion

#pragma region Get Set
		
		/// <summary>
		/// Gets the index path to the child entity.
		/// </summary>
		/// <returns>The path.</returns>
		Vector<Byte> const& get_path() const
		{
			return m_path;
		}

		/// <summary>
		/// Checks if this EntityPath is empty.
		/// </summary>
		/// <returns>True if empty.</returns>
		Bool is_empty() const
		{
			return m_path.is_empty();
		}

#pragma endregion

#pragma region Methods

	public:
		Bool parse(String const& text) override;
		String to_string() const override;

#pragma endregion
	};
}