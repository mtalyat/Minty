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
	}
}
