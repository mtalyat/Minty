#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/ImageLayout.h"

namespace Minty
{
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
			/// Color attachment.
			/// </summary>
			Color,

			/// <summary>
			/// Depth attachment.
			/// </summary>
			Depth
		};
		
		/// <summary>
		/// The load operation.
		/// </summary>
		enum class LoadOperation
		{
			/// <summary>
			/// Do nothing with the previous data.
			/// </summary>
			DontCare,

			/// <summary>
			/// Loads the previous data.
			/// </summary>
			Load,
			
			/// <summary>
			/// Clears the previous data.
			/// </summary>
			Clear,
		};
		
		/// <summary>
		/// The store operation.
		/// </summary>
		enum class StoreOperation
		{
			/// <summary>
			/// Does nothing with the current data.
			/// </summary>
			DontCare,

			/// <summary>
			/// Stores the current data.
			/// </summary>
			Store,
		};

#pragma endregion

#pragma region Variables

	public:
		/// <summary>
		/// The Type of this attachment.
		/// </summary>
		Type type;

		/// <summary>
		/// The format this attachment uses.
		/// </summary>
		Format format;

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