#ifndef MINTY_ENTITY_ENTITY_H
#define MINTY_ENTITY_ENTITY_H

/**
 * @file Entity.h
 * @brief Header file defining the Entity type.
 * @author Mitchell Talyat
 */

#include "Minty/Library/EnTT.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief An entity is a unique identifier for an object in the world.
	 */
	using Entity = entt::entity;

	/**
	 * @brief An invalid entity.
	 */
	constexpr Entity INVALID_ENTITY = entt::null;

    template<>
    struct Parser<Entity>
    {
        static Bool parse(StringView const str, Entity &value);
        static String to_string(Entity const &value);
    };
}

#endif // MINTY_ENTITY_ENTITY_H