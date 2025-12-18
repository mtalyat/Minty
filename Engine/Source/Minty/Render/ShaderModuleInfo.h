#ifndef MINTY_RENDER_SHADERMODULEINFO_H
#define MINTY_RENDER_SHADERMODULEINFO_H

/**
 * @file ShaderModuleInfo.h
 * @brief Header file defining the ShaderModuleInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    /**
     * @brief The arguments for a ShaderModule.
     */
    struct ShaderModuleInfo
    {
        /**
         * @brief The ID.
         */
        UUID id = {};

        /**
         * @brief The data of the ShaderModule.
         */
        AnyConst data = nullptr;

        /**
         * @brief The size of the ShaderModule in bytes.
         */
        Size size = 0;
    };
}

#endif // MINTY_RENDER_SHADERMODULEINFO_H