#include "pch.h"

#define SDL_MAIN_HANDLED

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

#include "FastNoiseLite.h"
#include "entt.hpp"

#include "M_C_Transform.h"
#include "M_C_Velocity.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_Camera.h"
#include "M_T_Destroy.h"

//#include "UI_Canvas.h"
//#include "UI_IClickable.h"
//#include "UI_IVisual.h"

#include "M_PriorityQueue.h"

#include "M_Time.h"

constexpr long FRAME_TIME = 16; // roughly 1/60, rounded down

namespace minty
{
	Engine* Engine::sp_active = nullptr;

	Engine::Engine()
		: m_quit(false)
		, m_isRunning(false)
		, m_isPaused(false)
		, m_gameWatch()
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

		// clean up SDL
		SDL_Quit();
	}

	void Engine::run()
	{
		// initialize
		m_quit = false;
		m_isRunning = true;
		m_isPaused = false;

		onStart();

		// create game
		if (mp_game->onCreate())
		{
			abort(11, "Failed to create game.");
			return;
		}

		// start game
		if (mp_game->onStart())
		{
			abort(12, "Failed to start game.");
			return;
		}

		Debug::log("Initialization completed in: " + m_gameWatch.toString());

		// FPS
		Stopwatch fpsWatch = Stopwatch::startNew();
		size_t frames = 0;

		// testing
		Stopwatch updateWatch;
		long updateMax = 0;
		Stopwatch loopWatch;
		long loopMax = 0;
		long diffMax = 0;

		Stopwatch renderWatch;

		// used in loop
		Scene* activeScene;
		SDL_Event event;

		SDL_Renderer* const renderer = mp_screen->renderer();
		entt::registry* registry = mp_game->registry();
		SceneManager* sceneManager = mp_game->sceneManager();

		while (!m_quit)
		{
			loopWatch.start();
			renderWatch.start();

			// get the active scene
			activeScene = sceneManager->active();

			// if no scene
			if (!activeScene)
			{
				abort(10, "No active scene.");
				break;
			}

			// get the canvas
			//UI_Canvas* activeCanvas = activeScene->mainCanvas();

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
					break;
				case SDL_KEYUP:
					mp_input->onKeyUp(event.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					mp_input->onMouseDown(&event.button);
					//// canvas
					//for (UI_IClickable* c : activeCanvas->clickables())
					//{
					//	c->onDown(&event.button);
					//}
					break;
				case SDL_MOUSEBUTTONUP:
					mp_input->onMouseUp(&event.button);
					//// canvas
					//for (UI_IClickable* c : activeCanvas->clickables())
					//{
					//	c->onUp(&event.button);
					//}
					break;
				case SDL_MOUSEMOTION:
					mp_input->onMouseMove(&event.motion);
					break;
				case SDL_MOUSEWHEEL:
					mp_input->onMouseScroll(&event.wheel);
					break;
				}
			}

			// only update if not paused, or if the >>| key is being pressed.
			if (!m_isPaused)
			{
				updateWatch.start();

				// run active coroutines
				mp_coroutineManager->run();

				// update scene
				activeScene->onUpdate();

				// destroy entities that are needing to be destroyed
				auto destroyView = registry->view<Destroy>();
				registry->destroy(destroyView.begin(), destroyView.end());

				updateWatch.stop();

				updateMax = updateMax > updateWatch.elapsed() ? updateMax : updateWatch.elapsed();
			}

			if (renderWatch.elapsed() >= FRAME_TIME)
			{
				// reset watch
				renderWatch.reset();

				// clear the screen so there is no smearing
				if (mp_screen->backgroundTexture())
				{
					// background
					SDL_RenderCopy(renderer, mp_screen->backgroundTexture(), NULL, NULL);
				}
				else
				{
					// set background color
					Color bgColor = mp_screen->backgroundColor();
					SDL_SetRenderDrawColor(renderer, bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());
					
					// color background
					SDL_RenderClear(renderer);
				}

				PriorityQueue<Pair<Point, Sprite const*>> queue;

				// render sprites based on main camera position
				if (registry->valid(activeScene->mainCamera()))
				{
					Transform const& cameraTransform = registry->get<Transform>(activeScene->mainCamera());
					for (auto&& [entity, transform, sprite] : registry->view<Transform const, SpriteRenderer const>().each())
					{
						// if the sprite is visible, render a copy of it
						if (!sprite.invisible)
						{
							queue.push(transform.zIndex, Pair<Point, Sprite const*>(Point(transform.worldPosX - cameraTransform.worldPosX, transform.worldPosY - cameraTransform.worldPosY), sprite.sprite));
						}
					}
					
					//// add UI elements
					//for (auto visual : activeScene->mainCanvas()->visuals())
					//{
					//	Sprite* visualSprite = visual->sprite();

					//	if (visualSprite->isVisible())
					//	{
					//		queue.push(visualSprite->order(), Pair<Point, Sprite const*>(visual->position(), visualSprite));
					//	}
					//}

					Pair<Point, Sprite const*> renderPair;

					// render in order
					while (queue.pop(renderPair))
					{
						SDL_Rect dstrect = { renderPair.first.x, renderPair.first.y, renderPair.second->width(), renderPair.second->height() };
						SDL_RenderCopy(renderer, renderPair.second->texture(), NULL, &dstrect);
					}
				}

				// draw to the screen
				SDL_RenderPresent(renderer);

				// another frame completed
				frames++;
			}

			// if a second has passed, display FPS
			if (fpsWatch.elapsed() > 1000)
			{
				// one second passed
				Debug::log(std::to_string(frames) + "fps");

				frames = 0;
				fpsWatch.restart();
			}

			loopWatch.stop();

			long loopElapsed = loopWatch.elapsed();

			Time::setDeltaTime(loopElapsed);

			loopMax = loopMax > loopElapsed ? loopMax : loopElapsed;
			diffMax = diffMax > (loopElapsed - updateWatch.elapsed()) ? diffMax : (loopElapsed - updateWatch.elapsed());

			loopWatch.reset();
			updateWatch.reset();
		}

		if (mp_game->onStop())
		{
			abort(13, "Failed to stop game.");
			return;
		}

		if (mp_game->onDestroy())
		{
			abort(14, "Failed to destroy game.");
			return;
		}

		Debug::log(std::format("Update max: {0}ms", std::to_string(updateMax)));
		Debug::log(std::format("Loop max: {0}ms", std::to_string(loopMax)));
		Debug::log(std::format("Loop w/o update max: {0}ms", std::to_string(loopMax - updateMax)));
		Debug::log(std::format("Diff max: {0}ms", std::to_string(diffMax)));

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

	void Engine::initialize()
	{
		SDL_SetMainReady();

		// initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO))
		{
			Debug::logErrorSDL(1, "Failed to init SDL.");
		}

		// init IMG SDL
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			Debug::logErrorSDL(2, "Failed to init IMG.");
		}

		// init screen/window, since it must be done after SDL_Init
		mp_screen = new Screen("Sand Game", 480, 270);

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
		m_gameWatch.start();
	}

	void Engine::onFinish()
	{
		m_gameWatch.stop();

		Debug::log("Program ran for: " + m_gameWatch.toString());
	}

	void Engine::uiClick(SDL_MouseButtonEvent* buttonEvent)
	{

	}
}