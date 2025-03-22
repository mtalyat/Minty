#include "Test_AssetManager.h"
#include "Minty.h"

void test_AssetManager(Test& _test)
{
	CATEGORY(AssetManager)
	{
		constexpr Char const* WRAP_PATH = "Assets/test.wrap";
		constexpr Char const* WRAP_ASSET_PATH = "Defaults/Texture/defaultTextureMint.png";
		constexpr Char const* ASSET_PATH = "Assets/text.txt";
		constexpr Char const* ASSET_PATH_MINTY = "Assets/minty.minty";
		constexpr Char const* DNE_PATH = "Assets/DNE.txt";
		constexpr Char const* TEST_PATH = "Assets/test.txt";

		TEST("Constructor")
		{
			AssetManagerBuilder builder;
			EXPECT_SUCCESS(AssetManager manager(builder));
		}

		TEST("Load Wrap")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			EXPECT_TRUE(manager.load_wrap(WRAP_PATH));
			EXPECT_FALSE(manager.load_wrap("Assets/DNE.wrap"));
			EXPECT_FALSE(manager.load_wrap("Assets/Game"));
			EXPECT_FALSE(manager.load_wrap(""));
		}

		TEST("Exists")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);

			EXPECT_TRUE(manager.exists(ASSET_PATH));
			EXPECT_FALSE(manager.exists(WRAP_ASSET_PATH));

			manager.load_wrap(WRAP_PATH);
			EXPECT_TRUE(manager.exists(ASSET_PATH));
			EXPECT_TRUE(manager.exists(WRAP_ASSET_PATH));
		}

		TEST("Open Reader")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Reader* reader = nullptr;
			EXPECT_TRUE(manager.open_reader(ASSET_PATH_MINTY, reader));
			EXPECT_NOT_EQUAL(reader, nullptr);
			EXPECT_TRUE(reader->indent("Object0"));
			manager.close_reader(reader);
			EXPECT_FALSE(manager.open_reader(DNE_PATH, reader));
			EXPECT_EQUAL(reader, nullptr);
		}

		TEST("Close Reader")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Reader* reader = nullptr;
			manager.open_reader(ASSET_PATH_MINTY, reader);
			EXPECT_NOT_EQUAL(reader, nullptr);
			manager.close_reader(reader);
			EXPECT_EQUAL(reader, nullptr);
			EXPECT_FAILURE(manager.close_reader(reader));
		}

		TEST("Open Writer")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Writer* writer = nullptr;
			EXPECT_TRUE(manager.open_writer(TEST_PATH, writer));
			EXPECT_NOT_EQUAL(writer, nullptr);
			writer->write("Hello", "World");
			manager.close_writer(writer);
			EXPECT_EQUAL(writer, nullptr);
			EXPECT_FAILURE(manager.close_writer(writer));
			EXPECT_FALSE(manager.open_writer("", writer));
			EXPECT_EQUAL(writer, nullptr);

			String text = File::read_text(TEST_PATH);
			EXPECT_EQUAL(text, "Hello: World\n");
		}

		TEST("Close Writer")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Writer* writer = nullptr;
			manager.open_writer(TEST_PATH, writer);
			EXPECT_NOT_EQUAL(writer, nullptr);
			manager.close_writer(writer);
			EXPECT_EQUAL(writer, nullptr);
			EXPECT_FAILURE(manager.close_writer(writer));
		}

		TEST("Contains")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			manager.load_wrap(WRAP_PATH);
			Ref<Text> textAsset = manager.load_now<Text>(ASSET_PATH);
			UUID id = parse_to<UUID>("0123456789abcdef");
			EXPECT_TRUE(manager.contains(id));
			EXPECT_FALSE(manager.contains(0));
			UUID badId = UUID::create();
			EXPECT_FALSE(manager.contains(badId));
		}
	}
}
