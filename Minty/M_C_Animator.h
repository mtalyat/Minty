#pragma once

#include "M_Main.h"
#include "M_Animation.h"
#include "M_Stopwatch.h"
#include <map>

namespace minty
{
	/// <summary>
	/// Holds data for animation processes that occur on an Entity.
	/// </summary>
	struct MINTY_API Animator
	{
	private:
		std::map<std::string, Animation*>* mp_animations;
		Animation* mp_activeAnimation;
		Stopwatch m_stopwatch;
		int m_frameIndex;

	public:
		Animator()
			: mp_animations(new std::map<std::string, Animation*>())
			, mp_activeAnimation(nullptr)
			, m_stopwatch()
			, m_frameIndex()
		{}

		~Animator()
		{
			// delete animations
			for (auto pair : *mp_animations)
			{
				delete pair.second;
			}

			// delete list
			delete mp_animations;
		}

		/// <summary>
		/// Loads an Animation into this Animator.
		/// </summary>
		/// <param name="animationName"></param>
		/// <param name="animation"></param>
		/// <returns></returns>
		bool emplace(std::string const& animationName, Animation* const animation);

		/// <summary>
		/// Removes the Animation with the given name from the Animator.
		/// </summary>
		/// <param name="animationName"></param>
		/// <returns></returns>
		bool erase(std::string const& animationName);

		/// <summary>
		/// Selects the Animation with the given name within this Animator to be played.
		/// </summary>
		/// <param name="animationName"></param>
		/// <returns></returns>
		bool select(std::string const& animationName);

		/// <summary>
		/// Updates this Animator and returns the Sprite that is currently being rendered.
		/// </summary>
		Sprite* update();

		/// <summary>
		/// Plays the selected animation.
		/// </summary>
		void play();

		/// <summary>
		/// Selects and plays the Animation with the given name.
		/// </summary>
		/// <param name="animationName"></param>
		void play(std::string const& animationName);

		/// <summary>
		/// Pauses the selected animation.
		/// </summary>
		void pause();

		/// <summary>
		/// Pauses and restarts the selected animation.
		/// </summary>
		void stop();

		/// <summary>
		/// Checks if this Animator is playing an animation.
		/// </summary>
		/// <returns></returns>
		constexpr bool isPlaying() const { return m_stopwatch.isRunning(); }

		/// <summary>
		/// Gets the active animation that is being played.
		/// </summary>
		/// <returns></returns>
		inline Animation* getActive() const { return mp_activeAnimation; }
	private:
	};
}