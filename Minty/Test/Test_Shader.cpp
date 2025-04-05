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

		TEST("Constructor/Create")
		{
			// load stuff
			RenderManager& renderManager = context.get_render_manager();
			Ref<Viewport> const& viewport = renderManager.get_default_viewport();

			ShaderBuilder builder{};
			EXPECT_FAILURE(Shader::create(builder));
		}
	}
}
