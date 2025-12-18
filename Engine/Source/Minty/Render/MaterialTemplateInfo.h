#ifndef MINTY_RENDER_MATERIALTEMPLATEINFO_H
#define MINTY_RENDER_MATERIALTEMPLATEINFO_H

/**
 * @file MaterialTemplateInfo.h
 * @brief Header file defining the MaterialTemplateInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Cargo.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/Shader.h"

namespace Minty
{
    /**
     * @brief The arguments for a MaterialTemplate.
     */
    struct MaterialTemplateInfo
    {
        /**
         * @brief The ID.
         */
        UUID id = UUID();

        /**
         * @brief The Shader for this MaterialTemplate.
         */
        Shared<Shader> shader = nullptr;

        /**
         * @brief The default values for this MaterialTemplate.
         */
        Cargo values;
    };
}

#endif // MINTY_RENDER_MATERIALTEMPLATEINFO_H