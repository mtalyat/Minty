#pragma once
#include "Minty/Data/String.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	class EntityManager;
	struct Component;

	struct ComponentInfo
	{
		String name;

		Function<Component& (EntityManager&, Entity const)> create;

		Function<Component* (EntityManager&, Entity const)> get;

		Function<Component const*(EntityManager const&, Entity const)> get_const;

		Function<void(EntityManager&, Entity const)> destroy;
	};

	/// <summary>
	/// The base class for all components. Holds data for an Entity.
	/// </summary>
	struct Component
		: public SerializableObject
	{
		virtual ~Component() = default;

		/// <summary>
		/// Write this Component's data to the writer.
		/// </summary>
		/// <param name="writer">The Writer to write to.</param>
		virtual void serialize(Writer& writer) const override {}

		/// <summary>
		/// Read this Component's data from the reader.
		/// </summary>
		/// <param name="reader">The Reader to read from.</param>
		/// <returns>True on success.</returns>
		virtual Bool deserialize(Reader& reader) override { return true; }
	};
}