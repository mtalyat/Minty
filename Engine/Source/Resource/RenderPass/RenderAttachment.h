#pragma once

/**
 * @file RenderAttachment.h
 * @brief Header file defining the RenderAttachment struct.
 * @author Mitchell Talyat
 */

#include "Core/Type/LoadOperation.h"
#include "Core/Type/StoreOperation.h"
#include "Resource/Image/ImageAspect.h"
#include "Resource/Image/ImageLayout.h"
#include "Core/Serialize/Serializer.h"

namespace Minty
{
	/**
	 * @brief Holds data for an attachment in a render pass.
	 */
	struct RenderAttachment
	{
		/**
		 * @brief The aspect of this attachment.
		 */
		ImageAspectFlags aspect = ImageAspectFlagsEnum::Undefined;

		/**
		 * @brief The load operation to perform.
		 */
		LoadOperation loadOperation = LoadOperationEnum::DontCare;

		/**
		 * @brief The store operation to perform.
		 */
		StoreOperation storeOperation = StoreOperationEnum::DontCare;

		/**
		 * @brief The initial layout of this attachment.
		 */
		ImageLayout initialLayout = ImageLayoutEnum::Undefined;

		/**
		 * @brief The final layout of this attachment.
		 */
		ImageLayout finalLayout = ImageLayoutEnum::Undefined;
	};

	template<>
	struct Serializer<RenderAttachment>
	{
		static Bool serialize(Writer& writer, RenderAttachment const& value);
		static Bool deserialize(Reader& reader, RenderAttachment& value);
	};
}
