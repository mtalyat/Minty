#include "Test_Wrap.h"
#include "Minty.h"

void test_Wrap(Test& _test)
{
	CATEGORY(Wrap)
	{
		constexpr Char const* TEST_PATH = "Assets/test.wrap";
		constexpr Char const* TEST_NEW_PATH = "Assets/test2.wrap";
		constexpr Char const* TEST_TEXT_PATH = "Assets/text.txt";

		TEST("Default Constructor")
		{
			Wrap wrap;
			EXPECT_TRUE(String(wrap.get_base_path()) == "");
			EXPECT_TRUE(wrap.get_content_version() == 0);
			EXPECT_TRUE(wrap.get_entry_count() == 0);
			EXPECT_TRUE(String(wrap.get_name()) == "");
			EXPECT_TRUE(wrap.get_path().get_string() == "");
			EXPECT_TRUE(wrap.get_size() == 0);
			EXPECT_TRUE(wrap.get_type() == Wrap::Type::None);
			EXPECT_TRUE(wrap.get_wrap_version() == 0);
		}

		TEST("Path Constructor")
		{
			Wrap wrap(TEST_PATH);
			EXPECT_TRUE(String(wrap.get_base_path()) != "");
			EXPECT_TRUE(wrap.get_content_version() >= 0);
			EXPECT_TRUE(wrap.get_entry_count() != 0);
			EXPECT_TRUE(String(wrap.get_name()) != "");
			EXPECT_TRUE(wrap.get_path() == Path(TEST_PATH).get_absolute());
			EXPECT_TRUE(wrap.get_size() != 0);
			EXPECT_TRUE(wrap.get_type() != Wrap::Type::None);
		}

		TEST("New Constructor")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(String(wrap.get_base_path()) == "");
			EXPECT_TRUE(wrap.get_content_version() == 0);
			EXPECT_TRUE(wrap.get_entry_count() == 0);
			EXPECT_TRUE(String(wrap.get_name()) == "Test");
			EXPECT_TRUE(wrap.get_path() == Path(TEST_NEW_PATH).get_absolute());
			EXPECT_TRUE(wrap.get_size() != 0);
			EXPECT_TRUE(wrap.get_type() == Wrap::Type::File);
			Path::exists(TEST_NEW_PATH);
			File::destroy(TEST_NEW_PATH);

			Wrap wrap2(TEST_NEW_PATH, "Test Again", 0, "Test/Path", 34);
			EXPECT_TRUE(String(wrap2.get_base_path()) == "Test/Path");
			EXPECT_TRUE(wrap2.get_content_version() == 34);
			EXPECT_TRUE(wrap2.get_entry_count() == 0);
			EXPECT_TRUE(String(wrap2.get_name()) == "Test Again");
			EXPECT_TRUE(wrap2.get_path() == Path(TEST_NEW_PATH).get_absolute());
			EXPECT_TRUE(wrap2.get_size() != 0);
			EXPECT_TRUE(wrap2.get_type() == Wrap::Type::File);
			Path::exists(TEST_NEW_PATH);
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get/Set Base Path")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(String(wrap.get_base_path()) == "");

			wrap.set_base_path("Test/Path");
			EXPECT_TRUE(String(wrap.get_base_path()) == "Test/Path");

			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get Path")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(wrap.get_path() == Path(TEST_NEW_PATH).get_absolute());
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get/Set Name")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(String(wrap.get_name()) == "Test");
			wrap.set_name("Test Again");
			EXPECT_TRUE(String(wrap.get_name()) == "Test Again");
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get Wrap Version")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(wrap.get_wrap_version() == WRAP_VERSION);
			File::destroy(TEST_NEW_PATH);
		}
		
		TEST("Get Content Version")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(wrap.get_content_version() == 0);
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get/Set Type")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(wrap.get_type() == Wrap::Type::File);
			wrap.set_type(Wrap::Type::None);
			EXPECT_TRUE(wrap.get_type() == Wrap::Type::None);
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get Size")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(wrap.get_size() != 0);
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get Entry Count")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 0);
			EXPECT_TRUE(wrap.get_entry_count() == 0);
			File::destroy(TEST_NEW_PATH);
			Wrap wrap2(TEST_NEW_PATH, "Test", 23);
			EXPECT_TRUE(wrap2.get_entry_count() == 23);
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Load")
		{
			Wrap wrap;
			wrap.load(TEST_PATH);
			EXPECT_TRUE(String(wrap.get_base_path()) != "");
			EXPECT_TRUE(wrap.get_content_version() >= 0);
			EXPECT_TRUE(wrap.get_entry_count() != 0);
			EXPECT_TRUE(String(wrap.get_name()) != "");
			EXPECT_TRUE(wrap.get_path() == Path(TEST_PATH).get_absolute());
			EXPECT_TRUE(wrap.get_size() != 0);
			EXPECT_TRUE(wrap.get_type() != Wrap::Type::None);
		}

		TEST("Add")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 1);
			wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			EXPECT_TRUE(wrap.get_entry_count() == 1);
			EXPECT_TRUE(wrap.get_size() != 0);

			// read raw file: can only do this because compression is None
			PhysicalFile file(TEST_TEXT_PATH, File::Flags::Read | File::Flags::Binary);
			Char buffer[KB];
			memset(buffer, 0, KB);
			file.read(buffer, KB);
			file.close();

			// assume lorem text is all there
			String text = buffer;
			EXPECT_TRUE(text.contains("Lorem ipsum"));

			// cannot add more than max entry count
			EXPECT_FAILURE(wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None));

			File::destroy(TEST_NEW_PATH);
		}

		TEST("Contains")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 1);
			wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			EXPECT_TRUE(wrap.contains("GenericAsset.txt"));
			EXPECT_TRUE(wrap.contains("Text2.txt") == false);
			File::destroy(TEST_NEW_PATH);

			Wrap wrap2(TEST_NEW_PATH, "Test", 1, "Base/Path");
			wrap2.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			EXPECT_TRUE(wrap2.contains("Base/Path/GenericAsset.txt"));
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Open")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 1);
			wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			VirtualFile file;
			EXPECT_TRUE(wrap.open("GenericAsset.txt", file));

			Char buffer[KB];
			memset(buffer, 0, KB);
			file.read(buffer, KB);
			file.close();

			// assume lorem text is all there
			String text = buffer;
			EXPECT_TRUE(text.contains("Lorem ipsum"));

			File::destroy(TEST_NEW_PATH);
		}

		TEST("Read Bytes")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 1);
			wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			Vector<Byte> data = wrap.read_bytes("GenericAsset.txt");
			// assume lorem text is all there
			String text = String::from_bytes(data.get_data(), data.get_size());

			EXPECT_TRUE(text.contains("Lorem ipsum"));
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get Entry Index")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 1);
			wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			EXPECT_TRUE(Path(wrap.get_entry(0).path) == "GenericAsset.txt");
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Get Entry Path")
		{
			Wrap wrap(TEST_NEW_PATH, "Test", 1);
			wrap.add(TEST_TEXT_PATH, "GenericAsset.txt", CompressionLevel::None);
			EXPECT_TRUE(Path(wrap.get_entry("GenericAsset.txt").path) == "GenericAsset.txt");
			File::destroy(TEST_NEW_PATH);
		}

		TEST("Load Or Create")
		{
			// create
			Wrap wrap = Wrap::load_or_create(TEST_NEW_PATH, "Test", 1, "Test/Path", 34);
			EXPECT_TRUE(Path(wrap.get_base_path()) == "Test/Path");
			EXPECT_TRUE(wrap.get_content_version() == 34);
			EXPECT_TRUE(wrap.get_entry_count() == 1);
			EXPECT_TRUE(String(wrap.get_name()) == "Test");
			EXPECT_TRUE(wrap.get_path() == Path(TEST_NEW_PATH).get_absolute());
			EXPECT_TRUE(wrap.get_size() != 0);
			EXPECT_TRUE(wrap.get_type() == Wrap::Type::File);

			// load
			Wrap wrap2 = Wrap::load_or_create(TEST_NEW_PATH, "Test", 1, "Test/Path", 34);
			EXPECT_TRUE(Path(wrap2.get_base_path()) == "Test/Path");
			EXPECT_TRUE(wrap2.get_content_version() == 34);
			EXPECT_TRUE(wrap2.get_entry_count() == 1);
			EXPECT_TRUE(String(wrap2.get_name()) == "Test");
			EXPECT_TRUE(wrap2.get_path() == Path(TEST_NEW_PATH).get_absolute());
			EXPECT_TRUE(wrap2.get_size() != 0);
			EXPECT_TRUE(wrap2.get_type() == Wrap::Type::File);

			File::destroy(TEST_NEW_PATH);
		}
	}
}
