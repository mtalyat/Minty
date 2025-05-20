#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Set.h"
#include "Minty/Render/ShaderCullMode.h"
#include "Minty/Render/ShaderFrontFace.h"
#include "Minty/Render/ShaderInput.h"
#include "Minty/Render/ShaderPolygonMode.h"
#include "Minty/Render/ShaderPrimitiveTopology.h"
#include "Minty/Render/ShaderVertexInput.h"

namespace Minty
{
	class Material;
	class RenderPass;
	class ShaderModule;
	class Viewport;

	/// <summary>
	/// The arguments for a Shader.
	/// </summary>
	struct ShaderBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

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
		// the render pass this Shader belongs to
		Ref<RenderPass> m_renderPass;
		// list of inputs to the shader (for verification when setting values)
		Map<String, ShaderInput> m_inputs;
		// list of materials that use this shader (for global updates)
		Set<Material*> m_materials;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates 
		/// </summary>
		/// <param name="builder"></param>
		Shader(ShaderBuilder const& builder);

		virtual ~Shader() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:
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
			MINTY_ASSERT(m_inputs.contains(name), "Shader does not contain input with name: " + name);
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
		/// <param name="builder">The arguments.</param>
		/// <returns>A Shader Owner.</returns>
		static Owner<Shader> create(ShaderBuilder const& builder = {});

#pragma endregion
	};
}