#ifndef MINTY_RENDER_RENDERTARGET_H
#define MINTY_RENDER_RENDERTARGET_H

/**
 * @file RenderTarget.h
 * @brief Header file defining the RenderTarget class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	class Image;
	class RenderPass;

	/**
	 * @brief The arguments for a RenderTarget.
	 */
	struct RenderTargetInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The RenderPass this RenderTarget belongs to.
		 */
		Ref<RenderPass> renderPass = nullptr;

		/**
		 * @brief The images this RenderTarget uses.
		 */
		Vector<Ref<Image>> images;

		/**
		 * @brief If true, the RenderTarget is bound to the screen surface.
		 */
		Bool surfaceBound = false;
	};

	/**
	 * @brief Represents a target that can be rendered to. (ex. a framebuffer/the screen, an image, etc.)
	 */
	class RenderTarget
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new RenderTarget.
		 * @param info The arguments.
		 */
		RenderTarget(RenderTargetInfo const& info);

		virtual ~RenderTarget() override;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if this RenderTarget is bound to the screen surface.
		 * @return True if bound to the Surface.
		 */
		Bool is_surface_bound() const { return m_surfaceBound; }

		/**
		 * @brief Gets the RenderPass this RenderTarget belongs to.
		 * @return The RenderPass.
		 */
		Ref<RenderPass> const& get_render_pass() const { return m_renderPass; }

		/**
		 * @brief Gets the images this RenderTarget uses.
		 * @return The images.
		 */
		Vector<Ref<Image>> const& get_images() const { return m_images; }

		/**
		 * @brief Gets the size of this RenderTarget in pixels.
		 * @return The size.
		 */
		virtual UInt2 get_size() const = 0;

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return RenderTarget.
		 */
		inline AssetType get_asset_type() const override { return AssetType::RenderTarget; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reinitializes this RenderTarget with the given arguments.
		 * @param info The arguments.
		 */
		virtual void refresh(RenderTargetInfo const& info) = 0;

		/**
		 * @brief Creates a new RenderTarget.
		 * @param info The arguments.
		 * @return A RenderTarget Owner.
		 */
		static Shared<RenderTarget> create(RenderTargetInfo const& info = {});

#pragma endregion

#pragma region Variables

	private:
		Ref<RenderPass> m_renderPass;
		Vector<Ref<Image>> m_images;
		Bool m_surfaceBound; // if true, the RenderTarget is bound to the screen surface

#pragma endregion
	};
}

#endif // MINTY_RENDER_RENDERTARGET_H