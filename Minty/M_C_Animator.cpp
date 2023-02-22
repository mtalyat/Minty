#include "pch.h"
#include "M_C_Animator.h"

namespace minty
{
    bool Animator::emplace(std::string const& animationName, Animation* const animation)
    {
        return mp_animations->try_emplace(animationName, animation).second;
    }

    bool Animator::erase(std::string const& animationName)
    {
        if (mp_animations->contains(animationName))
        {
            mp_animations->erase(animationName);

            return true;
        }

        return false;
    }

    bool Animator::select(std::string const& animationName)
    {
        // if does not contain an animation with this name, do nothing
        if (!mp_animations->contains(animationName))
        {
            return false;
        }

        Animation* selectedAnimation = mp_animations->at(animationName);

        // if already running this animation, do nothing
        if (mp_activeAnimation && mp_activeAnimation == selectedAnimation)
        {
            return true;
        }

        // contains animation
        mp_activeAnimation = mp_animations->at(animationName);
        m_frameIndex = 0;
    }

    Sprite* Animator::update()
    {
        // if no animation or not playing, do nothing
        if (!mp_activeAnimation || !isPlaying())
        {
            return nullptr;
        }

        // check for next frame
        elapsed_t laps = m_stopwatch.lap(mp_activeAnimation->frameTime);

        if (laps)
        {
            m_frameIndex = static_cast<int>(m_frameIndex + laps) % mp_activeAnimation->frameCount;
        }        

        return mp_activeAnimation->at(m_frameIndex);
    }

    void Animator::play()
    {
        m_stopwatch.start();
    }

    void Animator::play(std::string const& animationName)
    {
        select(animationName);
        play();
    }

    void Animator::pause()
    {
        m_stopwatch.stop();
    }

    void Animator::stop()
    {
        m_stopwatch.stop();
        m_stopwatch.reset();
    }
}
