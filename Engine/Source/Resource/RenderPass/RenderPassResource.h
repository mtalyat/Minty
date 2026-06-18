#pragma once

/**
 * @file RenderPass.h
 * @brief Header file for the RenderPass class.
 * @author Mitchell Talyat
 */

#include "RenderAttachment.h"
#include "Core/Serialize/Serializer.h"
#include "Core/Data/Vector.h"

namespace Minty
{
	/**
	 * @brief A RenderPass handles the attachments used for rendering.
	 */
	struct RenderPassResource
	{
		Vector<RenderAttachment> attachments;
	};

	template<>
	struct Serializer<RenderPassResource>
	{
		static Bool serialize(Writer& writer, RenderPassResource const& value);
		static Bool deserialize(Reader& reader, RenderPassResource& value);
	};
}
