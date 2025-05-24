#include "Test_ShaderModule.h"
#include "Minty.h"

void test_ShaderModule(Test& _test)
{
	static Char const* const VERT_MODULE_PATH = "Defaults/ShaderModule/defaultModule.vert.spv";
	static Char const* const FRAG_MODULE_PATH = "Defaults/ShaderModule/defaultModule.frag.spv";

	CATEGORY(ShaderModule)
	{
		Owner<Window> window = Window::create({});
		ContextBuilder contextBuilder{};
		contextBuilder.renderManagerBuilder.window = window;
		contextBuilder.assetManagerBuilder.wraps.add("Assets/test.wrap");
		Context context(contextBuilder);

		TEST("Constructor/Create")
		{
			ShaderModuleBuilder shaderModuleBuilder{};
			EXPECT_FAILURE(ShaderModule::create(shaderModuleBuilder));
			Size temp = 0;
			shaderModuleBuilder.data = &temp;
			EXPECT_FAILURE(ShaderModule::create(shaderModuleBuilder));
			shaderModuleBuilder.data = nullptr;
			shaderModuleBuilder.size = sizeof(Size);
			EXPECT_FAILURE(ShaderModule::create(shaderModuleBuilder));

			AssetManager& assetManager = context.get_asset_manager();
			Vector<Byte> bytes = assetManager.read_bytes(VERT_MODULE_PATH);
			shaderModuleBuilder.data = bytes.get_data();
			shaderModuleBuilder.size = bytes.get_size();
			Owner<ShaderModule> shaderModule = ShaderModule::create(shaderModuleBuilder);
			EXPECT_NOT_EQUAL(shaderModule, nullptr);
		}
	}
}
