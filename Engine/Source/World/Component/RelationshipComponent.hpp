#pragma once

/**
 * @file RelationshipComponent.h
 * @brief Header file defining the RelationshipComponent structure.
 * @author Mitchell Talyat
 */

#include "World/Entity/Entity.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	/**
	 * @brief Holds the relationship data of an Entity in a hierarchy.
	 */
	struct RelationshipComponent	
	{
		/**
		 * @brief The index of this Entity among its siblings.
		 */
		UInt index = 0;

		/**
		 * @brief The depth of this Entity in the tree.
		 */
		UInt depth = 0;

		/**
		 * @brief The number of children this Entity has.
		 */
		UInt children = 0;

		/**
		 * @brief The first child this Entity has.
		 */
		EntityHandle first = INVALID_ENTITY;

		/**
		 * @brief The last child this Entity has.
		 */
		EntityHandle last = INVALID_ENTITY;

		/**
		 * @brief The previous sibling this Entity has.
		 */
		EntityHandle prev = INVALID_ENTITY;

		/**
		 * @brief The next sibling this Entity has.
		 */
		EntityHandle next = INVALID_ENTITY;

		/**
		 * @brief The parent this Entity is a child to.
		 */
		EntityHandle parent = INVALID_ENTITY;
	};

	template<>
	struct Serializer<RelationshipComponent>
	{
		static Bool serialize(Writer& writer, RelationshipComponent const& value);
		static Bool deserialize(Reader& reader, RelationshipComponent& value);
	};
}
