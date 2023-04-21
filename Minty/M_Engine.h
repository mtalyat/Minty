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
        // is the engine quitting
        bool m_quit;
        // is the engine running
        bool m_isRunning;
        // is the engine paused
        bool m_isPaused;

        // the game timer
        Stopwatch m_gameWatch;

        // the config settings for the engine
        EngineConfig const* const mp_config;

        // the screen the engine is rendering to
        Screen* mp_screen;

        // the input system the engine will use to handle input
        Input* const mp_input;

        // the coroutine manager the engine will use to handle coroutines
        CoroutineManager* const mp_coroutineManager;

        // the game the engine is running
        Game* mp_game;

        // a reference to the running Engine
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
        /// Gets the Screen data for this Engine.
        /// </summary>
        /// <returns></returns>
        inline Screen* const screen() const { return mp_screen; }

        /// <summary>
        /// Gets the SDL Renderer associated with this screen for this Engine.
        /// </summary>
        /// <returns></returns>
        SDL_Renderer* const renderer() const;

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
