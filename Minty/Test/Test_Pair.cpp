#include "Test_Pair.h"
#include "Minty.h"

void test_Pair(Test& _test)
{
	CATEGORY(Pair)
	{
		TEST("Copy/Copy Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(first, second);
			EXPECT_TRUE(first == "first");
			EXPECT_TRUE(second == "second");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Move/Copy Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(std::move(first), second);
			EXPECT_TRUE(first == "");
			EXPECT_TRUE(second == "second");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Copy/Move Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(first, std::move(second));
			EXPECT_TRUE(first == "first");
			EXPECT_TRUE(second == "");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Move/Move Constructor")
		{
			String first = "first";
			String second = "second";
			Pair<String, String> pair(std::move(first), std::move(second));
			EXPECT_TRUE(first == "");
			EXPECT_TRUE(second == "");
			EXPECT_TRUE(pair.first == "first");
			EXPECT_TRUE(pair.second == "second");
		}

		TEST("Copy Constructor")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy(pair);
			EXPECT_TRUE(pair.first == "First");
			EXPECT_TRUE(pair.second == "Second");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Move Constructor")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy(std::move(pair));
			EXPECT_TRUE(pair.first == "");
			EXPECT_TRUE(pair.second == "");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Copy Operator")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy = pair;
			EXPECT_TRUE(pair.first == "First");
			EXPECT_TRUE(pair.second == "Second");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Move Operator")
		{
			Pair<String, String> pair("First", "Second");
			Pair<String, String> copy = std::move(pair);
			EXPECT_TRUE(pair.first == "");
			EXPECT_TRUE(pair.second == "");
			EXPECT_TRUE(copy.first == "First");
			EXPECT_TRUE(copy.second == "Second");
		}

		TEST("Equal Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy = pair;
			EXPECT_TRUE(pair == copy);
			EXPECT_TRUE(copy == pair);
			Pair<int, int> pair2(2, 2);
			EXPECT_TRUE(!(pair == pair2));
		}

		TEST("Not Equal Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(pair != copy);
			EXPECT_TRUE(copy != pair);
			Pair<int, int> pair2(4, 2);
			EXPECT_TRUE(!(pair != pair2));
		}

		TEST("Less Than Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(pair < copy);
			EXPECT_TRUE(!(copy < pair));
			copy = pair;
			EXPECT_TRUE(!(pair < copy));
			EXPECT_TRUE(!(copy < pair));
		}

		TEST("Less Than or Equal To Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(pair <= copy);
			EXPECT_TRUE(!(copy <= pair));
			copy = pair;
			EXPECT_TRUE(pair <= copy);
			EXPECT_TRUE(copy <= pair);
		}

		TEST("Greater Than Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(copy > pair);
			EXPECT_TRUE(!(pair > copy));
			copy = pair;
			EXPECT_TRUE(!(pair > copy));
			EXPECT_TRUE(!(copy > pair));
		}

		TEST("Greater Than or Equal To Operator")
		{
			Pair<int, int> pair(4, 2);
			Pair<int, int> copy(4, 3);
			EXPECT_TRUE(copy >= pair);
			EXPECT_TRUE(!(pair >= copy));
			copy = pair;
			EXPECT_TRUE(pair >= copy);
			EXPECT_TRUE(copy >= pair);
		}
	}
}