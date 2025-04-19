#include "Test_Shader.h"
#include "Minty.h"

void test_Shader(Test& _test)
{
	CATEGORY(Shader)
	{
		Owner<Window> window = Window::create({});
		ContextBuilder contextBuilder{};
		contextBuilder.renderManagerBuilder.window = window;
		contextBuilder.assetManagerBuilder.wraps.add("Assets/test.wrap");
		Context context(contextBuilder);

		// load stuff
		RenderManager& renderManager = context.get_render_manager();
		AssetManager& assetManager = context.get_asset_manager();
		Ref<Viewport> const& viewport = renderManager.get_default_viewport();
		Ref<ShaderModule> const& vertexModule = assetManager.load<ShaderModule>("Defaults/ShaderModule/defaultModule.vert.spv");
		Ref<ShaderModule> const& fragmentModule = assetManager.load<ShaderModule>("Defaults/ShaderModule/defaultModule.frag.spv");
		Ref<RenderPass> const& renderPass = assetManager.load<RenderPass>("Defaults/RenderPass/defaultRenderPass.mrpa");

		TEST("Constructor/Create")
		{
			ShaderBuilder builder{};
			EXPECT_FAILURE(Shader::create(builder));
			builder.viewport = viewport;
			EXPECT_FAILURE(Shader::create(builder));
			builder.viewport = nullptr;
			builder.vertexShaderModule = vertexModule;
			EXPECT_FAILURE(Shader::create(builder));
			builder.vertexShaderModule = nullptr;
			builder.fragmentShaderModule = fragmentModule;
			EXPECT_FAILURE(Shader::create(builder));
			builder.fragmentShaderModule = nullptr;
			builder.renderPass = renderPass;
			EXPECT_FAILURE(Shader::create(builder));
			builder.renderPass = nullptr;
			builder.viewport = viewport;
			builder.vertexShaderModule = vertexModule;
			builder.fragmentShaderModule = fragmentModule;
			builder.renderPass = renderPass;
			EXPECT_SUCCESS(Shader::create(builder));
		}

		TEST("Get Render Pass")
		{
			ShaderBuilder builder{};
			builder.viewport = viewport;
			builder.vertexShaderModule = vertexModule;
			builder.fragmentShaderModule = fragmentModule;
			builder.renderPass = renderPass;
			Owner<Shader> shader = Shader::create(builder);

			EXPECT_EQUAL(renderPass, shader->get_render_pass());
		}

		TEST("Contains Input")
		{
			Ref<Shader> shader = assetManager.load<Shader>("Defaults/Shader/defaultShader.msha");

			EXPECT_TRUE(shader->contains_input("object"));
			EXPECT_TRUE(shader->contains_input("camera"));
			EXPECT_TRUE(shader->contains_input("texture"));
			EXPECT_FALSE(shader->contains_input(""));
			EXPECT_FALSE(shader->contains_input("nonexistent"));

			assetManager.unload(shader->get_id());
		}
		
		TEST("Get Input")
		{
			Ref<Shader> shader = assetManager.load<Shader>("Defaults/Shader/defaultShader.msha");

			EXPECT_EQUAL(shader->get_input("object").type, ShaderInputType::PushConstant);
			EXPECT_EQUAL(shader->get_input("camera").type, ShaderInputType::UniformBuffer);
			EXPECT_EQUAL(shader->get_input("texture").type, ShaderInputType::CombinedImageSampler);

			assetManager.unload(shader->get_id());
		}

		TEST("Get Inputs")
		{
			Ref<Shader> shader = assetManager.load<Shader>("Defaults/Shader/defaultShader.msha");

			auto const& inputs = shader->get_inputs();
			EXPECT_EQUAL(inputs.get_size(), 3);
			EXPECT_EQUAL(inputs["object"].type, ShaderInputType::PushConstant);
			EXPECT_EQUAL(inputs["camera"].type, ShaderInputType::UniformBuffer);
			EXPECT_EQUAL(inputs["texture"].type, ShaderInputType::CombinedImageSampler);

			assetManager.unload(shader->get_id());
		}

		TEST("Set Global Input")
		{
			Ref<Shader> shader = assetManager.load<Shader>("Defaults/Shader/defaultShader.msha");

			// create material to be set globally
			Ref<MaterialTemplate> materialTemplate = assetManager.load<MaterialTemplate>("Defaults/MaterialTemplate/defaultMaterialTemplate.mmtp");
			Ref<Material> material = assetManager.load<Material>("Defaults/Material/defaultMaterial.mmat");
			
			// set global input
			Matrix4 cameraMatrix = Math::identity<Matrix4>();
			EXPECT_FAILURE(shader->set_global_input("", nullptr, 0));
			EXPECT_FAILURE(shader->set_global_input("", &cameraMatrix, sizeof(Matrix4)));
			EXPECT_FAILURE(shader->set_global_input("camera", nullptr, sizeof(Matrix4)));
			EXPECT_FAILURE(shader->set_global_input("camera", &cameraMatrix, 0));
			EXPECT_FAILURE(shader->set_global_input("camera", &cameraMatrix, sizeof(Matrix4) * 2));
			EXPECT_SUCCESS(shader->set_global_input("camera", &cameraMatrix, sizeof(Matrix4)));

			assetManager.unload(shader->get_id());
		}
	}
}
