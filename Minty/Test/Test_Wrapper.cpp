#include "Test_Wrapper.h"
#include "Minty.h"

void test_Wrapper(Test& _test)
{
	constexpr Char const* TEST_PATH = "Assets/test.wrap";
	constexpr Char const* TEST_NEW_PATH = "Assets/test2.wrap";
	constexpr Char const* TEST_TEXT_PATH = "Assets/text.txt";

	constexpr Char const* TEST_NAME = "Defaults";
	constexpr Char const* TEST_ASSET_PATH = "Defaults/Material/defaultMaterial.mmat";
	constexpr Char const* TEST_ASSET_PATH_2 = "Defaults/next_id.txt";

	CATEGORY(Wrapper)
	{
		TEST("Default Constructor")
		{
			Wrapper wrapper;
			EXPECT_EQUAL(wrapper.get_wrap_count(), 0);
		}

		TEST("Get Wrap Count")
		{
			Wrapper wrapper;
			EXPECT_EQUAL(wrapper.get_wrap_count(), 0);
			wrapper.add(TEST_PATH);
			EXPECT_EQUAL(wrapper.get_wrap_count(), 1);
		}

		TEST("Add Wrap")
		{
			Wrapper wrapper;
			Wrap wrap;
			wrapper.add(wrap);
			EXPECT_EQUAL(wrapper.get_wrap_count(), 1);
		}

		TEST("Add Path")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			EXPECT_EQUAL(wrapper.get_wrap_count(), 1);
		}

		TEST("Get Wrap")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			EXPECT_EQUAL(wrapper.get_wrap(0).get_path(), Path(TEST_PATH).get_absolute());
		}

		TEST("Const Get Wrap")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			const Wrapper& wrapper2 = wrapper;
			EXPECT_EQUAL(wrapper2.get_wrap(0).get_path(), Path(TEST_PATH).get_absolute());
		}

		TEST("Find By Path")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			EXPECT_NOT_EQUAL(wrapper.find_by_path(TEST_ASSET_PATH), nullptr);
			EXPECT_NOT_EQUAL(wrapper.find_by_path(TEST_ASSET_PATH_2), nullptr);
			EXPECT_EQUAL(wrapper.find_by_path("Not Here"), nullptr);
		}

		TEST("Const Find By Path")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			const Wrapper& wrapper2 = wrapper;
			EXPECT_NOT_EQUAL(wrapper2.find_by_path(TEST_ASSET_PATH), nullptr);
			EXPECT_NOT_EQUAL(wrapper2.find_by_path(TEST_ASSET_PATH_2), nullptr);
			EXPECT_EQUAL(wrapper2.find_by_path("Not Here"), nullptr);
		}

		TEST("Find By Name")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			EXPECT_NOT_EQUAL(wrapper.find_by_name(TEST_NAME), nullptr);
			EXPECT_EQUAL(wrapper.find_by_name("Not Here"), nullptr);
		}

		TEST("Const Find By Name")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			const Wrapper& wrapper2 = wrapper;
			EXPECT_NOT_EQUAL(wrapper2.find_by_name(TEST_NAME), nullptr);
			EXPECT_EQUAL(wrapper2.find_by_name("Not Here"), nullptr);
		}

		TEST("Contains")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			EXPECT_TRUE(wrapper.contains(TEST_ASSET_PATH));
			EXPECT_TRUE(wrapper.contains(TEST_ASSET_PATH_2));
			EXPECT_TRUE(!wrapper.contains("Not Here"));
		}

		TEST("Open")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			VirtualFile file;
			EXPECT_TRUE(wrapper.open(TEST_ASSET_PATH, file));
			file.close();
		}

		TEST("Read Bytes")
		{
			Wrapper wrapper;
			wrapper.add(TEST_PATH);
			Vector<Byte> data = wrapper.read_bytes(TEST_ASSET_PATH);
			EXPECT_NOT_EQUAL(data.get_size(), 0);
			String text = String::from_bytes(data.get_data(), data.get_size());
			EXPECT_TRUE(text.contains("Template: "));
		}
	}
}
