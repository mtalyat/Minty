#include "Test_Window.h"
#include "Minty.h"

void test_Window(Test& _test)
{
	CATEGORY(Window)
	{
		TEST("Constructor")
		{
			WindowBuilder builder;
			builder.id = UUID::create();
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_id(), builder.id);
			EXPECT_EQUAL(window->get_position(), builder.position);
			EXPECT_EQUAL(window->get_size(), builder.size);
			EXPECT_EQUAL(window->get_title(), builder.title);
		}

		TEST("Get ID")
		{
			WindowBuilder builder;
			builder.id = UUID::create();
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_id(), builder.id);
		}

		TEST("Get Title")
		{
			WindowBuilder builder;
			builder.title = "Test Window";
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_title(), builder.title);
		}

		TEST("Set Title")
		{
			WindowBuilder builder;
			builder.title = "Test Window";
			Owner<Window> window = Window::create(builder);
			window->set_title("New Title");
			EXPECT_EQUAL(window->get_title(), "New Title");
		}

		TEST("Get Position")
		{
			WindowBuilder builder;
			builder.position = { 100, 200 };
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_position(), builder.position);
		}

		TEST("Set Position")
		{
			WindowBuilder builder;
			builder.position = { 100, 200 };
			Owner<Window> window = Window::create(builder);
			window->set_position({ 300, 400 });
			EXPECT_EQUAL(window->get_position(), Int2(300, 400));
		}

		TEST("Get Size")
		{
			WindowBuilder builder;
			builder.size = { 800, 600 };
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_size(), builder.size);
		}

		TEST("Set Size")
		{
			WindowBuilder builder;
			builder.size = { 800, 600 };
			Owner<Window> window = Window::create(builder);
			window->set_size({ 1024, 768 });
			EXPECT_EQUAL(window->get_size(), UInt2(1024, 768));
		}

		TEST("Get Framebuffer Size")
		{
			WindowBuilder builder;
			builder.size = { 800, 600 };
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_framebuffer_size(), builder.size);
		}

		TEST("Get/Set Cursor Mode")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			window->set_cursor_mode(CursorMode::Disabled);
			EXPECT_EQUAL(window->get_cursor_mode(), CursorMode::Disabled);
			window->set_cursor_mode(CursorMode::Hidden);
			EXPECT_EQUAL(window->get_cursor_mode(), CursorMode::Hidden);
			window->set_cursor_mode(CursorMode::Normal);
			EXPECT_EQUAL(window->get_cursor_mode(), CursorMode::Normal);
		}

		TEST("Get Native")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			EXPECT_NOT_EQUAL(window->get_native(), nullptr);
		}

		TEST("Maximize")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			EXPECT_SUCCESS(window->maximize());
		}

		TEST("Minimize")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			EXPECT_SUCCESS(window->minimize());
		}

		TEST("Restore")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			EXPECT_SUCCESS(window->restore());
			window->minimize();
			EXPECT_SUCCESS(window->restore());
			window->maximize();
			EXPECT_SUCCESS(window->restore());
		}

		TEST("Close")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			EXPECT_SUCCESS(window->close());
			EXPECT_FALSE(window->is_open());
		}

		TEST("Is Open")
		{
			WindowBuilder builder;
			Owner<Window> window = Window::create(builder);
			EXPECT_TRUE(window->is_open());
			window->close();
			EXPECT_FALSE(window->is_open());
		}

		TEST("Process Events")
		{
			// TODO
		}

		TEST("Sync")
		{
			// TODO
		}

		TEST("Create")
		{
			WindowBuilder builder;
			builder.id = UUID::create();
			Owner<Window> window = Window::create(builder);
			EXPECT_EQUAL(window->get_id(), builder.id);
			EXPECT_EQUAL(window->get_position(), builder.position);
			EXPECT_EQUAL(window->get_size(), builder.size);
			EXPECT_EQUAL(window->get_title(), builder.title);
		}
	}
}
