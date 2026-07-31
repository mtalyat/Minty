#pragma once

namespace Minty
{
    class Scene;

    struct EntityManagerInfo
    {
        /**
         * @brief The Scene this EntityManager belongs to.
         */
        Scene* scene = nullptr;
    };
}