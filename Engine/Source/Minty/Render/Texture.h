#ifndef MINTY_RENDER_TEXTURE_H
#define MINTY_RENDER_TEXTURE_H

/**
 * @file Texture.h
 * @brief Header file defining the Texture class and TextureInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Render/AddressMode.h"
#include "Minty/Render/Filter.h"
#include "Minty/Render/Image.h"

namespace Minty
{
	struct TextureInfo;

	/**
	 * @brief An Image used for rendering.
	 */
	class Texture
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Texture.
		 * @param info The Texture info.
		 */
		Texture(TextureInfo const& info);

		virtual ~Texture() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Image this Texture uses.
		 * @return The Image.
		 */
		Ref<Image> const& get_image() const { return m_image; }

		/**
		 * @brief Gets the size of this Texture.
		 * @return The width and height of this Texture's image in pixels.
		 */
		inline UInt2 get_size() const { return m_image->get_size(); }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Texture.
		 */
		AssetType get_asset_type() const override { return AssetType::Texture; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Creates a new Texture.
		 * @param info The arguments.
		 * @return A Texture Owner.
		 */
		static Shared<Texture> create(TextureInfo const& info);

#pragma endregion

#pragma region Variables

	private:
		Ref<Image> m_image;

#pragma endregion
	};
}

#endif // MINTY_RENDER_TEXTURE_H