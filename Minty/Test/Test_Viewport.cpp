#include "Test_Viewport.h"
#include "Minty.h"

void test_Viewport(Test& _test)
{
	CATEGORY(Viewport)
	{
		TEST("Constructor/Create")
		{
			ViewportBuilder builder{};
			EXPECT_SUCCESS(Viewport::create(builder));
		}

		TEST("Set Position")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			Int2 value = Int2(-1, -1);
			EXPECT_SUCCESS(viewport->set_position(value));
			EXPECT_EQUAL(viewport->get_view_position(), value);
			EXPECT_EQUAL(viewport->get_mask_position(), value);
			value = Int2(0, 0);
			EXPECT_SUCCESS(viewport->set_position(value));
			EXPECT_EQUAL(viewport->get_view_position(), value);
			EXPECT_EQUAL(viewport->get_mask_position(), value);
			value = Int2(1, 1);
			EXPECT_SUCCESS(viewport->set_position(value));
			EXPECT_EQUAL(viewport->get_view_position(), value);
			EXPECT_EQUAL(viewport->get_mask_position(), value);
		}

		TEST("Set Size")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			UInt2 value = UInt2(0, 0);
			EXPECT_SUCCESS(viewport->set_size(value));
			EXPECT_EQUAL(viewport->get_view_size(), value);
			EXPECT_EQUAL(viewport->get_mask_size(), value);
			value = UInt2(1, 1);
			EXPECT_SUCCESS(viewport->set_size(value));
			EXPECT_EQUAL(viewport->get_view_size(), value);
			EXPECT_EQUAL(viewport->get_mask_size(), value);
		}

		TEST("Get/Set View Position")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			Int2 value = Int2(123, 123);
			EXPECT_SUCCESS(viewport->set_view_position(value));
			EXPECT_EQUAL(viewport->get_view_position(), value);
		}

		TEST("Get/Set View Size")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			UInt2 value = UInt2(123, 123);
			EXPECT_SUCCESS(viewport->set_view_size(value));
			EXPECT_EQUAL(viewport->get_view_size(), value);
		}

		TEST("Get/Set Mask Position")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			Int2 value = Int2(123, 123);
			EXPECT_SUCCESS(viewport->set_mask_position(value));
			EXPECT_EQUAL(viewport->get_mask_position(), value);
		}

		TEST("Get/Set Mask Size")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			UInt2 value = UInt2(123, 123);
			EXPECT_SUCCESS(viewport->set_mask_size(value));
			EXPECT_EQUAL(viewport->get_mask_size(), value);
		}

		TEST("Get Asset Type")
		{
			ViewportBuilder builder{};
			Owner<Viewport> viewport = Viewport::create(builder);
			EXPECT_EQUAL(viewport->get_asset_type(), AssetType::Viewport);
		}
	}
}
