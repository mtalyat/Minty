#include "Test_RenderManager.h"
#include "Minty.h"

void test_RenderManager(Test& _test)
{
	CATEGORY(RenderManager)
	{
		Owner<Window> window = Window::create({});

		TEST("Constructor")
		{
			RenderManagerBuilder builder{};
			builder.window = window;
			Owner<RenderManager> renderManager;
			EXPECT_SUCCESS(renderManager = RenderManager::create(builder));
			EXPECT_NOT_EQUAL(renderManager, nullptr);
		}

		TEST("Get Window")
		{
			RenderManagerBuilder builder{};
			builder.window = window;
			Owner<RenderManager> renderManager;
			EXPECT_SUCCESS(renderManager = RenderManager::create(builder));
			EXPECT_EQUAL(renderManager->get_window(), window);
		}

		TEST("Start Frame")
		{

		}

		TEST("End Frame")
		{

		}

		TEST("Create")
		{
			RenderManagerBuilder builder{};
			builder.window = window;
			Owner<RenderManager> renderManager;
			EXPECT_SUCCESS(renderManager = RenderManager::create(builder));
			EXPECT_NOT_EQUAL(renderManager, nullptr);
		}

		TEST("Get Singleton")
		{
			ContextBuilder contextBuilder{};
			contextBuilder.renderManagerBuilder.window = window;
			Context context(contextBuilder);
			Owner<RenderManager> renderManager;
			EXPECT_EQUAL(&RenderManager::get_singleton(), &context.get_render_manager());
		}
	}
}
