#pragma once

/**
 * @file SoLoud_AudioManager.h
 * @brief Header file for the SoLoud implementation of the AudioManager.
 * @author Mitchell Talyat
 */

#include "SoLoud_Clip.h"
#include "Platform/Type/Primitive.h"
#include "Library/SoLoud/SoLoud.h"
#include "Audio/Type/Handle.h"
#include "Core/Data/IndexPool.h"
#include "Core/Data/HandlePool.h"
#include "Core/Memory/DefaultAllocator.h"
#include "Resource/Type/Handle.h"

namespace Minty
{
    struct AudioManagerInfo;
    struct AudioSourceInfo;
    struct AudioListenerInfo;
    struct ClipResource;
    struct ClipInfo;

    class SoLoud_AudioManager
    {
#pragma region Constructor

    public:
        SoLoud_AudioManager(AudioManagerInfo const &info);

        ~SoLoud_AudioManager();

#pragma endregion

#pragma region Accessors

    public:
        Bool is_valid(AudioHandle const handle) const;

        Bool is_valid(AudioSourceHandle const handle) const;

#pragma endregion

#pragma region Methods

    public:
        ClipHandle create(ClipResourceHandle const resourceHandle);

        ClipHandle create(ClipInfo const &clipInfo);

        void destroy(ClipHandle const handle);

        AudioSourceHandle create_source(AudioSourceInfo const &info);

        void destroy_source(AudioSourceHandle const handle);

        void update_listener(AudioListenerInfo const &info);

        void update_source(AudioSourceHandle const handle, AudioSourceInfo const &info);

        AudioHandle play(ClipHandle const clip, Float const volume, Float const pan, Bool const paused, UInt const bus);

        AudioHandle play_object(ClipHandle const clip, AudioSourceInfo const &source, Float const volume, Bool const paused, UInt const bus);

        AudioHandle play_background(ClipHandle const clip, Float const volume, Bool const paused, UInt const bus);

        void stop(AudioHandle const handle);

        void stop_all();

        void set_pause(AudioHandle const handle, Bool const paused);

        void set_pause_all(Bool const paused);

        Bool get_pause(AudioHandle const handle) const;

#pragma endregion

#pragma region Variables

    private:
        IndexPool<Byte, AudioSourceHandle> m_sourcePool;
        HandlePool<SoLoud_ClipData, Clip> m_clipDataPool;
        SoLoud::Soloud *mp_engine;
        Bool m_dirty;
        DefaultAllocator m_allocator;

#pragma endregion
    };
}