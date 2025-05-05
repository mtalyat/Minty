#include "Test_MaterialTemplate.h"
#include "Minty.h"

void test_MaterialTemplate(Test& _test)
{
	CATEGORY(MaterialTemplate)
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
		Ref<Shader> const& shader = assetManager.load<Shader>("Defaults/Shader/defaultShader.msha");

		TEST("Constructor/Create")
		{
			MaterialTemplateBuilder builder{};
			EXPECT_FAILURE(MaterialTemplate::create(builder));
			builder.shader = shader;
			EXPECT_SUCCESS(MaterialTemplate::create(builder));
			builder.values.add("xxx", Object());
			EXPECT_FAILURE(MaterialTemplate::create(builder));
			builder.values.remove("xxx");
			builder.values.add("camera", Object());
			EXPECT_SUCCESS(MaterialTemplate::create(builder));
		}

		TEST("Get Shader")
		{
			MaterialTemplateBuilder builder{};
			builder.shader = shader;
			Owner<MaterialTemplate> materialTemplate = MaterialTemplate::create(builder);
			EXPECT_EQUAL(shader, materialTemplate->get_shader());
		}

		TEST("Get Values")
		{
			MaterialTemplateBuilder builder{};
			builder.shader = shader;
			builder.values.add("camera", Object());
			Owner<MaterialTemplate> materialTemplate = MaterialTemplate::create(builder);
			EXPECT_EQUAL(materialTemplate->get_inputs().get_size(), 1);
			EXPECT_TRUE(materialTemplate->get_inputs().contains("camera"));
			EXPECT_FALSE(materialTemplate->get_inputs().contains("xxx"));
		}

		TEST("Get Asset Type")
		{
			MaterialTemplateBuilder builder{};
			builder.shader = shader;
			Owner<MaterialTemplate> materialTemplate = MaterialTemplate::create(builder);
			EXPECT_EQUAL(materialTemplate->get_asset_type(), AssetType::MaterialTemplate);
		}
	}
}
