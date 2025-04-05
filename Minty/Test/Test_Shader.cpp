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

		}
	}
}
