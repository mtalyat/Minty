#ifndef MINTY_RENDER_RENDERPASS_H
#define MINTY_RENDER_RENDERPASS_H

/**
 * @file RenderPass.h
 * @brief Header file for the RenderPass class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Render/RenderAttachment.h"
#include "Minty/Render/RenderTarget.h"

namespace Minty
{
	struct RenderPassInfo;

	/**
	 * @brief A RenderPass handles the attachments used for rendering.
	 */
	class RenderPass
		: public Asset
	{
#pragma region Variables

	private:
		// all targets that use this RenderPass
		Set<RenderTarget*> m_renderTargets;
		Bool m_colorAttachment;
		Bool m_depthAttachment;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new RenderPass.
		 * @param info The arguments.
		 */
		RenderPass(RenderPassInfo const& info);

		virtual ~RenderPass() override = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if this RenderPass has a color attachment.
		 * @return True, if there is a color attachment.
		 */
		inline Bool has_color_attachment() const { return m_colorAttachment; }

		/**
		 * @brief Checks if this RenderPass has a depth attachment.
		 * @return True, if there is a depth attachment.
		 */
		inline Bool has_depth_attachment() const { return m_depthAttachment; }

		/**
		 * @brief Gets the AssetType for this Asset.
		 * @return RenderPass.
		 */
		inline AssetType get_asset_type() const override { return AssetType::RenderPass; }

		/**
		 * @brief Gets the native RenderPass object.
		 * @return The native object.
		 */
		virtual Any get_native() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reinitializes all of the RenderTargets that use this RenderPass.
		 */
		void refresh();

		/**
		 * @brief Registers a RenderTarget with this RenderPass.
		 * @param renderTarget The RenderTarget.
		 */
		void register_render_target(RenderTarget* const renderTarget);

		/**
		 * @brief Registers a RenderTarget with this RenderPass.
		 * @param renderTarget The RenderTarget.
		 */
		void unregister_render_target(RenderTarget* const renderTarget);

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Creates a new RenderPass.
		 * @param info The arguments.
		 * @return A RenderPass Owner.
		 */
		static Shared<RenderPass> create(RenderPassInfo const& info);

		/**
		 * @brief Creates a default RenderPass.
		 * @return A RenderPass Owner.
		 */
		static Shared<RenderPass> create();

#pragma endregion
	};
}

#endif // MINTY_RENDER_RENDERPASS_H