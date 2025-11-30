#ifndef MINTY_ENTITY_ENTITYPATH_H
#define MINTY_ENTITY_ENTITYPATH_H

/**
 * @file EntityPath.h
 * @brief Header file defining the EntityPath class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Serialization/Parseable.h"

namespace Minty
{
	/**
	 * @brief An EntityPath is a relational path from an Entity to another Entity.
	 */
	class EntityPath
		: public Parseable
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty EntityPath.
		 */
		EntityPath()
			: m_path()
		{
		}
		
		/**
		 * @brief Creates an EntityPath from the given path.
		 * @param path The child indices, going down the hierarchy.
		 */
		EntityPath(Vector<Byte> const& path)
			: m_path(path)
		{
		}

#pragma endregion

#pragma region Accessors
		
		/**
		 * @brief Gets the index path to the child entity.
		 * @return The path.
		 */
		Vector<Byte> const& get_path() const
		{
			return m_path;
		}

		/**
		 * @brief Checks if this EntityPath is empty.
		 * @return True if empty.
		 */
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

#pragma region Variables

	private:
		// the path to the (child) entity, relative to the (parent) entity
		Vector<Byte> m_path;

#pragma endregion
	};
}

#endif // MINTY_ENTITY_ENTITYPATH_H