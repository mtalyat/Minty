#pragma once

#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_SystemManager.h"
#include "entt.hpp"

namespace minty
{
    class Engine;
    class Game;
    class Input;
    //class UI_Canvas;

    /// <summary>
    /// A scene is a collection of entities, and other resources that will run during gameplay. Only one Scene can be loaded and running at any given time.
    /// </summary>
    class MINTY_API Scene :
        public Object
    {
    private:
        std::string m_name;

    protected:
        entt::registry* mp_registry;

        SystemManager m_systemManager;

        entt::entity m_mainCamera;
        //UI_Canvas* mp_mainCanvas;

        Game* const mp_game;
        Engine* const mp_engine;
    public:
        Scene(std::string const& name, Game* const game);
        virtual ~Scene();

        /// <summary>
        /// Called when the Engine starts, and will only be called once during the length of the program.
        /// </summary>
        /// <returns></returns>
        virtual int onCreate() { return 0; }

        /// <summary>
        /// Called when the Scene is loaded into the Game.
        /// </summary>
        /// <returns></returns>
        virtual int onLoad() = 0;

        /// <summary>
        /// Preforms update methods for Systems, followed by onUpdate().
        /// </summary>
        /// <returns></returns>
        int update();

        /// <summary>
        /// Called every update loop when this Scene is loaded.
        /// </summary>
        /// <returns></returns>
        virtual int onUpdate() = 0; // TODO update()

        /// <summary>
        /// Called when the Scene is unloaded from the Game.
        /// </summary>
        /// <returns></returns>
        virtual int onUnload() = 0;

        /// <summary>
        /// Called when the Engine stops, and will only be called once during the length of the program.
        /// </summary>
        /// <returns></returns>
        virtual int onDestroy() { return 0; }

        /// <summary>
        /// Gets the name of this Scene.
        /// </summary>
        /// <returns></returns>
        inline std::string const& name() const { return m_name; }

        /// <summary>
        /// Gets the main Camera entity in this Scene.
        /// </summary>
        /// <returns></returns>
        inline entt::entity& mainCamera() { return m_mainCamera; }

        /// <summary>
        /// Gets the SystemManager in this Scene.
        /// </summary>
        /// <returns></returns>
        inline SystemManager* const systemManager() { return &m_systemManager; }

        //inline UI_Canvas* mainCanvas() { return mp_mainCanvas; }

        /// <summary>
        /// Gets the Game that this Scene belongs to.
        /// </summary>
        /// <returns></returns>
        inline Game* const game() const { return mp_game; }

    protected:

        /*
                The following methods are helper methods for creating generic entities that may commonly be created within the scene. 
                This helps with development of projects, and should help reduce the code that is written. For example, almost every
                scene will need an entity with a Camera component.
        */

        /// <summary>
        /// Creates and returns an entity with the following components: Transform, Size and Camera.
        /// </summary>
        /// <returns></returns>
        entt::entity createEntity_camera();

        /// <summary>
        /// Creates and returns an entity with the following components: Transform, Size and SpriteRenderer.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="z"></param>
        /// <returns></returns>
        entt::entity createEntity_sprite(std::string const& path, float const x, float const y, int const z = 0);

        /// <summary>
        /// Creates and returns an entity with the following components: Transform, Size, SpriteRenderer and Collider.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="bounds"></param>
        /// <param name="z"></param>
        /// <returns></returns>
        entt::entity createEntity_spriteWithCollider(std::string const& path, float const x, float const y, int const z = 0, bool const isTrigger = false, bool const isStatic = false, Rect const* const rect = nullptr);
    };
}
