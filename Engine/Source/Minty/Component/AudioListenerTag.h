#ifndef MINTY_COMPONENT_AUDIOLISTENERCOMPONENT_H
#define MINTY_COMPONENT_AUDIOLISTENERCOMPONENT_H

/**
 * @file AudioListenerTag.h
 * @brief Header file defining the AudioListenerTag structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief Component representing an audio listener.
	 * All sounds will be played relative to the Entity with this listener.
	 */
	struct AudioListenerTag
		: public Component
	{};

    template<>
    struct Serializer<AudioListenerTag>
    {
        static void serialize(Writer& writer, AudioListenerTag const& value) {}
        static void deserialize(Reader& reader, AudioListenerTag& value) {}
    };
}

#endif // MINTY_COMPONENT_AUDIOLISTENERCOMPONENT_H