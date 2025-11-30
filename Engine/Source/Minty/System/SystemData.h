#ifndef MINTY_SYSTEM_SYSTEMDATA_H
#define MINTY_SYSTEM_SYSTEMDATA_H

/**
 * @file SystemData.h
 * @brief Header file for the SystemData struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    class System;
    struct SystemInfo;

    /**
     * @brief Data about a System type.
     */
	struct SystemData
	{
        /**
         * @brief The name of the System.
         */
		String name;

        /**
         * @brief The unique type ID of the System.
         */
		TypeID typeId;

		/**
         * @brief The function to create the System.
         */
		Function<System* (SystemInfo const&)> create;

		/**
         * @brief The default priority of the System, if none is specified.
         */
		Int defaultPriority = 0;
	};
}

#endif // MINTY_SYSTEM_SYSTEMDATA_H