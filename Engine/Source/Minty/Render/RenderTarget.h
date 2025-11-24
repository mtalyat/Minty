#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	class Image;
	class RenderPass;

	/// <summary>
	/// The arguments for a RenderTarget.
	/// </summary>
	struct RenderTargetBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The RenderPass this RenderTarget belongs to.
		/// </summary>
		Ref<RenderPass> renderPass = nullptr;

		/// <summary>
		/// The images this RenderTarget uses.
		/// </summary>
		Vector<Ref<Image>> images;

		/// <summary>
		/// If true, the RenderTarget is bound to the screen surface.
		/// </summary>
		Bool surfaceBound = false;
	};

	/// <summary>
	/// Represents a target that can be rendered to. (ex. a framebuffer/the screen, an image, etc.)
	/// </summary>
	class RenderTarget
		: public Asset
	{
#pragma region Variables

	private:
		Ref<RenderPass> m_renderPass;
		Vector<Ref<Image>> m_images;
		Bool m_surfaceBound = false; // if true, the RenderTarget is bound to the screen surface

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new RenderTarget.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		RenderTarget(RenderTargetBuilder const& builder);

		virtual ~RenderTarget() override;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if this RenderTarget is bound to the screen surface.
		/// </summary>
		/// <returns>True if bound to the Surface.</returns>
		Bool is_surface_bound() const { return m_surfaceBound; }

		/// <summary>
		/// Gets the RenderPass this RenderTarget belongs to.
		/// </summary>
		/// <returns>The RenderPass.</returns>
		Ref<RenderPass> const& get_render_pass() const { return m_renderPass; }

		/// <summary>
		/// Gets the images this RenderTarget uses.
		/// </summary>
		/// <returns>The images.</returns>
		Vector<Ref<Image>> const& get_images() const { return m_images; }

		/// <summary>
		/// Gets the size of this RenderTarget in pixels.
		/// </summary>
		/// <returns>The size.</returns>
		virtual UInt2 get_size() const = 0;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>RenderTarget.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::RenderTarget; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Reinitializes this RenderTarget with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		virtual void refresh(RenderTargetBuilder const& builder) = 0;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new RenderTarget.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A RenderTarget Owner.</returns>
		static Owner<RenderTarget> create(RenderTargetBuilder const& builder = {});

#pragma endregion
	};
}