#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Render/AddressMode.h"
#include "Minty/Render/Filter.h"
#include "Minty/Render/Image.h"

namespace Minty
{
	/// <summary>
	/// Arguments for creating a Texture.
	/// </summary>
	struct TextureBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The Image this Texture uses.
		/// </summary>
		Ref<Image> image;

		/// <summary>
		/// The filter to use for this Texture.
		/// </summary>
		Filter filter = Filter::Undefined;

		/// <summary>
		/// The coordinate address mode to use for this Texture.
		/// </summary>
		AddressMode addressMode = AddressMode::Repeat;

		/// <summary>
		/// When true, the coordinates are normalized to the range [0, 1]. Otherwise, they are from [0, width] and [0, height].
		/// </summary>
		Bool normalizeCoordinates = true;
	};

	/// <summary>
	/// An Image used for rendering.
	/// </summary>
	class Texture
		: public Asset
	{
#pragma region Variables

	private:
		Ref<Image> m_image;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Texture.
		/// </summary>
		/// <param name="builder">The Texture builder.</param>
		Texture(TextureBuilder const& builder)
			: Asset(builder.id)
			, m_image(builder.image)
		{
			MINTY_ASSERT(m_image != nullptr, "Image must not be null.");
		}

		virtual ~Texture() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Image this Texture uses.
		/// </summary>
		/// <returns>The Image.</returns>
		Ref<Image> const& get_image() const { return m_image; }

		/// <summary>
		/// Gets the size of this Texture.
		/// </summary>
		/// <returns>The width and height of this Texture's image in pixels.</returns>
		UInt2 get_size() const { return m_image->get_size(); }

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Texture.</returns>
		AssetType get_asset_type() const override { return AssetType::Texture; }

#pragma endregion

#pragma region Statics

	public:
		static Owner<Texture> create(TextureBuilder const& builder = {});

#pragma endregion

	};
}