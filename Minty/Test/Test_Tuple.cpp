#include "Test_Tuple.h"
#include "Minty.h"

void test_Tuple(Test& _test)
{
	CATEGORY(tuple)
	{
		TEST("Copy/Copy Constructor")
		{
			String first = "first";
			String second = "second";
			Tuple<String, String> tuple(first, second);
			EXPECT_TRUE(first == "first");
			EXPECT_TRUE(second == "second");
			EXPECT_TRUE(tuple.get_first() == "first");
			EXPECT_TRUE(tuple.get_second() == "second");
		}

		TEST("Move/Copy Constructor")
		{
			String first = "first";
			String second = "second";
			Tuple<String, String> tuple(std::move(first), second);
			EXPECT_TRUE(first == "");
			EXPECT_TRUE(second == "second");
			EXPECT_TRUE(tuple.get_first() == "first");
			EXPECT_TRUE(tuple.get_second() == "second");
		}

		TEST("Copy/Move Constructor")
		{
			String first = "first";
			String second = "second";
			Tuple<String, String> tuple(first, std::move(second));
			EXPECT_TRUE(first == "first");
			EXPECT_TRUE(second == "");
			EXPECT_TRUE(tuple.get_first() == "first");
			EXPECT_TRUE(tuple.get_second() == "second");
		}

		TEST("Move/Move Constructor")
		{
			String first = "first";
			String second = "second";
			Tuple<String, String> tuple(std::move(first), std::move(second));
			EXPECT_TRUE(first == "");
			EXPECT_TRUE(second == "");
			EXPECT_TRUE(tuple.get_first() == "first");
			EXPECT_TRUE(tuple.get_second() == "second");
		}

		TEST("Copy Constructor")
		{
			Tuple<String, String> tuple("First", "Second");
			Tuple<String, String> copy(tuple);
			EXPECT_TRUE(tuple.get_first() == "First");
			EXPECT_TRUE(tuple.get_second() == "Second");
			EXPECT_TRUE(copy.get_first() == "First");
			EXPECT_TRUE(copy.get_second() == "Second");
		}

		TEST("Move Constructor")
		{
			Tuple<String, String> tuple("First", "Second");
			Tuple<String, String> copy(std::move(tuple));
			EXPECT_TRUE(tuple.get_first() == "");
			EXPECT_TRUE(tuple.get_second() == "");
			EXPECT_TRUE(copy.get_first() == "First");
			EXPECT_TRUE(copy.get_second() == "Second");
		}

		TEST("Copy Operator")
		{
			Tuple<String, String> tuple("First", "Second");
			Tuple<String, String> copy = tuple;
			EXPECT_TRUE(tuple.get_first() == "First");
			EXPECT_TRUE(tuple.get_second() == "Second");
			EXPECT_TRUE(copy.get_first() == "First");
			EXPECT_TRUE(copy.get_second() == "Second");
		}

		TEST("Move Operator")
		{
			Tuple<String, String> tuple("First", "Second");
			Tuple<String, String> copy = std::move(tuple);
			EXPECT_TRUE(tuple.get_first() == "");
			EXPECT_TRUE(tuple.get_second() == "");
			EXPECT_TRUE(copy.get_first() == "First");
			EXPECT_TRUE(copy.get_second() == "Second");
		}

		TEST("Equal Operator")
		{
			Tuple<int, int> tuple(4, 2);
			Tuple<int, int> copy = tuple;
			EXPECT_TRUE(tuple == copy);
			EXPECT_TRUE(copy == tuple);
			Tuple<int, int> tuple2(2, 2);
			EXPECT_TRUE(!(tuple == tuple2));
		}

		TEST("Not Equal Operator")
		{
			Tuple<int, int> tuple(4, 2);
			Tuple<int, int> copy(4, 3);
			EXPECT_TRUE(tuple != copy);
			EXPECT_TRUE(copy != tuple);
			Tuple<int, int> tuple2(4, 2);
			EXPECT_TRUE(!(tuple != tuple2));
		}

		TEST("Less Than Operator")
		{
			Tuple<int, int> tuple(4, 2);
			Tuple<int, int> copy(4, 3);
			EXPECT_TRUE(tuple < copy);
			EXPECT_TRUE(!(copy < tuple));
			copy = tuple;
			EXPECT_TRUE(!(tuple < copy));
			EXPECT_TRUE(!(copy < tuple));
		}

		TEST("Less Than or Equal To Operator")
		{
			Tuple<int, int> tuple(4, 2);
			Tuple<int, int> copy(4, 3);
			EXPECT_TRUE(tuple <= copy);
			EXPECT_TRUE(!(copy <= tuple));
			copy = tuple;
			EXPECT_TRUE(tuple <= copy);
			EXPECT_TRUE(copy <= tuple);
		}

		TEST("Greater Than Operator")
		{
			Tuple<int, int> tuple(4, 2);
			Tuple<int, int> copy(4, 3);
			EXPECT_TRUE(copy > tuple);
			EXPECT_TRUE(!(tuple > copy));
			copy = tuple;
			EXPECT_TRUE(!(tuple > copy));
			EXPECT_TRUE(!(copy > tuple));
		}

		TEST("Greater Than or Equal To Operator")
		{
			Tuple<int, int> tuple(4, 2);
			Tuple<int, int> copy(4, 3);
			EXPECT_TRUE(copy >= tuple);
			EXPECT_TRUE(!(tuple >= copy));
			copy = tuple;
			EXPECT_TRUE(tuple >= copy);
			EXPECT_TRUE(copy >= tuple);
		}
	}
}