#ifndef MINTY_COMPONENT_SIMULATECOMPONENT_H
#define MINTY_COMPONENT_SIMULATECOMPONENT_H

/**
 * @file SimulateComponent.h
 * @brief Header file defining the SimulateComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief Used to tag objects that should be controlled by the physics simulation.
	 */
	struct SimulateComponent
		: public Component
	{
	};
}

#endif // MINTY_COMPONENT_SIMULATECOMPONENT_H