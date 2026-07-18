#pragma once

/**
 * @file RenderPass.h
 * @brief Header file for the RenderPass class.
 * @author Mitchell Talyat
 */

#include "RenderAttachment.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Type/Color.hpp"
#include "Resource/Type/Handle.hpp"

namespace Minty
{
	/**
	 * @brief A RenderPass handles the attachments used for rendering.
	 */
	struct RenderPassResource
	{
		Vector<RenderAttachment> attachments;
		RenderTargetResourceHandle renderTarget = INVALID_HANDLE;
		ViewportResourceHandle viewport = INVALID_HANDLE;
		Color clearColor = Color::black();
		Float clearDepth = 1.0f;
		UInt clearStencil = 0;
	};

	template<>
	struct Serializer<RenderPassResource>
	{
		static Bool serialize(Writer& writer, RenderPassResource const& value);
		static Bool deserialize(Reader& reader, RenderPassResource& value);
	};
}
