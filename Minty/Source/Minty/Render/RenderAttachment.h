#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/ImageLayout.h"
#include "Minty/Render/LoadOperation.h"
#include "Minty/Render/StoreOperation.h"

namespace Minty
{
	/// <summary>
	/// Holds data for an attachment in a render pass.
	/// </summary>
	struct RenderAttachment
	{
#pragma region Classes

	public:
		/// <summary>
		/// The type.
		/// </summary>
		enum class Type
		{
			/// <summary>
			/// Invalid.
			/// </summary>
			Undefined,

			/// <summary>
			/// Color attachment.
			/// </summary>
			Color,

			/// <summary>
			/// Depth attachment.
			/// </summary>
			Depth
		};

#pragma endregion

#pragma region Variables

	public:
		/// <summary>
		/// The Type of this attachment.
		/// </summary>
		Type type = Type::Undefined;

		/// <summary>
		/// The format this attachment uses.
		/// </summary>
		Format format = Format::Default;

		/// <summary>
		/// The load operation to perform.
		/// </summary>
		LoadOperation loadOperation = LoadOperation::DontCare;

		/// <summary>
		/// The store operation to perform.
		/// </summary>
		StoreOperation storeOperation = StoreOperation::DontCare;

		/// <summary>
		/// The initial layout of this attachment.
		/// </summary>
		ImageLayout initialLayout = ImageLayout::Undefined;

		/// <summary>
		/// The final layout of this attachment.
		/// </summary>
		ImageLayout finalLayout = ImageLayout::Undefined;

#pragma endregion
	};
}