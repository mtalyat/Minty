#ifndef MINTY_COMPONENT_RELATIONSHIPCOMPONENT_H
#define MINTY_COMPONENT_RELATIONSHIPCOMPONENT_H

/**
 * @file RelationshipComponent.h
 * @brief Header file defining the RelationshipComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	/**
	 * @brief Holds the relationship data of an Entity in a hierarchy.
	 */
	struct RelationshipComponent
		: public Component
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
		Entity first = INVALID_ENTITY;

		/**
		 * @brief The last child this Entity has.
		 */
		Entity last = INVALID_ENTITY;

		/**
		 * @brief The previous sibling this Entity has.
		 */
		Entity prev = INVALID_ENTITY;

		/**
		 * @brief The next sibling this Entity has.
		 */
		Entity next = INVALID_ENTITY;

		/**
		 * @brief The parent this Entity is a child to.
		 */
		Entity parent = INVALID_ENTITY;
	};

	template<>
	struct Serializer<RelationshipComponent>
	{
		static void serialize(Writer& writer, RelationshipComponent const& value);
		static void deserialize(Reader& reader, RelationshipComponent& value);
	};
}

#endif // MINTY_COMPONENT_RELATIONSHIPCOMPONENT_H