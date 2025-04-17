#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Render/RenderAttachment.h"
#include "Minty/Render/RenderTarget.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a RenderPass.
	/// </summary>
	struct RenderPassBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The color attachment, if any.
		/// </summary>
		RenderAttachment const* colorAttachment = nullptr;

		/// <summary>
		/// The depth attachment, if any.
		/// </summary>
		RenderAttachment const* depthAttachment = nullptr;
	};

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
		/// <summary>
		/// Creates a new RenderPass.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		RenderPass(RenderPassBuilder const& builder)
			: Asset(builder.id)
			, m_colorAttachment(builder.colorAttachment != nullptr)
			, m_depthAttachment(builder.depthAttachment != nullptr)
		{
			MINTY_ASSERT(m_colorAttachment || m_depthAttachment, "RenderPass must have at least one attachment.");
		}

		virtual ~RenderPass() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if this RenderPass has a color attachment.
		/// </summary>
		/// <returns>True, if there is a color attachment.</returns>
		inline Bool has_color_attachment() const { return m_colorAttachment; }

		/// <summary>
		/// Checks if this RenderPass has a depth attachment.
		/// </summary>
		/// <returns>True, if there is a depth attachment.</returns>
		inline Bool has_depth_attachment() const { return m_depthAttachment; }

		/// <summary>
		/// Gets the AssetType for this Asset.
		/// </summary>
		/// <returns>RenderPass.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::RenderPass; }

		/// <summary>
		/// Gets the native RenderPass object.
		/// </summary>
		/// <returns>The native object.</returns>
		virtual void* get_native() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Reinitializes all of the RenderTargets that use this RenderPass.
		/// </summary>
		/// <param name="builder">The RenderTargetBuilder to use.</param>
		void refresh(RenderTargetBuilder const& builder);

		/// <summary>
		/// Registers a RenderTarget with this RenderPass.
		/// </summary>
		/// <param name="renderTarget">The RenderTarget.</param>
		void register_render_target(RenderTarget* const renderTarget);

		/// <summary>
		/// Registers a RenderTarget with this RenderPass.
		/// </summary>
		/// <param name="renderTarget">The RenderTarget.</param>
		void unregister_render_target(RenderTarget* const renderTarget);

#pragma endregion

#pragma region Statics

	public:
		static Owner<RenderPass> create(RenderPassBuilder const& builder = {});

#pragma endregion

	};
}