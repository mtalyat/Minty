#include "Test_Image.h"
#include "Minty.h"

void test_Image(Test& _test)
{
	CATEGORY(Image)
	{
		Owner<Window> window = Window::create({});
		ContextBuilder contextBuilder{};
		contextBuilder.renderManagerBuilder.window = window;
		Context context(contextBuilder);

		TEST("Constructor/Create")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			EXPECT_SUCCESS(Image::create(builder));
			builder.size = { 0, 0 };
			EXPECT_FAILURE(Image::create(builder));
			builder.size = { 128, 128 };
			builder.format = Format::Undefined;
			EXPECT_FAILURE(Image::create(builder));
			builder.format = Format::Default;
			builder.type = ImageType::Undefined;
			EXPECT_FAILURE(Image::create(builder));
			builder.type = ImageType::D2;
			builder.tiling = ImageTiling::Undefined;
			EXPECT_FAILURE(Image::create(builder));
			builder.tiling = ImageTiling::Optimal;
			builder.aspect = ImageAspect::Undefined;
			EXPECT_FAILURE(Image::create(builder));
			builder.aspect = ImageAspect::Color;
			builder.usage = ImageUsage::Undefined;
			EXPECT_FAILURE(Image::create(builder));
			builder.usage = ImageUsage::Sampled;
		}

		TEST("Set Pixels")
		{
			// TODO
			EXPECT_TRUE(true);
		}

		TEST("Get Format")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_format(), Format::Default);
			builder.format = Format::R8G8B8A8_UINT;
			image = Image::create(builder);
			EXPECT_EQUAL(image->get_format(), Format::R8G8B8A8_UINT);
		}

		TEST("Get Type")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_type(), ImageType::D2);
			builder.type = ImageType::D1;
			image = Image::create(builder);
			EXPECT_EQUAL(image->get_type(), ImageType::D1);
		}

		TEST("Get Tiling")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_tiling(), ImageTiling::Optimal);
			builder.tiling = ImageTiling::Linear;
			image = Image::create(builder);
			EXPECT_EQUAL(image->get_tiling(), ImageTiling::Linear);
		}

		TEST("Get Aspect")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_aspect(), ImageAspect::Color);
			builder.aspect = ImageAspect::Depth;
			image = Image::create(builder);
			EXPECT_EQUAL(image->get_aspect(), ImageAspect::Depth);
		}

		TEST("Get Usage")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_usage(), ImageUsage::Sampled);
			builder.usage = ImageUsage::Storage;
			image = Image::create(builder);
			EXPECT_EQUAL(image->get_usage(), ImageUsage::Storage);
		}

		TEST("Get Size")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_size(), UInt2(128, 128));
			builder.size = { 256, 256 };
			image = Image::create(builder);
			EXPECT_EQUAL(image->get_size(), UInt2(256, 256));
		}

		TEST("Is Immutable")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->is_immutable(), false);
			builder.immutable = true;
			image = Image::create(builder);
			EXPECT_EQUAL(image->is_immutable(), true);
		}

		TEST("Get Native")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_NOT_EQUAL(image->get_native(), nullptr);
		}

		TEST("Get Asset Type")
		{
			ImageBuilder builder{};
			builder.size = { 128, 128 };
			auto image = Image::create(builder);
			EXPECT_EQUAL(image->get_asset_type(), AssetType::Image);
		}
	}
}
