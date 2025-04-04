#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// Arguments for a Viewport.
	/// </summary>
	struct ViewportBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The position of the view.
		/// </summary>
		Int2 viewPosition = { 0, 0 };

		/// <summary>
		/// The size of the view.
		/// </summary>
		UInt2 viewSize = { 0, 0 };

		/// <summary>
		/// The position of the mask.
		/// </summary>
		Int2 maskPosition = { 0, 0 };

		/// <summary>
		/// The size of the mask.
		/// </summary>
		UInt2 maskSize = { 0, 0 };

		/// <summary>
		/// The minimum depth of the viewport.
		/// </summary>
		Float minDepth = 0.0f;

		/// <summary>
		/// The maximum depth of the viewport.
		/// </summary>
		Float maxDepth = 1.0f;
	};

	/// <summary>
	/// Represents a view with a mask that can be used to render to a specific area of the screen.
	/// </summary>
	class Viewport
		: public Asset
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Viewport.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Viewport(ViewportBuilder const& builder)
			: Asset(builder.id)
		{
			MINTY_ASSERT(builder.minDepth >= 0.0f && builder.minDepth <= 1.0f, "ViewportBuilder minDepth must be between 0.0 and 1.0.");
			MINTY_ASSERT(builder.maxDepth >= 0.0f && builder.maxDepth <= 1.0f, "ViewportBuilder maxDepth must be between 0.0 and 1.0.");
			MINTY_ASSERT(builder.minDepth <= builder.maxDepth, "ViewportBuilder minDepth must be less than or equal to maxDepth.");
		}

		virtual ~Viewport() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Sets the view position and mask position.
		/// </summary>
		/// <param name="position">The new value.</param>
		virtual void set_position(Int2 const& position) = 0;

		/// <summary>
		/// Sets the view size and mask size.
		/// </summary>
		/// <param name="size">The new value.</param>
		virtual void set_size(UInt2 const& size) = 0;

		/// <summary>
		/// Gets the view position.
		/// </summary>
		/// <returns>The value.</returns>
		virtual Int2 get_view_position() const = 0;

		/// <summary>
		/// Sets the view position.
		/// </summary>
		/// <param name="position">The new value.</param>
		virtual void set_view_position(Int2 const& position) = 0;

		/// <summary>
		/// Gets the view size.
		/// </summary>
		/// <returns>The value.</returns>
		virtual UInt2 get_view_size() const = 0;

		/// <summary>
		/// Sets the view size.
		/// </summary>
		/// <param name="size">The new value.</param>
		virtual void set_view_size(UInt2 const& size) = 0;

		/// <summary>
		/// Gets the mask position.
		/// </summary>
		/// <returns>The value.</returns>
		virtual Int2 get_mask_position() const = 0;

		/// <summary>
		/// Sets the mask position.
		/// </summary>
		/// <param name="position">The new value.</param>
		virtual void set_mask_position(Int2 const& position) = 0;

		/// <summary>
		/// Gets the mask size.
		/// </summary>
		/// <returns>The value.</returns>
		virtual UInt2 get_mask_size() const = 0;

		/// <summary>
		/// Sets the mask size.
		/// </summary>
		/// <param name="size">The new value.</param>
		virtual void set_mask_size(UInt2 const& size) = 0;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Viewport.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Viewport; }

#pragma endregion

#pragma region Statics

	public:
		static Owner<Viewport> create(ViewportBuilder const& builder = {});

#pragma endregion
	};
}