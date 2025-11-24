#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/// <summary>
	/// The arguments used to create an AudioClip.
	/// </summary>
	struct AudioClipBuilder
	{
		/// <summary>
		/// The ID of the AudioClip.
		/// </summary>
		UUID id;

		/// <summary>
		/// The byte data of the AudioClip.
		/// </summary>
		Vector<Byte> data;

		/// <summary>
		/// The starting volume of the AudioClip.
		/// </summary>
		Float volume = 1.0f;

		/// <summary>
		/// If true, the AudioClip will loop.
		/// </summary>
		Bool loop = false;

		/// <summary>
		/// The loop point of the AudioClip. 0.0 = start, 1.0 = end.
		/// </summary>
		Float loopPoint = 0.0f;

		/// <summary>
		/// If true, the AudioClip can only be played once at a time.
		/// </summary>
		Bool exclusive = false;
	};

	class AudioClip
		: public Asset
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new AudioClip using the given AudioClipBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		AudioClip(AudioClipBuilder const& builder)
			: Asset(builder.id)
		{
		}

		virtual ~AudioClip()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the native audio clip object.
		/// </summary>
		/// <returns>The object.</returns>
		virtual void* get_native() const = 0;

		/// <summary>
		/// Gets the type of this Asset.
		/// </summary>
		/// <returns>AudioClip.</returns>
		AssetType get_asset_type() const override { return AssetType::AudioClip; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new AudioClip using the given AudioClipBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		static Owner<AudioClip> create(AudioClipBuilder const& builder = {});

#pragma endregion
	};
}