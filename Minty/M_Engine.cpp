#include "pch.h"

//#define SDL_MAIN_HANDLED

#include "M_Engine.h"

#include "M_Screen.h"
#include "M_Scene.h"
#include "M_SceneManager.h"
#include "M_Game.h"
#include "M_Input.h"

#include "M_Debug.h"
#include "M_Stopwatch.h"
#include "M_Random.h"
#include "M_Color.h"
#include "M_Math.h"
#include "M_Coroutine.h"
#include "M_Point.h"
#include "M_Pair.h"
#include "M_Sprite.h"

#include "FastNoiseLite.h"
#include "entt.hpp"

#include "M_C_Position.h"
#include "M_C_Scale.h"
#include "M_C_Velocity.h"
#include "M_C_Camera.h"
#include "M_T_Destroy.h"
#include "M_C_DestroyTimer.h"

#include "M_PriorityQueue.h"

#include "M_Time.h"

#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace minty
{
	constexpr elapsed_t FIXED_UPDATE_TIME = ONE_MILLISECOND * 20;// 0.02 seconds

	Engine* Engine::sp_active = nullptr;

	Engine::Engine(EngineConfig const* const config)
		: m_quit(false)
		, m_isRunning(false)
		, m_isPaused(false)
		, m_gameWatch()
		, mp_config(config == nullptr ? new EngineConfig() : config)
		, mp_screen(nullptr)
		, mp_input(new Input())
		, mp_coroutineManager(new CoroutineManager())
		, mp_game(nullptr)
	{
		sp_active = this;

		initialize();
	}

	Engine::~Engine()
	{
		delete mp_input;
		delete mp_coroutineManager;
		delete mp_screen;

		// clean up
		Mix_Quit();
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	void Engine::run()
	{
		onStart();

		// start game
		if (mp_game->onStart())
		{
			abort(12, "Failed to start game.");
			return;
		}

		Debug::log("Initialization completed in: " + m_gameWatch.toString());

		Time::setFixedDeltaTime(FIXED_UPDATE_TIME);

		// debug
		Debug::log(std::format("Fixed time: {}", std::to_string(Time::fixedDeltaTime())));

		// FPS
		Stopwatch fpsWatch = Stopwatch::startNew();
		size_t frames = 0;
		size_t fixedFrames = 0;
		elapsed_t frameTime = mp_config->getFPNS();

		// timers
		Stopwatch renderWatch;
		Stopwatch fixedWatch;

		// testing
		Stopwatch updateWatch;
		Stopwatch fixedUpdateWatch;
		Stopwatch loopWatch;
		elapsed_t updateMax = 0;
		elapsed_t fixedUpdateMax = 0;
		elapsed_t loopMax = 0;
		elapsed_t diffMax = 0;

		SDL_Renderer* const renderer = mp_screen->renderer();
		entt::registry* registry = mp_game->registry();
		SceneManager* sceneManager = mp_game->sceneManager();

		// used in loop
		Scene* activeScene = sceneManager->active();
		SDL_Event event;

		// start watches
		fixedWatch.start();

		while (!m_quit)
		{
			loopWatch.start();
			renderWatch.start();

			// force events
			SDL_PumpEvents();

			// if there is an event waiting...
			while (SDL_PollEvent(&event))
			{
				// there was an event, handle it
				switch (event.type)
				{
				case SDL_QUIT: // Window Close button
					m_quit = true;
					break;
				case SDL_KEYDOWN:
					mp_input->onKeyDown(event.key.keysym.sym);

					if (mp_config->quitOnEscape && event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit();
					}
					break;
				case SDL_KEYUP:
					mp_input->onKeyUp(event.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					MouseClickEvent click
					{
						event.button.button,
						event.button.clicks,
						event.button.x,
						event.button.y
					};

					// if a click did not occur, do normal mouse down
					if (!activeScene->inputSystem()->onMouseDown(&click))
					{
						mp_input->onMouseDown(&event.button);
					}
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					MouseClickEvent click
					{
						event.button.button,
						event.button.clicks,
						event.button.x,
						event.button.y
					};

					// if a click did not occur, do normal mouse up
					if (!activeScene->inputSystem()->onMouseUp(&click))
					{
						mp_input->onMouseUp(&event.button);
					}
					break;
				}
				case SDL_MOUSEMOTION:
					mp_input->onMouseMove(&event.motion);

					activeScene->inputSystem()->onMouseMove(event.motion.x, event.motion.y);
					break;
				case SDL_MOUSEWHEEL:
					mp_input->onMouseScroll(&event.wheel);
					break;
				}
			}

			// get the active scene
			activeScene = sceneManager->active();

			// if no scene, abort
			if (!activeScene)
			{
				abort(10, "No active scene.");
				break;
			}

			// only update if not paused, or if the >>| key is being pressed.
			if (!m_isPaused)
			{
				updateWatch.start();

				// run active coroutines
				mp_coroutineManager->run();

				// update scene
				if (activeScene->update())
				{
					Debug::logError(24, "Failed to update active scene.");
				}

				updateWatch.stop();
				updateMax = updateMax > updateWatch.elapsed() ? updateMax : updateWatch.elapsed();

				// fixed update scene
				if (fixedWatch.lap(FIXED_UPDATE_TIME))
				{
					fixedUpdateWatch.start();

					if (activeScene->fixedUpdate())
					{
						Debug::logError(33, "Failed to fixed update active scene.");
					}

					fixedUpdateWatch.stop();
					fixedUpdateMax = fixedUpdateMax > fixedUpdateWatch.elapsed() ? fixedUpdateMax : fixedUpdateWatch.elapsed();

					fixedFrames++;
				}
			}

			// if time to render
			if (renderWatch.lap(frameTime))
			{
				activeScene->renderSystem()->update();

				// another frame completed
				frames++;
			}

			// if a second has passed, display FPS
			if (fpsWatch.lap(ONE_SECOND))
			{
				// one second passed, log FPS

				Debug::log(std::format("{0}fps, {1}tps", std::to_string(frames), std::to_string(fixedFrames)));
				frames = 0;
				fixedFrames = 0;
			}

			loopWatch.stop();

			long loopElapsed = loopWatch.elapsed();

			Time::setDeltaTime(loopElapsed);

			loopMax = loopMax > loopElapsed ? loopMax : loopElapsed;
			diffMax = diffMax > (loopElapsed - updateWatch.elapsed()) ? diffMax : (loopElapsed - updateWatch.elapsed());

			loopWatch.reset();
			updateWatch.reset();
			fixedUpdateWatch.reset();
		}

		if (mp_game->onStop())
		{
			abort(13, "Failed to stop game.");
			return;
		}

		// stop game clock
		m_gameWatch.stop();

		Debug::setWatch(nullptr);

		Debug::log(std::format("Update max: {0}ns", std::to_string(updateMax)));
		Debug::log(std::format("Fixed update max: {0}ns", std::to_string(fixedUpdateMax)));
		Debug::log(std::format("Loop max: {0}ns", std::to_string(loopMax)));
		Debug::log(std::format("Loop w/o update max: {0}ns", std::to_string(loopMax - updateMax)));
		Debug::log(std::format("Diff max: {0}ns", std::to_string(diffMax)));

		onFinish();

		m_isRunning = false;
	}

	void Engine::quit()
	{
		if (m_isRunning)
		{
			m_quit = true;
		}
	}

	void Engine::load(Game* const game)
	{
		// assign game
		mp_game = game;

		// set screen title
		mp_screen->setTitle(game->name());
	}

	SDL_Renderer* const Engine::renderer() const
	{
		return mp_screen->renderer();
	}

	void Engine::initialize()
	{
		//SDL_SetMainReady();

		// initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO))
		{
			Debug::logErrorSDL(1, "Failed to init SDL.");
		}

		// init ttf
		if (TTF_Init())
		{
			Debug::logError(-1, TTF_GetError());
		}

		// init IMG SDL
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			Debug::logErrorSDL(2, "Failed to init IMG.");
		}

		// init mixer
		Mix_Init(MIX_INIT_MP3);
		if (SDL_Init(SDL_INIT_AUDIO))
		{
			Debug::logErrorSDL(39, "Failed to init AUDIO.");
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
		{
			Debug::logErrorSDL(40, "Failed to init MIXER.");
		}

		// init screen/window, since it must be done after SDL_Init
		mp_screen = new Screen("Minty Engine", mp_config);

		// initialize random values
		random_seed_time();

		// initialize debug
		Debug::setWatch(&m_gameWatch);
	}

	void Engine::abort(unsigned int const code, std::string const& errorMessage)
	{
		m_quit = false;
		m_isRunning = false;

		if (!errorMessage.empty())
		{
			Debug::logError(code, "Engine aborted. " + errorMessage);
		}

		onFinish();
	}

	void Engine::onStart()
	{
		Debug::log("Starting engine.");

		// initialize
		m_quit = false;
		m_isRunning = true;
		m_isPaused = false;

		// start game clock
		m_gameWatch.start();
	}

	void Engine::onFinish()
	{
		m_gameWatch.stop();

		Debug::log("Program ran for: " + m_gameWatch.toString());
	}
}