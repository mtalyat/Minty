#pragma once

namespace Minty
{
    class Scene;

    struct SystemManagerInfo
    {
        /**
         * @brief The Scene this SystemManager belongs to.
         */
        Scene* scene = nullptr;
    };
}