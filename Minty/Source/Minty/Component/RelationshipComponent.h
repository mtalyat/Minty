#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	/// <summary>
	/// Holds relationship data for an Entity.
	/// </summary>
	struct RelationshipComponent
		: public Component
	{
		/// <summary>
		/// The index of this Entity among its siblings.
		/// </summary>
		UInt index = 0;

		/// <summary>
		/// The depth of this Entity in the tree.
		/// </summary>
		UInt depth = 0;

		/// <summary>
		/// The number of children this Entity has.
		/// </summary>
		UInt children = 0;

		/// <summary>
		/// The first child this Entity has.
		/// </summary>
		Entity first = INVALID_ENTITY;

		/// <summary>
		/// The last child this Entity has.
		/// </summary>
		Entity last = INVALID_ENTITY;

		/// <summary>
		/// The previous sibling this Entity has.
		/// </summary>
		Entity prev = INVALID_ENTITY;

		/// <summary>
		/// The next sibling this Entity has.
		/// </summary>
		Entity next = INVALID_ENTITY;

		/// <summary>
		/// The parent this Entity is a child to.
		/// </summary>
		Entity parent = INVALID_ENTITY;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}