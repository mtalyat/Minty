#pragma once
#include "Minty/Audio/AudioManager.h"
#include "Minty/Library/SoLoud.h"

namespace Minty
{
	class SoLoud_AudioManager
		: public AudioManager
	{
#pragma region Variables

	private:
		SoLoud::Soloud* m_engine;
		Bool m_dirty;

#pragma endregion

#pragma region Constructors

	public:
		SoLoud_AudioManager(AudioManagerBuilder const& builder)
			: AudioManager(builder)
			, m_engine(new SoLoud::Soloud())
			, m_dirty(false)
		{
		}

		~SoLoud_AudioManager()
		{
			delete m_engine;
		}

#pragma endregion

#pragma region Get Set

	public:
		Bool is_valid(Handle const handle) const override;

		void set_audio_listener(AudioListener const& listener) override;

		void set_audio_source(Handle const handle, AudioSource const& source) override;

		void set_pause(Handle const handle, Bool const paused) override;

		Bool get_pause(Handle const handle) const override;

		void set_pause_all(Bool const paused) override;

#pragma endregion

#pragma region Methods

	public:
		void initialize() override;

		void dispose() override;

		void finalize() override;

		Handle play(Ref<AudioClip> const& clip, Float const volume, Float const pan, Bool const paused, UInt const bus) override;

		Handle play_object(Ref<AudioClip> const& clip, AudioSource const& source, Float const volume, Bool const paused, UInt const bus) override;

		Handle play_background(Ref<AudioClip> const& clip, Float const volume, Bool const paused, UInt const bus) override;

		void stop(Handle const handle) override;

		void stop_all() override;

#pragma endregion
	};
}