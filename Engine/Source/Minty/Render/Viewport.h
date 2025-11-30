#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// Arguments for a Viewport.
	/// </summary>
	struct ViewportInfo
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = UUID();

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
		/// <param name="info">The arguments.</param>
		Viewport(ViewportInfo const& info)
			: Asset(info.id)
		{
			MINTY_ASSERT(info.minDepth >= 0.0f && info.minDepth <= 1.0f, ErrorCode::Argument_OutOfBounds, info.minDepth);
			MINTY_ASSERT(info.maxDepth >= 0.0f && info.maxDepth <= 1.0f, ErrorCode::Argument_OutOfBounds, info.maxDepth);
			MINTY_ASSERT(info.minDepth <= info.maxDepth, ErrorCode::Argument_IncorrectOrder, info.minDepth, info.maxDepth);
		}

		virtual ~Viewport() override
		{
		}

#pragma endregion

#pragma region Accessors

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
		/// Called when this Viewport is binded for rendering.
		/// </summary>
		virtual void on_bind() = 0;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Viewport.</returns>
		inline AssetType get_asset_type() const override { return AssetType::Viewport; }

#pragma endregion

#pragma region Statics

	public:
		static Shared<Viewport> create(ViewportInfo const& info = {});

#pragma endregion
	};
}