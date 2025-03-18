#include "Test_File.h"
#include "Minty.h"

void test_File(Test& _test)
{
	CATEGORY(File)
	{
		constexpr Char const* TEST_PATH = "Assets/test.txt";
		constexpr Char const* TEST_PATH_2 = "Assets/test2.txt";

		TEST("Copy")
		{
			File::copy(TEST_PATH, TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == true);
			EXPECT_TRUE(Path::exists(TEST_PATH) == true);
			File::destroy(TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == false);
		}

		TEST("Move")
		{
			File::move(TEST_PATH, TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == true);
			EXPECT_TRUE(Path::exists(TEST_PATH) == false);
			File::move(TEST_PATH_2, TEST_PATH);
			EXPECT_TRUE(Path::exists(TEST_PATH) == true);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == false);
		}

		TEST("Create")
		{
			File::create(TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == true);
			File::destroy(TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == false);
		}

		TEST("Destroy")
		{
			File::create(TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == true);
			File::destroy(TEST_PATH_2);
			EXPECT_TRUE(Path::exists(TEST_PATH_2) == false);
		}

		TEST("Read/Write Lines")
		{
			Vector<String> expected = { "Hello, World!", "Hello again!", "And again!" };
			File::write_lines(TEST_PATH_2, expected);
			Vector<String> actual = File::read_lines(TEST_PATH_2);
			EXPECT_EQUAL(actual.get_size(), expected.get_size());
			for (Size i = 0; i < Math::min(expected.get_size(), actual.get_size()); i++)
			{
				EXPECT_EQUAL(actual[i], expected[i]);
			}
			File::destroy(TEST_PATH_2);
		}

		TEST("Read/Write Text")
		{
			String expected = "Hello, World!\nHello again!\nAnd again!";
			File::write_text(TEST_PATH_2, expected);
			String actual = File::read_text(TEST_PATH_2);
			EXPECT_EQUAL(actual, expected);
			File::destroy(TEST_PATH_2);
		}
	}
}
