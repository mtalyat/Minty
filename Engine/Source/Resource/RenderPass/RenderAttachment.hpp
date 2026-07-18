#pragma once

/**
 * @file RenderAttachment.h
 * @brief Header file defining the RenderAttachment struct.
 * @author Mitchell Talyat
 */

#include "Core/Type/LoadOperation.hpp"
#include "Core/Type/StoreOperation.hpp"
#include "Resource/Image/ImageAspect.hpp"
#include "Resource/Image/ImageLayout.hpp"
#include "Core/Serialize/Serializer.hpp"

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
