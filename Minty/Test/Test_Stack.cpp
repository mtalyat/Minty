#include "Test_Stack.h"
#include "Minty.h"

void test_Stack(Test& _test)
{
	CATEGORY(Stack)
	{
		TEST("Default Constructor")
		{
			Stack<int> stack;
			EXPECT_TRUE(stack.get_capacity() == 0);
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Capacity Constructor")
		{
			Stack<int> stack(10);
			EXPECT_TRUE(stack.get_capacity() == 10);
			EXPECT_TRUE(stack.get_size() == 0);
			Stack<int> stack2(0);
			EXPECT_TRUE(stack2.get_capacity() == 0);
			EXPECT_TRUE(stack2.get_size() == 0);
		}

		TEST("Copy Constructor")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			Stack<int> stack2(stack);
			EXPECT_TRUE(stack2.get_capacity() == 10);
			EXPECT_TRUE(stack2.get_size() == 3);
			EXPECT_TRUE(stack2.pop() == 3);
			EXPECT_TRUE(stack2.pop() == 2);
			EXPECT_TRUE(stack2.pop() == 1);
			EXPECT_TRUE(stack2.get_size() == 0);
		}

		TEST("Move Constructor")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			Stack<int> stack2(std::move(stack));
			EXPECT_TRUE(stack2.get_capacity() == 10);
			EXPECT_TRUE(stack2.get_size() == 3);
			EXPECT_TRUE(stack2.pop() == 3);
			EXPECT_TRUE(stack2.pop() == 2);
			EXPECT_TRUE(stack2.pop() == 1);
			EXPECT_TRUE(stack2.get_size() == 0);
		}

		TEST("Copy Assignment Operator")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			Stack<int> stack2;
			stack2 = stack;
			EXPECT_TRUE(stack2.get_capacity() == 10);
			EXPECT_TRUE(stack2.get_size() == 3);
			EXPECT_TRUE(stack2.pop() == 3);
			EXPECT_TRUE(stack2.pop() == 2);
			EXPECT_TRUE(stack2.pop() == 1);
			EXPECT_TRUE(stack2.get_size() == 0);
		}

		TEST("Move Assignment Operator")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			Stack<int> stack2;
			stack2 = std::move(stack);
			EXPECT_TRUE(stack2.get_capacity() == 10);
			EXPECT_TRUE(stack2.get_size() == 3);
			EXPECT_TRUE(stack2.pop() == 3);
			EXPECT_TRUE(stack2.pop() == 2);
			EXPECT_TRUE(stack2.pop() == 1);
			EXPECT_TRUE(stack2.get_size() == 0);
		}

		TEST("Get Capacity")
		{
			Stack<int> stack(10);
			EXPECT_TRUE(stack.get_capacity() == 10);
			stack.reserve(20);
			EXPECT_TRUE(stack.get_capacity() == 20);
		}

		TEST("Get Size")
		{
			Stack<int> stack(10);
			EXPECT_TRUE(stack.get_size() == 0);
			stack.push(1);
			EXPECT_TRUE(stack.get_size() == 1);
			stack.push(2);
			EXPECT_TRUE(stack.get_size() == 2);
			stack.push(3);
			EXPECT_TRUE(stack.get_size() == 3);
			stack.pop();
			EXPECT_TRUE(stack.get_size() == 2);
			stack.pop();
			EXPECT_TRUE(stack.get_size() == 1);
			stack.pop();
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Get Data")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			EXPECT_TRUE(stack.get_data()[1] == 2);
			EXPECT_TRUE(stack.get_data()[2] == 3);
		}

		TEST("Const Get Data")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			const Stack<int>& stack2 = stack;
			EXPECT_TRUE(stack2.get_data()[0] == 1);
			EXPECT_TRUE(stack2.get_data()[1] == 2);
			EXPECT_TRUE(stack2.get_data()[2] == 3);
		}

		TEST("Reserve")
		{
			Stack<int> stack(10);
			stack.reserve(20);
			EXPECT_TRUE(stack.get_capacity() == 20);
			stack.reserve(5);
			EXPECT_TRUE(stack.get_capacity() == 20);
		}

		TEST("Push Copy")
		{
			Stack<int> stack(10);
			stack.push(1);
			EXPECT_TRUE(stack.get_size() == 1);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			stack.push(2);
			EXPECT_TRUE(stack.get_size() == 2);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			EXPECT_TRUE(stack.get_data()[1] == 2);
			stack.push(3);
			EXPECT_TRUE(stack.get_size() == 3);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			EXPECT_TRUE(stack.get_data()[1] == 2);
			EXPECT_TRUE(stack.get_data()[2] == 3);
		}

		TEST("Push Move")
		{
			Stack<int> stack(10);
			stack.push(1);
			EXPECT_TRUE(stack.get_size() == 1);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			stack.push(2);
			EXPECT_TRUE(stack.get_size() == 2);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			EXPECT_TRUE(stack.get_data()[1] == 2);
			stack.push(3);
			EXPECT_TRUE(stack.get_size() == 3);
			EXPECT_TRUE(stack.get_data()[0] == 1);
			EXPECT_TRUE(stack.get_data()[1] == 2);
			EXPECT_TRUE(stack.get_data()[2] == 3);
		}

		TEST("Pop")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			EXPECT_TRUE(stack.pop() == 3);
			EXPECT_TRUE(stack.pop() == 2);
			EXPECT_TRUE(stack.pop() == 1);
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Is Empty")
		{
			Stack<int> stack(10);
			EXPECT_TRUE(stack.is_empty());
			stack.push(1);
			EXPECT_TRUE(!stack.is_empty());
			stack.pop();
			EXPECT_TRUE(stack.is_empty());
		}

		TEST("Peek")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			EXPECT_TRUE(stack.peek() == 3);
			stack.pop();
			EXPECT_TRUE(stack.peek() == 2);
			stack.pop();
			EXPECT_TRUE(stack.peek() == 1);
			stack.pop();
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Const Peek")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			const Stack<int>& stack2 = stack;
			EXPECT_TRUE(stack2.peek() == 3);
			stack.pop();
			EXPECT_TRUE(stack2.peek() == 2);
			stack.pop();
			EXPECT_TRUE(stack2.peek() == 1);
			stack.pop();
			EXPECT_TRUE(stack2.get_size() == 0);
		}

		TEST("Clear")
		{
			Stack<int> stack(10);
			stack.push(1);
			stack.push(2);
			stack.push(3);
			stack.clear();
			EXPECT_TRUE(stack.get_size() == 0);
		}
	}
}
