#ifndef MINTY_RENDER_SHADERINFO_H
#define MINTY_RENDER_SHADERINFO_H

/**
 * @file ShaderInfo.h
 * @brief Header file defining the ShaderInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Data/UUID.h"
#include "Minty/FSM/Conditional.h"
#include "Minty/Render/ShaderPrimitiveTopology.h"
#include "Minty/Render/ShaderPolygonMode.h"
#include "Minty/Render/ShaderFrontFace.h"
#include "Minty/Render/ShaderCullMode.h"
#include "Minty/Render/DepthMode.h"
#include "Minty/Render/StencilMode.h"
#include "Minty/Render/ShaderVertexInput.h"
#include "Minty/Render/ShaderInput.h"

namespace Minty
{
    class Viewport;
    class ShaderModule;
    class RenderPass;

    /**
	 * @brief The arguments for a Shader.
	 */
	struct ShaderInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The priority of the Shader. Higher priority Shaders are rendered first.
		 */
		Int priority = 0;

		/**
		 * @brief The viewport this Shader is used to render to.
		 */
		Ref<Viewport> viewport = nullptr;

		/**
		 * @brief The ShaderModule for the fragment shader.
		 */
		Ref<ShaderModule> fragmentShaderModule = nullptr;

		/**
		 * @brief The name of the main function for the fragment shader module.
		 */
		String fragmentShaderModuleEntryPoint = "main";

		/**
		 * @brief The ShaderModule for the vertex shader.
		 */
		Ref<ShaderModule> vertexShaderModule = nullptr;

		/**
		 * @brief The name of the main function for the vertex shader module.
		 */
		String vertexShaderModuleEntryPoint = "main";

		/**
		 * @brief The RenderPass this Shader is used to render to.
		 */
		Ref<RenderPass> renderPass = nullptr;

		/**
		 * @brief The primitive topology of the Shader.
		 */
		ShaderPrimitiveTopology primitiveTopology = ShaderPrimitiveTopology::TriangleList;

		/**
		 * @brief The polygon mode of the Shader.
		 */
		ShaderPolygonMode polygonMode = ShaderPolygonMode::Fill;

		/**
		 * @brief The orientation of the front face of the polygons.
		 */
		ShaderFrontFace frontFace = ShaderFrontFace::Clockwise;

		/**
		 * @brief The cull mode of the Shader.
		 */
		ShaderCullMode cullMode = ShaderCullMode::None;

		/**
		 * @brief The width of the lines in the Shader. Must be 1.0f if not using line topology.
		 */
		Float lineWidth = 1.0f;

		/**
		 * @brief Support for transparency in the Shader.
		 */
		Bool transparency = false;

		/**
		 * @brief Should this Shader use the depth buffer?
		 */
		DepthMode depthMode = DepthMode::Write;

		/**
		 * @brief Defines the default depth test operation as 'less than'.
		 */
		Conditional depthTestOp = Conditional::LessThan;

		/**
		 * @brief Should this Shader use the stencil buffer?
		 */
		StencilMode stencilMode = StencilMode::None;

		/**
		 * @brief Defines the default stencil test operation as 'equal'.
		 */
		Conditional stencilTestOp = Conditional::Equal;

		/**
		 * @brief The vertex input of the Shader.
		 */
		ShaderVertexInput vertexInput;

		/**
		 * @brief The inputs of the Shader.
		 */
		Vector<ShaderInput> inputs;
	};
}

#endif // MINTY_RENDER_SHADERINFO_H