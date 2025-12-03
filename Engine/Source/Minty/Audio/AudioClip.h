#ifndef MINTY_AUDIO_AUDIOCLIP_H
#define MINTY_AUDIO_AUDIOCLIP_H

/**
 * @file AudioClip.h
 * @brief Header file defining the AudioClip class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	struct AudioClipInfo;
	
	/**
	 * @brief Class representing an audio clip asset.
	 */
	class AudioClip
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an AudioClip with the given arguments.
		 * @param info The arguments.
		 */
		AudioClip(AudioClipInfo const& info);

		virtual ~AudioClip() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the native audio clip object.
		 * @return The native audio clip object.
		 */
		virtual Any get_native() const = 0;

		/**
		 * @brief Gets the AssetType of this AudioClip.
		 * @return The AssetType.
		 */
		AssetType get_asset_type() const override { return AssetType::AudioClip; }
		
		/**
		 * @brief Creates an AudioClip with the given arguments.
		 * @param info The arguments.
		 * @return A Shared pointer to the created AudioClip.
		 */
		static Shared<AudioClip> create(AudioClipInfo const& info);

		/**
		 * @brief Creates a default AudioClip.
		 * @return A Shared pointer to the created default AudioClip.
		 */
		static Shared<AudioClip> create();

#pragma endregion
	};
}

#endif // MINTY_AUDIO_AUDIOCLIP_H