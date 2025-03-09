#include "Test_DualBuffer.h"
#include "Minty.h"

void test_DualBuffer(Test& _test)
{
	CATEGORY(DualBuffer)
	{
		Path const TEST_PATH = "test.txt";

		TEST("Default Constructor")
		{
			DualBuffer buffer;
			EXPECT_FALSE(buffer.is_open());
		}

		TEST("Open Constructor")
		{
			DualBuffer buffer(std::cout, TEST_PATH);
			EXPECT_TRUE(buffer.is_open());
			buffer.close();
			File::destroy(TEST_PATH);
		}

		TEST("Is Open")
		{
			DualBuffer buffer;
			EXPECT_FALSE(buffer.is_open());
			buffer.open(std::cout, TEST_PATH);
			EXPECT_TRUE(buffer.is_open());
			buffer.close();
			EXPECT_FALSE(buffer.is_open());
			File::destroy(TEST_PATH);
		}

		TEST("Open")
		{
			DualBuffer buffer;
			buffer.open(std::cout, TEST_PATH);
			EXPECT_TRUE(buffer.is_open());
			EXPECT_FAIL(buffer.open(std::cout, TEST_PATH));
			buffer.close();
			buffer.open(std::cout, TEST_PATH);
			EXPECT_TRUE(buffer.is_open());
			buffer.close();
			File::destroy(TEST_PATH);
		}

		TEST("Close")
		{
			DualBuffer buffer;
			EXPECT_FAIL(buffer.close());
			buffer.open(std::cout, TEST_PATH);
			buffer.close();
			EXPECT_FALSE(buffer.is_open());
			File::destroy(TEST_PATH);
		}
	}
}
