#include "Test_AssetManager.h"
#include "Minty.h"

void test_AssetManager(Test& _test)
{
	CATEGORY(AssetManager)
	{
		constexpr Char const* WRAP_PATH = "Assets/test.wrap";
		constexpr Char const* WRAP_ASSET_PATH = "Defaults/Texture/defaultTextureMint.png";
		constexpr Char const* ASSET_PATH = "Assets/text.txt";
		constexpr Char const* ASSET_PATH_MINTY = "Assets/minty.txt";
		constexpr Char const* DNE_PATH = "Assets/DNE.txt";
		constexpr Char const* TEST_PATH = "Assets/test.txt";

		ContextBuilder builder{};
		Context context(builder);

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

		TEST("Schedule Load")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			UUID id = manager.schedule_load(ASSET_PATH);
			EXPECT_SUCCESS(manager.sync());
			EXPECT_TRUE(manager.contains(id));
			EXPECT_SUCCESS(manager.sync());
		}

		TEST("Load Asset")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Asset> asset = manager.load_asset(ASSET_PATH);
			EXPECT_NOT_EQUAL(asset, nullptr);
			EXPECT_TRUE(manager.contains(asset->get_id()));
			EXPECT_EQUAL(asset->get_id(), parse_to<UUID>("0123456789abcdef"));
			EXPECT_FAILURE(manager.load_asset(DNE_PATH));
			EXPECT_FAILURE(manager.load_asset(TEST_PATH));
			EXPECT_FAILURE(manager.load_asset(ASSET_PATH));
		}

		TEST("Load")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			EXPECT_NOT_EQUAL(textAsset, nullptr);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			EXPECT_EQUAL(textAsset->get_id(), parse_to<UUID>("0123456789abcdef"));
			EXPECT_FAILURE(manager.load<Text>(DNE_PATH));
			EXPECT_FAILURE(manager.load<Text>(TEST_PATH));
			EXPECT_FAILURE(manager.load<Text>(ASSET_PATH));
		}

		TEST("Schedule Unload")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			manager.schedule_unload(id);
			manager.sync();
			EXPECT_FALSE(manager.contains(id));
			EXPECT_EQUAL(textAsset, nullptr);
		}

		TEST("Unload")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			manager.unload(id);
			EXPECT_FALSE(manager.contains(id));
			EXPECT_EQUAL(textAsset, nullptr);
		}

		TEST("Unload All")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID textAssetId = textAsset->get_id();
			Ref<Text> mintyAsset = manager.load<Text>(ASSET_PATH_MINTY);
			UUID mintyAssetId = mintyAsset->get_id();
			manager.unload_all();
			EXPECT_FALSE(manager.contains(textAssetId));
			EXPECT_FALSE(manager.contains(mintyAssetId));
			EXPECT_EQUAL(textAsset, nullptr);
			EXPECT_EQUAL(mintyAsset, nullptr);
		}

		TEST("Sync")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			UUID id = manager.schedule_load(ASSET_PATH);
			EXPECT_FALSE(manager.contains(id));
			manager.sync();
			EXPECT_TRUE(manager.contains(id));
			manager.schedule_unload(id);
			EXPECT_TRUE(manager.contains(id));
			manager.sync();
			EXPECT_FALSE(manager.contains(id));
		}

		TEST("Is Syncing")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			EXPECT_FALSE(manager.is_syncing());
			UUID id = manager.schedule_load(ASSET_PATH);
			EXPECT_TRUE(manager.is_syncing());
			manager.sync();
			EXPECT_FALSE(manager.is_syncing());
		}

		TEST("Create")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			TextBuilder textBuilder;
			textBuilder.id = UUID::create();
			textBuilder.text = "Hello world!";
			Ref<Text> textAsset = manager.create<Text>(textBuilder);
			EXPECT_NOT_EQUAL(textAsset, nullptr);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
		}

		TEST("Add")
		{
			AssetManagerBuilder builder;
			builder.savePaths = true;
			AssetManager manager(builder);
			TextBuilder textBuilder;
			textBuilder.id = UUID::create();
			textBuilder.text = "Hello world!";
			Owner<Text> textAsset = Text::create(textBuilder);
			EXPECT_FALSE(manager.contains(textAsset->get_id()));
			manager.add(textAsset);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), "");
		}

		TEST("Add Path")
		{
			AssetManagerBuilder builder;
			builder.savePaths = true;
			AssetManager manager(builder);
			TextBuilder textBuilder;
			textBuilder.id = UUID::create();
			textBuilder.text = "Hello world!";
			Owner<Text> textAsset = Text::create(textBuilder);
			EXPECT_FALSE(manager.contains(textAsset->get_id()));
			manager.add(ASSET_PATH, textAsset);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), ASSET_PATH);
		}

		TEST("Contains")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			manager.load_wrap(WRAP_PATH);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = parse_to<UUID>("0123456789abcdef");
			EXPECT_TRUE(manager.contains(id));
			EXPECT_FALSE(manager.contains(0));
			UUID badId = UUID::create();
			EXPECT_FALSE(manager.contains(badId));
		}

		TEST("Get Asset")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			manager.load_wrap(WRAP_PATH);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.get_asset(id), textAsset);
			EXPECT_EQUAL(manager.get_asset(0), nullptr);
			UUID badId = UUID::create();
			EXPECT_EQUAL(manager.get_asset(badId), nullptr);
		}

		TEST("Get")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			manager.load_wrap(WRAP_PATH);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.get<Text>(id), textAsset);
			EXPECT_EQUAL(manager.get<Text>(0), nullptr);
			UUID badId = UUID::create();
			EXPECT_EQUAL(manager.get<Text>(badId), nullptr);
		}

		TEST("At Asset")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			manager.load_wrap(WRAP_PATH);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.at_asset(id), textAsset);
			EXPECT_FAILURE(manager.at_asset(0));
			UUID badId = UUID::create();
			EXPECT_FAILURE(manager.at_asset(badId));
		}

		TEST("At")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			manager.load_wrap(WRAP_PATH);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.at<Text>(id), textAsset);
			EXPECT_FAILURE(manager.at<Text>(0));
			UUID badId = UUID::create();
			EXPECT_FAILURE(manager.at<Text>(badId));
		}

		TEST("Get By Type")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			Ref<Text> mintyAsset = manager.load<Text>(ASSET_PATH_MINTY);
			Vector<Ref<Text>> texts = manager.get_by_type<Text>();
			EXPECT_EQUAL(texts.get_size(), 2);
		}

		TEST("Get Asset Path")
		{
			{
				AssetManagerBuilder builder;
				builder.savePaths = true;
				AssetManager manager(builder);
				Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), ASSET_PATH);
			}
			{

				AssetManagerBuilder builder;
				builder.savePaths = false;
				AssetManager manager(builder);
				Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), "");
			}
		}

		TEST("Get Asset Name")
		{
			{
				AssetManagerBuilder builder;
				builder.savePaths = true;
				AssetManager manager(builder);
				Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_name(textAsset->get_id()), "text");
			}
			{
				AssetManagerBuilder builder;
				builder.savePaths = false;
				AssetManager manager(builder);
				Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_name(textAsset->get_id()), "");
			}
		}

		TEST("Remove")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Ref<Text> textAsset = manager.load<Text>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_TRUE(manager.contains(id));
			Owner<Text> removedAsset = manager.remove(id);
			EXPECT_EQUAL(removedAsset, textAsset);
			EXPECT_FALSE(manager.contains(id));
			removedAsset.release();
			EXPECT_EQUAL(textAsset, nullptr);
		}

		TEST("Clone")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			TextBuilder textBuilder;
			textBuilder.id = UUID::create();
			textBuilder.text = "Hello world!";
			Ref<Text> textAsset = manager.create<Text>(textBuilder);
			Ref<Text> clonedAsset = manager.clone<Text>(textAsset->get_id());
			EXPECT_NOT_EQUAL(clonedAsset, nullptr);
			EXPECT_NOT_EQUAL(clonedAsset, textAsset);
			EXPECT_NOT_EQUAL(clonedAsset->get_id(), textAsset->get_id());
			EXPECT_EQUAL(clonedAsset->get_text(), textAsset->get_text());
		}

		TEST("Get Dependents")
		{
			// TODO
			EXPECT_TRUE(true);
		}

		TEST("Read Text")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			String text = manager.read_text(ASSET_PATH);
			EXPECT_TRUE(text.starts_with("Lorem"));
		}

		TEST("Read Lines")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Vector<String> lines = manager.read_lines(ASSET_PATH);
			EXPECT_EQUAL(lines.get_size(), 5);
			EXPECT_TRUE(lines[0].starts_with("Lorem"));
			EXPECT_TRUE(lines[1].starts_with("Aliquam"));
			EXPECT_TRUE(lines[2].starts_with("Aenean"));
			EXPECT_TRUE(lines[3].starts_with("Quisque id"));
			EXPECT_TRUE(lines[4].starts_with("Quisque lacinia"));
		}

		TEST("Read Bytes")
		{
			AssetManagerBuilder builder;
			AssetManager manager(builder);
			Vector<Byte> bytes = manager.read_bytes(ASSET_PATH);
			EXPECT_EQUAL(bytes.get_size(), 2948);
		}
	}
}
