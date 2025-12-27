#ifndef MINTY_COMPONENT_AUDIOLISTENERCOMPONENT_H
#define MINTY_COMPONENT_AUDIOLISTENERCOMPONENT_H

/**
 * @file AudioListenerComponent.h
 * @brief Header file defining the AudioListenerComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief Component representing an audio listener.
	 * All sounds will be played relative to the Entity with this listener.
	 */
	struct AudioListenerComponent
		: public Component
	{};
}

#endif // MINTY_COMPONENT_AUDIOLISTENERCOMPONENT_H