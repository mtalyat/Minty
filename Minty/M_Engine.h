#pragma once

#include "M_Object.h"
#include "M_Stopwatch.h"
#include "M_EngineConfig.h"
#include <SDL.h>
#include <SDL_image.h>

namespace minty
{
    class Screen;
    class SceneManager;
    class ElementRegistry;
    class Game;
    class Input;
    class CoroutineManager;

    /// <summary>
    /// The engine controls running the simulation in its entirety.
    /// </summary>
    class MINTY_API Engine :
        public Object
    {
    private:
        bool m_quit;
        bool m_isRunning;
        bool m_isPaused;

        Stopwatch m_gameWatch;

        EngineConfig const* const mp_config;

        Screen* mp_screen;

        Input* const mp_input;

        CoroutineManager* const mp_coroutineManager;

        Game* mp_game;

        static Engine* sp_active;
    public:
        /// <summary>
        /// Creates a new Engine.
        /// </summary>
        Engine(EngineConfig const* const config = nullptr);
        ~Engine();

        /// <summary>
        /// Runs the Engine until quit, or completion.
        /// </summary>
        void run();

        /// <summary>
        /// Prematurely quits the Engine.
        /// </summary>
        void quit();

        /// <summary>
        /// Pauses the Engine.
        /// </summary>
        inline void pause() { m_isPaused = true; }

        /// <summary>
        /// Unpauses the Engine.
        /// </summary>
        inline void unpause() { m_isPaused = false; }

        /// <summary>
        /// Toggles the pause state of the Engine.
        /// </summary>
        void togglePause() { if (m_isPaused) { unpause(); } else { pause(); } }

        /// <summary>
        /// Loads a Game into the Engine.
        /// </summary>
        /// <param name="game"></param>
        void load(Game* const game);

        /// <summary>
        /// Gets the Screen data associated with this session.
        /// </summary>
        /// <returns></returns>
        inline Screen* const screen() const { return mp_screen; }

        /// <summary>
        /// Gets the Input for the Engine.
        /// </summary>
        /// <returns></returns>
        inline Input* const input() const { return mp_input; }

        /// <summary>
        /// Gets the CoroutineManager for the Engine.
        /// </summary>
        /// <returns></returns>
        inline CoroutineManager* const coroutineManager() const { return mp_coroutineManager; }

        /// <summary>
        /// Gets the currently active Engine.
        /// </summary>
        /// <returns></returns>
        inline static Engine* active() { return sp_active; }

    private:
        /// <summary>
        /// Sets up the Engine.
        /// </summary>
        void initialize();

        /// <summary>
        /// Aborts the currently running Game.
        /// </summary>
        void abort(unsigned int const code, std::string const& errorMessage = "");

        /// <summary>
        /// Called when the Game starts.
        /// </summary>
        void onStart();

        /// <summary>
        /// Called when the Game finishes.
        /// </summary>
        void onFinish();
    };
}
