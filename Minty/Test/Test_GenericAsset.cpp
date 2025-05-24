#include "Test_GenericAsset.h"
#include "Minty.h"

void test_GenericAsset(Test& _test)
{
	CATEGORY(GenericAsset)
	{
		TEST("Constructor")
		{
			{
				GenericAssetBuilder builder{};
				GenericAsset asset(builder);
				EXPECT_EQUAL(asset.get_id().get_data(), 0);
				EXPECT_EQUAL(asset.get_data().get_size(), 0);
				EXPECT_EQUAL(asset.get_asset_type(), AssetType::Generic);
			}
			{
				GenericAssetBuilder builder
				{
					.id = 1,
					.data = ConstantContainer("Hello, World!", 13)
				};
				GenericAsset asset(builder);
				EXPECT_EQUAL(asset.get_id().get_data(), 1);
				EXPECT_EQUAL(asset.get_data().get_size(), 13);
				EXPECT_EQUAL(asset.get_asset_type(), AssetType::Generic);
			}
		}

		TEST("Get Data")
		{
			GenericAssetBuilder builder
			{
				.data = ConstantContainer("Hello, World!", 13)
			};
			GenericAsset asset(builder);
			EXPECT_EQUAL(asset.get_data().get_size(), 13);
		}

		TEST("Get Data Const")
		{
			GenericAssetBuilder builder
			{
				.data = ConstantContainer("Hello, World!", 13)
			};
			GenericAsset const asset(builder);
			EXPECT_EQUAL(asset.get_data().get_size(), 13);
		}

		TEST("Get Text")
		{
			GenericAssetBuilder builder
			{
				.data = ConstantContainer("Hello, World!", 13)
			};
			GenericAsset asset(builder);
			EXPECT_EQUAL(asset.get_text(), "Hello, World!");
		}

		TEST("Get Asset Type")
		{
			GenericAssetBuilder builder{};
			GenericAsset asset(builder);
			EXPECT_EQUAL(asset.get_asset_type(), AssetType::Generic);
		}

		TEST("Create")
		{
			{
				GenericAssetBuilder builder{};
				Owner<GenericAsset> asset = GenericAsset::create(builder);
				EXPECT_EQUAL(asset->get_id().get_data(), 0);
				EXPECT_EQUAL(asset->get_data().get_size(), 0);
				EXPECT_EQUAL(asset->get_asset_type(), AssetType::Generic);
			}
			{
				GenericAssetBuilder builder
				{
					.id = 1,
					.data = ConstantContainer("Hello, World!", 13)
				};
				Owner<GenericAsset> asset = GenericAsset::create(builder);
				EXPECT_EQUAL(asset->get_id().get_data(), 1);
				EXPECT_EQUAL(asset->get_data().get_size(), 13);
				EXPECT_EQUAL(asset->get_asset_type(), AssetType::Generic);
			}
		}
	}
}
