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

		TEST("Constructor/Create")
		{
			//ShaderBuilder builder{};
			//EXPECT_FAILURE(Shader::create(builder));
			//builder.viewport = viewport;
			//builder.vertexShaderModule = vertexModule;
			//builder.fragmentShaderModule = fragmentModule;
			//EXPECT_SUCCESS(Shader::create(builder));
		}

		TEST("Get Render Pass")
		{

		}
	}
}
