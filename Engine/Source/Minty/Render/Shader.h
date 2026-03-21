#ifndef MINTY_RENDER_SHADER_H
#define MINTY_RENDER_SHADER_H

/**
 * @file Shader.h
 * @brief Header file for the Shader class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Map.h"
#include "Minty/FSM/Conditional.h"
#include "Minty/Render/ShaderCullMode.h"
#include "Minty/Render/ShaderFrontFace.h"
#include "Minty/Render/ShaderInput.h"
#include "Minty/Render/ShaderPolygonMode.h"
#include "Minty/Render/ShaderPrimitiveTopology.h"
#include "Minty/Render/ShaderVertexInput.h"
#include "Minty/Render/DepthMode.h"
#include "Minty/Render/StencilMode.h"
#include "Minty/Render/RenderPass.h"

namespace Minty
{
	class Material;
	class ShaderModule;
	class Viewport;
	struct ShaderInfo;

	/**
	 * @brief Represents a Shader program on the GPU.
	 */
	class Shader
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Shader.
		 * @param info The arguments.
		 */
		Shader(ShaderInfo const& info);

		virtual ~Shader() override = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Returns the priority of this Shader.
		 * @return The priority.
		 */
		Int get_priority() const { return m_priority; }

		/**
		 * @brief Gets the depth mode of this Shader.
		 * @return The depth mode.
		 */
		DepthMode get_depth_mode() const { return m_depthMode; }

		/**
		 * @brief Gets the stencil mode of this Shader.
		 * @return The stencil mode.
		 */
		StencilMode get_stencil_mode() const { return m_stencilMode; }

		/**
		 * @brief Gets the RenderPass this Shader is used to render to.
		 * @return The RenderPass.
		 */
		Shared<RenderPass> const& get_render_pass() const { return m_renderPass; }

		/**
		 * @brief Checks if this Shader contains an input with the given name.
		 * @param name The name.
		 * @return True if it exists.
		 */
		Bool contains_input(String const& name) const { return m_inputs.contains(name); }

		/**
		 * @brief Gets the input with the given name.
		 * @param name The name.
		 * @return The input.
		 */
		ShaderInput const& get_input(String const& name) const
		{
			MINTY_ASSERT_F(m_inputs.contains(name), ErrorCode::Argument_KeyNotFound, name);
			return m_inputs[name];
		}

		/**
		 * @brief Gets all of the inputs of this Shader.
		 * @return A map of names and inputs.
		 */
		Map<String, ShaderInput> const& get_inputs() const { return m_inputs; }

		/**
		 * @brief Sets the input data for all Materials that use this Shader.
		 * @param name The name.
		 * @param data A pointer to the data.
		 * @param size The size of the data.
		 */
		void set_global_input(String const& name, AnyConst const data, Size const size);

		template <typename T>
		inline void set_global_input(String const& name, T const& value)
		{
			set_global_input(name, static_cast<AnyConst>(&value), sizeof(T));
		}

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Shader.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Shader; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when this Shader is binded for rendering.
		 */
		virtual void on_bind() = 0;

		/**
		 * @brief Registers a Material to this Shader.
		 * @param material The Material.
		 */
		void register_material(Material* const material);

		/**
		 * @brief Unregisters a Material from this Shader.
		 * @param material The Material.
		 */
		void unregister_material(Material* const material);

		/**
		 * @brief Creates a new Shader.
		 * @param info The arguments.
		 * @return A Shader Owner.
		 */
		static Shared<Shader> create(ShaderInfo const& info);

		/**
		 * @brief Creates a default Shader.
		 * @return A Shader Owner.
		 */
		static Shared<Shader> create();

#pragma endregion

#pragma region Variables

	private:
		Int m_priority;
		// the render pass this Shader belongs to
		Shared<RenderPass> m_renderPass;
		// list of inputs to the shader (for verification when setting values)
		Map<String, ShaderInput> m_inputs;
		// list of materials that use this shader (for global updates)
		Set<Material*> m_materials;
		DepthMode m_depthMode;
		StencilMode m_stencilMode;

#pragma endregion
	};
}

#endif // MINTY_RENDER_SHADER_H