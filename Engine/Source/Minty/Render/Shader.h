#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/FSM/Conditional.h"
#include "Minty/Render/ShaderCullMode.h"
#include "Minty/Render/ShaderFrontFace.h"
#include "Minty/Render/ShaderInput.h"
#include "Minty/Render/ShaderPolygonMode.h"
#include "Minty/Render/ShaderPrimitiveTopology.h"
#include "Minty/Render/ShaderVertexInput.h"
#include "Minty/Render/DepthMode.h"
#include "Minty/Render/StencilMode.h"

namespace Minty
{
	class Material;
	class RenderPass;
	class ShaderModule;
	class Viewport;

	/// <summary>
	/// The arguments for a Shader.
	/// </summary>
	struct ShaderInfo
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The priority of the Shader. Higher priority Shaders are rendered first.
		/// </summary>
		Int priority = 0;

		/// <summary>
		/// The viewport this Shader is used to render to.
		/// </summary>
		Ref<Viewport> viewport = nullptr;

		/// <summary>
		/// The ShaderModule for the fragment shader.
		/// </summary>
		Ref<ShaderModule> fragmentShaderModule = nullptr;

		/// <summary>
		/// The name of the main function for the fragment shader module.
		/// </summary>
		String fragmentShaderModuleEntryPoint = "main";

		/// <summary>
		/// The ShaderModule for the vertex shader.
		/// </summary>
		Ref<ShaderModule> vertexShaderModule = nullptr;

		/// <summary>
		/// The name of the main function for the vertex shader module.
		/// </summary>
		String vertexShaderModuleEntryPoint = "main";

		/// <summary>
		/// The RenderPass this Shader is used to render to.
		/// </summary>
		Ref<RenderPass> renderPass = nullptr;

		/// <summary>
		/// The primitive topology of the Shader.
		/// </summary>
		ShaderPrimitiveTopology primitiveTopology = ShaderPrimitiveTopology::TriangleList;

		/// <summary>
		/// The polygon mode of the Shader.
		/// </summary>
		ShaderPolygonMode polygonMode = ShaderPolygonMode::Fill;

		/// <summary>
		/// The orientation of the front face of the polygons.
		/// </summary>
		ShaderFrontFace frontFace = ShaderFrontFace::Clockwise;

		/// <summary>
		/// The cull mode of the Shader.
		/// </summary>
		ShaderCullMode cullMode = ShaderCullMode::None;

		/// <summary>
		/// The width of the lines in the Shader. Must be 1.0f if not using line topology.
		/// </summary>
		Float lineWidth = 1.0f;

		/// <summary>
		/// Support for transparency in the Shader.
		/// </summary>
		Bool transparency = false;

		/// <summary>
		/// Should this Shader use the depth buffer?
		/// </summary>
		DepthMode depthMode = DepthMode::Write;

		/// <summary>
		/// Defines the default depth test operation as 'less than'.
		/// </summary>
		Conditional depthTestOp = Conditional::LessThan;

		/// <summary>
		/// Should this Shader use the stencil buffer?
		/// </summary>
		StencilMode stencilMode = StencilMode::None;

		/// <summary>
		/// Defines the default stencil test operation as 'equal'.
		/// </summary>
		Conditional stencilTestOp = Conditional::Equal;

		/// <summary>
		/// The vertex input of the Shader.
		/// </summary>
		ShaderVertexInput vertexInput;

		/// <summary>
		/// The inputs of the Shader.
		/// </summary>
		Vector<ShaderInput> inputs;
	};

	/// <summary>
	/// Represents a Shader program on the GPU.
	/// </summary>
	class Shader
		: public Asset
	{
#pragma region Variables

	private:
		Int m_priority;
		// the render pass this Shader belongs to
		Ref<RenderPass> m_renderPass;
		// list of inputs to the shader (for verification when setting values)
		Map<String, ShaderInput> m_inputs;
		// list of materials that use this shader (for global updates)
		Set<Material*> m_materials;
		DepthMode m_depthMode;
		StencilMode m_stencilMode;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates 
		/// </summary>
		/// <param name="info"></param>
		Shader(ShaderInfo const& info);

		virtual ~Shader() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Returns the priority of this Shader.
		/// </summary>
		/// <returns>The priority.</returns>
		Int get_priority() const { return m_priority; }

		/// <summary>
		/// Gets the depth mode of this Shader.
		/// </summary>
		/// <returns>The depth mode.</returns>
		DepthMode get_depth_mode() const { return m_depthMode; }

		/// <summary>
		/// Gets the stencil mode of this Shader.
		/// </summary>
		/// <returns>The stencil mode.</returns>
		StencilMode get_stencil_mode() const { return m_stencilMode; }

		/// <summary>
		/// Gets the RenderPass this Shader is used to render to.
		/// </summary>
		/// <returns>The RenderPass.</returns>
		Ref<RenderPass> const& get_render_pass() const { return m_renderPass; }

		/// <summary>
		/// Checks if this Shader contains an input with the given name.
		/// </summary>
		/// <param name="name">The name.</param>
		/// <returns>True if it exists.</returns>
		Bool contains_input(String const& name) const { return m_inputs.contains(name); }

		/// <summary>
		/// Gets the input with the given name.
		/// </summary>
		/// <param name="name">The name.</param>
		/// <returns>The input.</returns>
		ShaderInput const& get_input(String const& name) const
		{
			MINTY_ASSERT(m_inputs.contains(name), F("Shader does not contain input with name: {}", name));
			return m_inputs[name];
		}

		/// <summary>
		/// Gets all of the inputs of this Shader.
		/// </summary>
		/// <returns>A map of names and inputs.</returns>
		Map<String, ShaderInput> const& get_inputs() const { return m_inputs; }

		/// <summary>
		/// Sets the input data for all Materials that use this Shader.
		/// </summary>
		/// <param name="name">The name.</param>
		/// <param name="data">A pointer to the data.</param>
		/// <param name="size">The size of the data.</param>
		void set_global_input(String const& name, void const* const data, Size const size);

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Shader.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Shader; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when this Shader is binded for rendering.
		/// </summary>
		virtual void on_bind() = 0;

		/// <summary>
		/// Registers a Material to this Shader.
		/// </summary>
		/// <param name="material">The Material.</param>
		void register_material(Material* const material);

		/// <summary>
		/// Unregisters a Material from this Shader.
		/// </summary>
		/// <param name="material">The Material.</param>
		void unregister_material(Material* const material);

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Shader.
		/// </summary>
		/// <param name="info">The arguments.</param>
		/// <returns>A Shader Owner.</returns>
		static Owner<Shader> create(ShaderInfo const& info = {});

#pragma endregion
	};
}