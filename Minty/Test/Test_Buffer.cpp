#include "Test_Buffer.h"
#include "Minty.h"

void test_Buffer(Test& _test)
{
	CATEGORY(Buffer)
	{
		ContextBuilder contextBuilder{};
		contextBuilder.debugLogPath = "log.txt";
		RenderManagerBuilder renderManagerBuilder{};

		Owner<Window> window = Window::create({}); 
		renderManagerBuilder.window = window;
		contextBuilder.renderManagerBuilder = &renderManagerBuilder;

		JobManagerBuilder jobManagerBuilder{};
		contextBuilder.jobManagerBuilder = &jobManagerBuilder;

		Context context(contextBuilder);

		TEST("Constructor/Create")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = false;
			builder.size = 0;
			builder.usage = BufferUsage::Undefined;
			EXPECT_FAILURE(Buffer::create(builder)); // zero size, usage, etc.
			builder.size = 100;
			EXPECT_FAILURE(Buffer::create(builder)); // no usage
			builder.size = 0;
			builder.usage = BufferUsage::Vertex;
			EXPECT_FAILURE(Buffer::create(builder)); // no size
			Size value = 52;
			builder.size = sizeof(Size);
			builder.data = &value;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_EQUAL(buffer->get_size(), sizeof(Size));
			EXPECT_EQUAL(buffer->get_usage(), BufferUsage::Vertex);
			EXPECT_EQUAL(buffer->is_frequent(), false);
		}

		TEST("Get Data")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = false;
			builder.size = sizeof(Size);
			builder.usage = BufferUsage::Vertex;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_FAILURE(buffer->get_data());
			builder.frequent = true;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_NOT_EQUAL(buffer->get_data(), nullptr);
		}

		TEST("Set Data")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = true;
			builder.size = sizeof(Size);
			builder.usage = BufferUsage::Vertex;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_FAILURE(buffer->set_data(nullptr));
			Size value = 52;
			EXPECT_SUCCESS(buffer->set_data(&value));
			EXPECT_EQUAL(*static_cast<Size*>(buffer->get_data()), value);
		}

		TEST("Get Size")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = false;
			builder.size = sizeof(Size);
			builder.usage = BufferUsage::Vertex;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_EQUAL(buffer->get_size(), sizeof(Size));
			builder.size = KB;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_EQUAL(buffer->get_size(), KB);
		}

		TEST("Get Usage")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = false;
			builder.size = sizeof(Size);
			builder.usage = BufferUsage::Vertex;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_EQUAL(buffer->get_usage(), BufferUsage::Vertex);
			builder.usage = BufferUsage::Index;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_EQUAL(buffer->get_usage(), BufferUsage::Index);
		}

		TEST("Is Frequent")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = false;
			builder.size = sizeof(Size);
			builder.usage = BufferUsage::Vertex;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_FALSE(buffer->is_frequent());
			builder.frequent = true;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_TRUE(buffer->is_frequent());
		}

		TEST("Get Native")
		{
			BufferBuilder builder{};
			builder.data = nullptr;
			builder.frequent = false;
			builder.size = sizeof(Size);
			builder.usage = BufferUsage::Vertex;
			Owner<Buffer> buffer;
			EXPECT_SUCCESS(buffer = Buffer::create(builder));
			EXPECT_NOT_EQUAL(buffer->get_native(), nullptr);
		}
	}
}
