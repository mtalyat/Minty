#pragma once

namespace Minty
{
    class Scene;
    class Event;
    struct Timestep;

    /**
     * @brief Handles the execution and management of script components within the world.
     */
    class ScriptSystem
    {
#pragma region Constructor

	public:
		/**
		 * @brief Creates a ScriptSystem using the given Scene.
		 */
		ScriptSystem(Scene& scene);

#pragma endregion

#pragma region Method

public:
    /**
     * List of functions that systems can implement:
     on_frame_update
     on_fixed_update
     on_finalize
     on_render
     on_event
     on_load
     on_unload
     on_enable
     on_disable
     */
    void on_load();
    void on_unload();
    void on_enable();
    void on_disable();
    void on_frame_update(Timestep const &timestep);
    void on_fixed_update(Timestep const &timestep);
    void on_finalize();
    void on_render();
    void on_event(Event &event);

#pragma endregion

#pragma region Variable

	private:
		Scene* mp_scene;

#pragma endregion
    };
}