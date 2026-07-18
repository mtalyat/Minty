#include "SoLoud_AudioManager.hpp"
#include "SoLoud_Convert.hpp"
#include "Audio/AudioListener/AudioListenerInfo.hpp"
#include "Audio/AudioSource/AudioSourceInfo.hpp"
#include "Core/Debug/Debug.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Core/Memory/FrameAllocator.hpp"
#include "Resource/Clip/ClipInfo.hpp"

using namespace Minty;

Minty::SoLoud_AudioManager::SoLoud_AudioManager(AudioManagerInfo const &info)
    : m_sourcePool(), m_clipDataPool(), mp_engine(nullptr), m_dirty(true), m_allocator()
{
    mp_engine = m_allocator.construct<SoLoud::Soloud>();
    mp_engine->init(SoLoud::Soloud::CLIP_ROUNDOFF | SoLoud::Soloud::LEFT_HANDED_3D);
}

Minty::SoLoud_AudioManager::~SoLoud_AudioManager()
{
    // Unload all clips
    for (ClipHandle const handle : m_clipDataPool.get_handles())
    {
        destroy(handle);
    }

    // Close engine
    mp_engine->deinit();
    m_allocator.destruct(mp_engine);
}

Bool Minty::SoLoud_AudioManager::is_valid(AudioHandle const index) const
{
    return mp_engine->isValidVoiceHandle(static_cast<SoLoud::handle>(index));
}

Bool Minty::SoLoud_AudioManager::is_valid(AudioSourceHandle const handle) const
{
    return m_sourcePool.contains(handle);
}

ClipHandle Minty::SoLoud_AudioManager::create(ClipResourceHandle const resourceHandle)
{
    ResourceManager &resourceManager = ResourceManager::get_instance();
    ClipResource const &clipResource = resourceManager.at<ClipResource>(resourceHandle);
    
    // add data to an info and create a clip from it
    ClipInfo clipInfo{};
    clipInfo.data = clipResource.data.view();
    clipInfo.volume = clipResource.volume;
    clipInfo.loopPoint = clipResource.loopPoint;
    clipInfo.looping = clipResource.looping;
    clipInfo.exclusive = clipResource.exclusive;

    return create(clipInfo);
}

ClipHandle Minty::SoLoud_AudioManager::create(ClipInfo const &clipInfo)
{
    // Create clip data
    ClipHandle const handle = m_clipDataPool.add(SoLoud_ClipData{});
    SoLoud_ClipData &clipData = m_clipDataPool.at(handle);
    
    // Create SoLoud data
    MINTY_ASSERT(!clipInfo.data.is_empty(), ErrorCodeEnum::Audio_FailedToLoadClip);
    MINTY_ASSERT(clipInfo.data.get_size() <= static_cast<Size>(UINT_MAX), ErrorCodeEnum::Audio_FailedToLoadClip);
    SoLoud::result const result = clipData.wav.loadMem(
        static_cast<unsigned char const*>(clipInfo.data.get_data()),
        static_cast<unsigned int>(clipInfo.data.get_size()),
        false,
        false
    );
    MINTY_ASSERT_A(result == SoLoud::SO_NO_ERROR, ErrorCodeEnum::Audio_FailedToLoadClip, static_cast<Size>(result));

    // Set properties
    clipData.wav.setVolume(clipInfo.volume);
    clipData.wav.setLoopPoint(clipInfo.loopPoint);
    clipData.wav.setLooping(clipInfo.looping);
    clipData.wav.setSingleInstance(clipInfo.exclusive);

    return handle;
}

void Minty::SoLoud_AudioManager::destroy(ClipHandle const handle)
{
    MINTY_ASSERT(m_clipDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
    m_clipDataPool.remove(handle);
}

AudioSourceHandle Minty::SoLoud_AudioManager::create_source(AudioSourceInfo const &info)
{
    AudioSourceHandle const handle = m_sourcePool.add(0);
    update_source(handle, info);
    return handle; 
}

void Minty::SoLoud_AudioManager::destroy_source(AudioSourceHandle const handle)
{
    MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);
    m_sourcePool.remove(handle);
}

void Minty::SoLoud_AudioManager::update_listener(AudioListenerInfo const &info)
{
    mp_engine->set3dListenerParameters(
        info.position.x, info.position.y, info.position.z,
        info.velocity.x, info.velocity.y, info.velocity.z,
        info.forward.x, info.forward.y, info.forward.z,
        info.up.x, info.up.y, info.up.z
    );
    m_dirty = true;
}

void Minty::SoLoud_AudioManager::update_source(AudioSourceHandle const handle, AudioSourceInfo const &info)
{
    MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);
    SoLoud::handle const soLoudHandle = static_cast<SoLoud::handle>(handle);
    mp_engine->set3dSourceParameters(
        soLoudHandle,
        info.position.x, info.position.y, info.position.z,
        info.velocity.x, info.velocity.y, info.velocity.z
    );
    mp_engine->set3dSourceAttenuation(
        soLoudHandle,
        Converter<Attenuation, unsigned int>::from_minty(info.attenuation),
        info.attenuationRolloff
    );
    mp_engine->set3dSourceMinMaxDistance(
        soLoudHandle,
        info.minDistance,
        info.maxDistance
    );
    m_dirty = true;
}

AudioHandle Minty::SoLoud_AudioManager::play(ClipHandle const clip, Float const volume, Float const pan, Bool const paused, UInt const bus)
{
    SoLoud_ClipData &clipData = m_clipDataPool.at(clip);
    SoLoud::handle const soLoudHandle = mp_engine->play(clipData.wav, volume, pan, paused, bus);
    m_dirty = true;
    return static_cast<AudioHandle>(soLoudHandle);
}

AudioHandle Minty::SoLoud_AudioManager::play_object(ClipHandle const clip, AudioSourceInfo const &source, Float const volume, Bool const paused, UInt const bus)
{
    SoLoud_ClipData &clipData = m_clipDataPool.at(clip);
    SoLoud::handle soLoudHandle = mp_engine->play3d(
        clipData.wav,
        source.position.x, source.position.y, source.position.z,
        source.velocity.x, source.velocity.y, source.velocity.z,
        volume, paused, bus
    );
    mp_engine->set3dSourceAttenuation(
        soLoudHandle,
        Converter<Attenuation, unsigned int>::from_minty(source.attenuation),
        source.attenuationRolloff
    );
    mp_engine->set3dSourceMinMaxDistance(
        soLoudHandle,
        source.minDistance,
        source.maxDistance
    );
    m_dirty = true;
    return static_cast<AudioHandle>(soLoudHandle);
}

AudioHandle Minty::SoLoud_AudioManager::play_background(ClipHandle const clip, Float const volume, Bool const paused, UInt const bus)
{
    SoLoud_ClipData &clipData = m_clipDataPool.at(clip);
    SoLoud::handle soLoudHandle = mp_engine->playBackground(clipData.wav, volume, paused, bus);
    return static_cast<AudioHandle>(soLoudHandle);
}

void Minty::SoLoud_AudioManager::stop(AudioHandle const handle)
{
    MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);
    SoLoud::handle soLoudHandle = static_cast<SoLoud::handle>(handle);
    mp_engine->stop(soLoudHandle);
}

void Minty::SoLoud_AudioManager::stop_all()
{
    mp_engine->stopAll();
}

void Minty::SoLoud_AudioManager::set_pause(AudioHandle const handle, Bool const paused)
{
    MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);
    SoLoud::handle const soLoudHandle = static_cast<SoLoud::handle>(handle);
    mp_engine->setPause(soLoudHandle, paused);
}

void Minty::SoLoud_AudioManager::set_pause_all(Bool const paused)
{
    mp_engine->setPauseAll(paused);
}

Bool Minty::SoLoud_AudioManager::get_pause(AudioHandle const handle) const
{
    MINTY_ASSERT(is_valid(handle), ErrorCodeEnum::Argument_KeyNotFound);
    SoLoud::handle const soLoudHandle = static_cast<SoLoud::handle>(handle);
    return mp_engine->getPause(soLoudHandle);
}
