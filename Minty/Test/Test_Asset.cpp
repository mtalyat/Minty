#include "Test_Asset.h"
#include "Minty.h"

void test_Asset(Test& _test)
{
	CATEGORY(Asset)
	{
		TEST("ID Constructor")
		{
			GenericAssetBuilder builder
			{
				.id = 0
			};
			GenericAsset asset(builder);
			EXPECT_EQUAL(asset.get_id().get_data(), 0);
			builder.id = 1;
			asset = GenericAsset(builder);
			EXPECT_EQUAL(asset.get_id().get_data(), 1);
			builder.id = 0xFFFFFFFFFFFFFFFF;
			asset = GenericAsset(builder);
			EXPECT_EQUAL(asset.get_id().get_data(), 0xFFFFFFFFFFFFFFFF);
		}

		TEST("Get ID")
		{
			GenericAssetBuilder builder
			{
				.id = 0
			};
			GenericAsset asset(builder);
			EXPECT_EQUAL(asset.get_id().get_data(), 0);
			builder.id = 1;
			asset = GenericAsset(builder);
			EXPECT_EQUAL(asset.get_id().get_data(), 1);
		}

		TEST("Get Asset Type Path")
		{
			Vector<Pair<Char const*, AssetType>> const EXTENSIONS =
			{
				{ EXTENSION_ANIMATION, AssetType::Animation },
				{ EXTENSION_ANIMATOR, AssetType::Animator },
				{ EXTENSION_AUDIO_CLIP_WAV, AssetType::AudioClip },
				{ EXTENSION_AUDIO_CLIP_MP3, AssetType::AudioClip },
				{ EXTENSION_BITMAP, AssetType::Image },
				{ EXTENSION_FONT, AssetType::Font },
				{ EXTENSION_FONT_VARIANT, AssetType::FontVariant },
				{ EXTENSION_JPEG, AssetType::Image },
				{ EXTENSION_JPG, AssetType::Image },
				{ EXTENSION_MATERIAL, AssetType::Material},
				{ EXTENSION_MATERIAL_TEMPLATE, AssetType::MaterialTemplate},
				{ EXTENSION_MESH_OBJECT, AssetType::Mesh},
				{ EXTENSION_PNG, AssetType::Image },
				{ EXTENSION_SCENE, AssetType::Scene },
				{ EXTENSION_SCRIPT, AssetType::Script },
				{ EXTENSION_SHADER, AssetType::Shader },
				{ EXTENSION_SHADER_CODE, AssetType::ShaderCode },
				{ EXTENSION_SHADER_CODE_FRAGMENT, AssetType::ShaderCode },
				{ EXTENSION_SHADER_CODE_VERTEX, AssetType::ShaderCode },
				{ EXTENSION_SHADER_MODULE, AssetType::ShaderModule },
				{ EXTENSION_SPRITE, AssetType::Sprite },
				{ EXTENSION_WRAP, AssetType::Wrap },
			};

			for (auto const& [extension, expected] : EXTENSIONS)
			{
				String pathStr = String("test").append(extension);
				Path path = pathStr.get_data();
				AssetType actual = Asset::get_asset_type(path);
				EXPECT_EQUAL(actual, expected);
			}
		}

		TEST("Get Asset Type TypeID")
		{
			Path path = "test.txt";
			EXPECT_EQUAL(Asset::get_asset_type(path), AssetType::Generic);
			path = "";
			EXPECT_FAILURE(Asset::get_asset_type(path));
		}

		TEST("Get Meta Path")
		{
			Path path = "test.png";
			EXPECT_EQUAL(Asset::get_meta_path(path), "test.png.meta");
			path = "";
			EXPECT_FAILURE(Asset::get_meta_path(path));
		}
	}
}
