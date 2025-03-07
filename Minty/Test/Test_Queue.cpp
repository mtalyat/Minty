#include "Test_Queue.h"
#include "Minty.h"

void test_Queue(Test& _test)
{
	CATEGORY(Queue)
	{
		TEST("Default Constructor")
		{
			Queue<int> test;
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Copy Constructor")
		{
			Queue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Queue<int> copy(test);
			EXPECT_TRUE(copy.get_size() == 3);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy.pop() == i);
			}
		}

		TEST("Move Constructor")
		{
			Queue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Queue<int> copy(std::move(test));
			EXPECT_TRUE(copy.get_size() == 3);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy.pop() == i);
			}
		}

		TEST("Copy Operator")
		{
			Queue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Queue<int> copy = test;
			EXPECT_TRUE(copy.get_size() == 3);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy.pop() == i);
			}
		}

		TEST("Move Operator")
		{
			Queue<int> test;
			test.push(0);
			test.push(1);
			test.push(2);
			Queue<int> copy = std::move(test);
			EXPECT_TRUE(copy.get_size() == 3);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy.pop() == i);
			}
		}

		TEST("Get Size")
		{
			Queue<int> test;
			EXPECT_TRUE(test.get_size() == 0);
			test.push(0);
			EXPECT_TRUE(test.get_size() == 1);
			test.pop();
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Push Copy")
		{
			Queue<String> test;
			String str = "5";
			test.push(str);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test.peek() == "5");
			str = "10";
			test.push(str);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test.pop() == "5");
			EXPECT_TRUE(test.pop() == "10");
		}

		TEST("Push Move")
		{
			Queue<String> test;
			String str = "5";
			test.push(std::move(str));
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test.peek() == "5");
			str = "10";
			test.push(std::move(str));
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test.pop() == "5");
			EXPECT_TRUE(test.pop() == "10");
		}

		TEST("Pop")
		{
			Queue<int> test;
			EXPECT_FAIL(test.pop());
			test.push(0);
			test.push(1);
			test.push(2);
			EXPECT_TRUE(test.pop() == 0);
			EXPECT_TRUE(test.pop() == 1);
			EXPECT_TRUE(test.pop() == 2);
			EXPECT_FAIL(test.pop());
		}

		TEST("Is Empty")
		{
			Queue<int> test;
			EXPECT_TRUE(test.is_empty());
			test.push(0);
			EXPECT_TRUE(!test.is_empty());
			test.pop();
			EXPECT_TRUE(test.is_empty());
		}

		TEST("Clear")
		{
			Queue<int> test;
			test.push(0);
			test.push(1);
			EXPECT_TRUE(test.get_size() == 2);
			test.clear();
			EXPECT_TRUE(test.get_size() == 0);
		}
	}
}
