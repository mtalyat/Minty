#pragma once
#include "Minty/Audio/AudioClip.h"
#include "Minty/Library/SoLoud.h"

namespace Minty
{
	class SoLoud_AudioClip
		: public AudioClip
	{
#pragma region Variables

	private:
		SoLoud::Wav* mp_clip;

#pragma endregion

#pragma region Constructors

	public:
		SoLoud_AudioClip(AudioClipBuilder const& builder);

		~SoLoud_AudioClip() override;

#pragma endregion

#pragma region Get Set

	public:
		void* get_native() const override { return mp_clip; }

#pragma endregion

	};
}