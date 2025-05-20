#include "Test_Scene.h"
#include "Minty.h"

void test_Scene(Test& _test)
{
	CATEGORY(Scene)
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

		Debug::set_flags(DebugFlags::All);

		TEST("Constructor/Create")
		{
			Ref<Scene> scene = context.get_asset_manager().load<Scene>("Assets/minty.msce");

			EXPECT_EQUAL(scene->get_name(), "minty");
			UUID id("ee7ea0f3b2ed868f");
			EXPECT_EQUAL(scene->get_id(), id);
			EntityManager& entityManager = scene->get_entity_manager();
			EXPECT_EQUAL(entityManager.get_size(), 2);

			UUID cameraId("6e2c8e09c099405c");
			EXPECT_TRUE(entityManager.contains(cameraId));
			UUID cubeId("99606238de99041e");
			EXPECT_TRUE(entityManager.contains(cubeId));
		}

		Debug::set_flags(DebugFlags::Default);
	}
}
