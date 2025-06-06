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

		Owner<Window> window = Window::create({});
		ContextBuilder builder{};
		builder.renderManagerBuilder.window = window;
		Context context(builder);

		TEST("Constructor")
		{
			AssetManagerBuilder builder{};
			EXPECT_SUCCESS(AssetManager manager(builder));
		}

		TEST("Load Wrap")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			EXPECT_TRUE(manager.load_wrap(WRAP_PATH));
			EXPECT_FALSE(manager.load_wrap("Assets/DNE.wrap"));
			EXPECT_FALSE(manager.load_wrap("Assets/Game"));
			EXPECT_FALSE(manager.load_wrap(""));
			manager.dispose();
		}

		TEST("Exists")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();

			EXPECT_TRUE(manager.exists(ASSET_PATH));
			EXPECT_FALSE(manager.exists(WRAP_ASSET_PATH));

			manager.load_wrap(WRAP_PATH);
			EXPECT_TRUE(manager.exists(ASSET_PATH));
			EXPECT_TRUE(manager.exists(WRAP_ASSET_PATH));
			manager.dispose();
		}

		TEST("Open Reader")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Reader* reader = nullptr;
			EXPECT_TRUE(manager.open_reader(ASSET_PATH_MINTY, reader));
			EXPECT_NOT_EQUAL(reader, nullptr);
			EXPECT_TRUE(reader->indent("Object0"));
			manager.close_reader(reader);
			EXPECT_FALSE(manager.open_reader(DNE_PATH, reader));
			EXPECT_EQUAL(reader, nullptr);
			manager.dispose();
		}

		TEST("Close Reader")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Reader* reader = nullptr;
			manager.open_reader(ASSET_PATH_MINTY, reader);
			EXPECT_NOT_EQUAL(reader, nullptr);
			manager.close_reader(reader);
			EXPECT_EQUAL(reader, nullptr);
			EXPECT_FAILURE(manager.close_reader(reader));
			manager.dispose();
		}

		TEST("Open Writer")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
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
			manager.dispose();
		}

		TEST("Close Writer")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Writer* writer = nullptr;
			manager.open_writer(TEST_PATH, writer);
			EXPECT_NOT_EQUAL(writer, nullptr);
			manager.close_writer(writer);
			EXPECT_EQUAL(writer, nullptr);
			EXPECT_FAILURE(manager.close_writer(writer));
			manager.dispose();
		}

		TEST("Schedule Load")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			UUID id = manager.schedule_load(ASSET_PATH);
			EXPECT_SUCCESS(manager.sync());
			EXPECT_TRUE(manager.contains(id));
			EXPECT_SUCCESS(manager.sync());
			manager.dispose();
		}

		TEST("Load Asset")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<Asset> asset = manager.load_asset(ASSET_PATH);
			EXPECT_NOT_EQUAL(asset, nullptr);
			EXPECT_TRUE(manager.contains(asset->get_id()));
			EXPECT_EQUAL(asset->get_id(), parse_to<UUID>("0123456789abcdef"));
			EXPECT_FAILURE(manager.load_asset(DNE_PATH));
			EXPECT_FAILURE(manager.load_asset(TEST_PATH));
			EXPECT_FAILURE(manager.load_asset(ASSET_PATH));
			manager.dispose();
		}

		TEST("Load")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			EXPECT_NOT_EQUAL(textAsset, nullptr);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			EXPECT_EQUAL(textAsset->get_id(), parse_to<UUID>("0123456789abcdef"));
			EXPECT_FAILURE(manager.load<GenericAsset>(DNE_PATH));
			EXPECT_FAILURE(manager.load<GenericAsset>(TEST_PATH));
			EXPECT_FAILURE(manager.load<GenericAsset>(ASSET_PATH));
			manager.dispose();
		}

		TEST("Schedule Unload")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			manager.schedule_unload(id);
			manager.sync();
			EXPECT_FALSE(manager.contains(id));
			EXPECT_EQUAL(textAsset, nullptr);
			manager.dispose();
		}

		TEST("Unload")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			manager.unload(id);
			EXPECT_FALSE(manager.contains(id));
			EXPECT_EQUAL(textAsset, nullptr);
			manager.dispose();
		}

		TEST("Unload All")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID textAssetId = textAsset->get_id();
			Ref<GenericAsset> mintyAsset = manager.load<GenericAsset>(ASSET_PATH_MINTY);
			UUID mintyAssetId = mintyAsset->get_id();
			manager.unload_all();
			EXPECT_FALSE(manager.contains(textAssetId));
			EXPECT_FALSE(manager.contains(mintyAssetId));
			EXPECT_EQUAL(textAsset, nullptr);
			EXPECT_EQUAL(mintyAsset, nullptr);
			manager.dispose();
		}

		TEST("Sync")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			UUID id = manager.schedule_load(ASSET_PATH);
			EXPECT_FALSE(manager.contains(id));
			manager.sync();
			EXPECT_TRUE(manager.contains(id));
			manager.schedule_unload(id);
			EXPECT_TRUE(manager.contains(id));
			manager.sync();
			EXPECT_FALSE(manager.contains(id));
			manager.dispose();
		}

		TEST("Is Syncing")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			EXPECT_FALSE(manager.is_syncing());
			UUID id = manager.schedule_load(ASSET_PATH);
			EXPECT_TRUE(manager.is_syncing());
			manager.sync();
			EXPECT_FALSE(manager.is_syncing());
			manager.dispose();
		}

		TEST("Create")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			GenericAssetBuilder textBuilder;
			textBuilder.id = UUID::create();
			Ref<GenericAsset> textAsset = manager.create<GenericAsset>(textBuilder);
			EXPECT_NOT_EQUAL(textAsset, nullptr);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			manager.dispose();
		}

		TEST("Add")
		{
			AssetManagerBuilder builder{};
			builder.savePaths = true;
			AssetManager manager(builder);
			manager.initialize();
			GenericAssetBuilder textBuilder;
			textBuilder.id = UUID::create();
			Owner<GenericAsset> textAsset = GenericAsset::create(textBuilder);
			EXPECT_FALSE(manager.contains(textAsset->get_id()));
			manager.add(textAsset);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), "");
			manager.dispose();
		}

		TEST("Add Path")
		{
			AssetManagerBuilder builder{};
			builder.savePaths = true;
			AssetManager manager(builder);
			manager.initialize();
			GenericAssetBuilder textBuilder;
			textBuilder.id = UUID::create();
			Owner<GenericAsset> textAsset = GenericAsset::create(textBuilder);
			EXPECT_FALSE(manager.contains(textAsset->get_id()));
			manager.add(ASSET_PATH, textAsset);
			EXPECT_TRUE(manager.contains(textAsset->get_id()));
			EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), ASSET_PATH);
			manager.dispose();
		}

		TEST("Contains")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			manager.load_wrap(WRAP_PATH);
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = parse_to<UUID>("0123456789abcdef");
			EXPECT_TRUE(manager.contains(id));
			EXPECT_FALSE(manager.contains(0));
			UUID badId = UUID::create();
			EXPECT_FALSE(manager.contains(badId));
			manager.dispose();
		}

		TEST("Get Asset")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			manager.load_wrap(WRAP_PATH);
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.get_asset(id), textAsset);
			EXPECT_EQUAL(manager.get_asset(0), nullptr);
			UUID badId = UUID::create();
			EXPECT_EQUAL(manager.get_asset(badId), nullptr);
			manager.dispose();
		}

		TEST("Get")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			manager.load_wrap(WRAP_PATH);
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.get<GenericAsset>(id), textAsset);
			EXPECT_EQUAL(manager.get<GenericAsset>(0), nullptr);
			UUID badId = UUID::create();
			EXPECT_EQUAL(manager.get<GenericAsset>(badId), nullptr);
			manager.dispose();
		}

		TEST("At Asset")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			manager.load_wrap(WRAP_PATH);
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.at_asset(id), textAsset);
			EXPECT_FAILURE(manager.at_asset(0));
			UUID badId = UUID::create();
			EXPECT_FAILURE(manager.at_asset(badId));
			manager.dispose();
		}

		TEST("At")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			manager.load_wrap(WRAP_PATH);
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_EQUAL(manager.at<GenericAsset>(id), textAsset);
			EXPECT_FAILURE(manager.at<GenericAsset>(0));
			UUID badId = UUID::create();
			EXPECT_FAILURE(manager.at<GenericAsset>(badId));
			manager.dispose();
		}

		TEST("Get By Type")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			Ref<GenericAsset> mintyAsset = manager.load<GenericAsset>(ASSET_PATH_MINTY);
			Vector<Ref<GenericAsset>> texts = manager.get_by_type<GenericAsset>();
			EXPECT_EQUAL(texts.get_size(), 2);
			manager.dispose();
		}

		TEST("Get Asset Path")
		{
			{
				AssetManagerBuilder builder{};
				builder.savePaths = true;
				AssetManager manager(builder);
				manager.initialize();
				Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), ASSET_PATH);
				manager.dispose();
			}
			{

				AssetManagerBuilder builder{};
				builder.savePaths = false;
				AssetManager manager(builder);
				manager.initialize();
				Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_path(textAsset->get_id()), "");
				manager.dispose();
			}
		}

		TEST("Get Asset Name")
		{
			{
				AssetManagerBuilder builder{};
				builder.savePaths = true;
				AssetManager manager(builder);
				manager.initialize();
				Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_name(textAsset->get_id()), "text");
				manager.dispose();
			}
			{
				AssetManagerBuilder builder{};
				builder.savePaths = false;
				AssetManager manager(builder);
				manager.initialize();
				Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
				EXPECT_EQUAL(manager.get_asset_name(textAsset->get_id()), "");
				manager.dispose();
			}
		}

		TEST("Remove")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Ref<GenericAsset> textAsset = manager.load<GenericAsset>(ASSET_PATH);
			UUID id = textAsset->get_id();
			EXPECT_TRUE(manager.contains(id));
			Owner<GenericAsset> removedAsset = manager.remove(id);
			EXPECT_EQUAL(removedAsset, textAsset);
			EXPECT_FALSE(manager.contains(id));
			removedAsset.release();
			EXPECT_EQUAL(textAsset, nullptr);
			manager.dispose();
		}

		TEST("Clone")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			GenericAssetBuilder textBuilder;
			textBuilder.id = UUID::create();
			String text = "Hello, World!";
			textBuilder.data = ConstantContainer(text.get_data(), text.get_size());
			Ref<GenericAsset> textAsset = manager.create<GenericAsset>(textBuilder);
			Ref<GenericAsset> clonedAsset = manager.clone<GenericAsset>(textAsset->get_id());
			EXPECT_NOT_EQUAL(clonedAsset, nullptr);
			EXPECT_NOT_EQUAL(clonedAsset, textAsset);
			EXPECT_NOT_EQUAL(clonedAsset->get_id(), textAsset->get_id());
			EXPECT_EQUAL(clonedAsset->get_text(), textAsset->get_text());
			manager.dispose();
		}

		TEST("Get Dependents")
		{
			// TODO
			EXPECT_TRUE(true);
		}

		TEST("Read GenericAsset")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			String text = manager.read_text(ASSET_PATH);
			EXPECT_TRUE(text.starts_with("Lorem"));
			manager.dispose();
		}

		TEST("Read Lines")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Vector<String> lines = manager.read_lines(ASSET_PATH);
			EXPECT_EQUAL(lines.get_size(), 5);
			EXPECT_TRUE(lines[0].starts_with("Lorem"));
			EXPECT_TRUE(lines[1].starts_with("Aliquam"));
			EXPECT_TRUE(lines[2].starts_with("Aenean"));
			EXPECT_TRUE(lines[3].starts_with("Quisque id"));
			EXPECT_TRUE(lines[4].starts_with("Quisque lacinia"));
			manager.dispose();
		}

		TEST("Read Bytes")
		{
			AssetManagerBuilder builder{};
			AssetManager manager(builder);
			manager.initialize();
			Vector<Byte> bytes = manager.read_bytes(ASSET_PATH);
			EXPECT_EQUAL(bytes.get_size(), 2948);
			manager.dispose();
		}
	}
}
