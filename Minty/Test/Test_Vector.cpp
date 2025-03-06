#include "MintyTest.h"

void test_Vector(Test& _test)
{
	CATEGORY(Vector::Iterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.end());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.end();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.begin());
			it = test.end();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.begin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.end();
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(it - 2 == test.begin() + 1);
			EXPECT_TRUE(it - 1 == test.begin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::Iterator it = test.begin();
			Vector<int>::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(Vector::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.cend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.cend());
			it = test.cbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.cend());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.cend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.cend());
			it = test.cbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.cend());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.cbegin());
			it = test.cend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.cbegin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cend();
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(it - 2 == test.cbegin() + 1);
			EXPECT_TRUE(it - 1 == test.cbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.cbegin());
			EXPECT_TRUE(test.cbegin() == it);
			EXPECT_TRUE(copy == test.cbegin());
			EXPECT_TRUE(test.cbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstIterator it = test.cbegin();
			Vector<int>::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != it));
			EXPECT_TRUE(!(copy != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != copy));
		}
	}

	CATEGORY(Vector::ReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			it = test.rbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.rend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.rend());
			it = test.rbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.rend());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.rend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.rend());
			it = test.rbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.rend());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.rbegin());
			it = test.rend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.rbegin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rend();
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(it - 2 == test.rbegin() + 1);
			EXPECT_TRUE(it - 1 == test.rbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.rbegin());
			EXPECT_TRUE(test.rbegin() == it);
			EXPECT_TRUE(copy == test.rbegin());
			EXPECT_TRUE(test.rbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ReverseIterator it = test.rbegin();
			Vector<int>::ReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != it));
			EXPECT_TRUE(!(copy != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != copy));
		}
	}

	CATEGORY(Vector::ConstReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Move Constructor")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			it = test.crbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Copy Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			copy = it;
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Move Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 5);
			EXPECT_TRUE(*(copy + 1) == 5);
			EXPECT_TRUE(*(copy + 2) == 5);
			EXPECT_TRUE(copy + 3 == test.crend());
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(*++copy == 5);
			EXPECT_TRUE(++copy == test.crend());
			it = test.crbegin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(*copy++ == 5);
			EXPECT_TRUE(copy == test.crend());
		}

		TEST("Dereference Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
			EXPECT_TRUE(it + 3 == test.crend());
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(*++it == 5);
			EXPECT_TRUE(++it == test.crend());
			it = test.crbegin();
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(*it++ == 5);
			EXPECT_TRUE(it == test.crend());
		}

		TEST("Decrement Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(--it == test.crbegin());
			it = test.crend();
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(it == test.crbegin());
		}

		TEST("Addition Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(it - 2 == test.crbegin() + 1);
			EXPECT_TRUE(it - 1 == test.crbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.crbegin());
			EXPECT_TRUE(test.crbegin() == it);
			EXPECT_TRUE(copy == test.crbegin());
			EXPECT_TRUE(test.crbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Vector<int> test(3, 5);
			Vector<int>::ConstReverseIterator it = test.crbegin();
			Vector<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != it));
			EXPECT_TRUE(!(copy != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != copy));
		}
	}

	CATEGORY(Vector)
	{
		TEST("Default Constructor")
		{
			Vector<int> vec;
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 0);
			EXPECT_TRUE(vec.get_data() == nullptr);
		}

		TEST("Capacity Constructor")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 10);
			EXPECT_TRUE(vec.get_data() != nullptr);

			Vector<int> vec2(0);
			EXPECT_TRUE(vec2.get_size() == 0);
			EXPECT_TRUE(vec2.get_capacity() == 0);
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Value Constructor")
		{
			Vector<int> vec(10, 5);
			EXPECT_TRUE(vec.get_size() == 10);
			EXPECT_TRUE(vec.get_capacity() == 10);
			EXPECT_TRUE(vec.get_data() != nullptr);
			for (Size i = 0; i < vec.get_size(); i++)
			{
				EXPECT_TRUE(vec[i] == 5);
			}

			Vector<int> vec2(0, 0);
			EXPECT_TRUE(vec2.get_size() == 0);
			EXPECT_TRUE(vec2.get_capacity() == 0);
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Initializer List Constructor")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.get_size() == 5);
			EXPECT_TRUE(vec.get_capacity() == 5);
			EXPECT_TRUE(vec.get_data() != nullptr);
			for (Size i = 0; i < vec.get_size(); i++)
			{
				EXPECT_TRUE(vec[i] == i);
			}

			Vector<int> vec2({});
			EXPECT_TRUE(vec2.get_size() == 0);
			EXPECT_TRUE(vec2.get_capacity() == 0);
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Copy Constructor")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy(vec);
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Move Constructor")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy(std::move(vec));
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Copy Operator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy = vec;
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Move Operator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> copy = std::move(vec);
			EXPECT_TRUE(copy.get_size() == 5);
			EXPECT_TRUE(copy.get_capacity() == 5);
			EXPECT_TRUE(copy.get_data() != nullptr);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Index Operator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 2);
			EXPECT_TRUE(vec[3] == 3);
			EXPECT_TRUE(vec[4] == 4);
			EXPECT_FAIL(vec[5]);
		}

		TEST("Const Index Operator")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 2);
			EXPECT_TRUE(vec[3] == 3);
			EXPECT_TRUE(vec[4] == 4);
			EXPECT_FAIL(vec[5]);
		}

		TEST("Get Capacity")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_capacity() == 10);

			Vector<int> vec2;
			EXPECT_TRUE(vec2.get_capacity() == 0);
		}

		TEST("Get Size")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_size() == 0);

			vec.resize(5);
			EXPECT_TRUE(vec.get_size() == 5);
		}

		TEST("Get Data")
		{
			Vector<int> vec(10);
			EXPECT_TRUE(vec.get_data() != nullptr);
			Vector<int> vec2;
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Const Get Data")
		{
			Vector<int> const vec(10);
			EXPECT_TRUE(vec.get_data() != nullptr);
			Vector<int> const vec2;
			EXPECT_TRUE(vec2.get_data() == nullptr);
		}

		TEST("Reserve")
		{
			Vector<int> vec(10);
			vec.reserve(20);
			EXPECT_TRUE(vec.get_capacity() == 20);
			vec.reserve(5);
			EXPECT_TRUE(vec.get_capacity() == 20);
		}

		TEST("Resize")
		{
			Vector<int> vec(10);
			vec.resize(5);
			EXPECT_TRUE(vec.get_size() == 5);
			vec.resize(10);
			EXPECT_TRUE(vec.get_size() == 10);
			vec.resize(0);
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 10);
			vec.resize(20);
			EXPECT_TRUE(vec.get_size() == 20);
			EXPECT_TRUE(vec.get_capacity() == 20);
		}

		TEST("Add Copy")
		{
			Vector<String> vec(10);
			String str = "5";
			vec.add(str);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == "5");
			str = "10";
			vec.add(str);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[1] == "10");
		}

		TEST("Add Move")
		{
			Vector<String> vec(10);
			String str = "5";
			vec.add(std::move(str));
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == "5");
			str = "10";
			vec.add(std::move(str));
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[1] == "10");
		}

		TEST("Add Range")
		{
			Vector<int> vec(10);
			Vector<int> range({ 0, 1, 2, 3, 4 });
			vec.add(range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 5);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 2);
			EXPECT_TRUE(vec[3] == 3);
			EXPECT_TRUE(vec[4] == 4);
		}

		TEST("Insert Index Copy")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.insert(2, 5);
			EXPECT_TRUE(vec.get_size() == 6);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 2);
			EXPECT_TRUE(vec[4] == 3);
			EXPECT_TRUE(vec[5] == 4);
			vec.insert(0, 6);
			EXPECT_TRUE(vec.get_size() == 7);
			EXPECT_TRUE(vec[0] == 6);
			EXPECT_TRUE(vec[1] == 0);
			EXPECT_TRUE(vec[2] == 1);
			EXPECT_TRUE(vec[3] == 5);
			EXPECT_TRUE(vec[4] == 2);
			EXPECT_TRUE(vec[5] == 3);
			EXPECT_TRUE(vec[6] == 4);
			vec.insert(7, 7);
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 6);
			EXPECT_TRUE(vec[1] == 0);
			EXPECT_TRUE(vec[2] == 1);
			EXPECT_TRUE(vec[3] == 5);
			EXPECT_TRUE(vec[4] == 2);
			EXPECT_TRUE(vec[5] == 3);
			EXPECT_TRUE(vec[6] == 4);
			EXPECT_TRUE(vec[7] == 7);
		}

		TEST("Insert Index Move")
		{
			Vector<String> vec({ "0", "1", "2", "3", "4" });
			String str = "5";
			vec.insert(2, std::move(str));
			EXPECT_TRUE(vec.get_size() == 6);
			EXPECT_TRUE(vec[0] == "0");
			EXPECT_TRUE(vec[1] == "1");
			EXPECT_TRUE(vec[2] == "5");
			EXPECT_TRUE(vec[3] == "2");
			EXPECT_TRUE(vec[4] == "3");
			EXPECT_TRUE(vec[5] == "4");
			str = "6";
			vec.insert(0, std::move(str));
			EXPECT_TRUE(vec.get_size() == 7);
			EXPECT_TRUE(vec[0] == "6");
			EXPECT_TRUE(vec[1] == "0");
			EXPECT_TRUE(vec[2] == "1");
			EXPECT_TRUE(vec[3] == "5");
			EXPECT_TRUE(vec[4] == "2");
			EXPECT_TRUE(vec[5] == "3");
			EXPECT_TRUE(vec[6] == "4");
			str = "7";
			vec.insert(7, std::move(str));
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == "6");
			EXPECT_TRUE(vec[1] == "0");
			EXPECT_TRUE(vec[2] == "1");
			EXPECT_TRUE(vec[3] == "5");
			EXPECT_TRUE(vec[4] == "2");
			EXPECT_TRUE(vec[5] == "3");
			EXPECT_TRUE(vec[6] == "4");
			EXPECT_TRUE(vec[7] == "7");
		}

		TEST("Insert Iterator Copy")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> range({ 5, 6, 7 });
			vec.insert(vec.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 6);
			EXPECT_TRUE(vec[4] == 7);
			EXPECT_TRUE(vec[5] == 2);
			EXPECT_TRUE(vec[6] == 3);
			EXPECT_TRUE(vec[7] == 4);
		}

		TEST("Insert Iterator Move")
		{
			Vector<String> vec({ "0", "1", "2", "3", "4" });
			Vector<String> range({ "5", "6", "7" });
			vec.insert(vec.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == "0");
			EXPECT_TRUE(vec[1] == "1");
			EXPECT_TRUE(vec[2] == "5");
			EXPECT_TRUE(vec[3] == "6");
			EXPECT_TRUE(vec[4] == "7");
			EXPECT_TRUE(vec[5] == "2");
			EXPECT_TRUE(vec[6] == "3");
			EXPECT_TRUE(vec[7] == "4");
		}

		TEST("Insert Index Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> range({ 5, 6, 7 });
			vec.insert(2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 6);
			EXPECT_TRUE(vec[4] == 7);
			EXPECT_TRUE(vec[5] == 2);
			EXPECT_TRUE(vec[6] == 3);
			EXPECT_TRUE(vec[7] == 4);
		}

		TEST("Insert Iterator Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> range({ 5, 6, 7 });
			vec.insert(vec.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(vec.get_size() == 8);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 5);
			EXPECT_TRUE(vec[3] == 6);
			EXPECT_TRUE(vec[4] == 7);
			EXPECT_TRUE(vec[5] == 2);
			EXPECT_TRUE(vec[6] == 3);
			EXPECT_TRUE(vec[7] == 4);
		}

		TEST("Remove Index")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(2);
			EXPECT_TRUE(vec.get_size() == 4);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 3);
			EXPECT_TRUE(vec[3] == 4);
			vec.remove(0);
			EXPECT_TRUE(vec.get_size() == 3);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			EXPECT_TRUE(vec[2] == 4);
			vec.remove(2);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			vec.remove(1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 1);
			vec.remove(0);
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Remove Iterator")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(vec.begin() + 2);
			EXPECT_TRUE(vec.get_size() == 4);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 1);
			EXPECT_TRUE(vec[2] == 3);
			EXPECT_TRUE(vec[3] == 4);
			vec.remove(vec.begin());
			EXPECT_TRUE(vec.get_size() == 3);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			EXPECT_TRUE(vec[2] == 4);
			vec.remove(vec.begin() + 2);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 1);
			EXPECT_TRUE(vec[1] == 3);
			vec.remove(vec.begin() + 1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 1);
			vec.remove(vec.begin());
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Remove Index Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_FAIL(vec.remove(0, 0));
			EXPECT_FAIL(vec.remove(5, 1));
			EXPECT_FAIL(vec.remove(0, 6));
			vec.remove(1, 3);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 4);
			vec.remove(0, 1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			vec.remove(0, 1);
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Remove Iterator Range")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.remove(vec.begin() + 1, vec.begin() + 4);
			EXPECT_TRUE(vec.get_size() == 2);
			EXPECT_TRUE(vec[0] == 0);
			EXPECT_TRUE(vec[1] == 4);
			vec.remove(vec.begin(), vec.begin() + 1);
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			EXPECT_FAIL(vec.remove(vec.begin(), vec.begin()));
			EXPECT_TRUE(vec.get_size() == 1);
			EXPECT_TRUE(vec[0] == 4);
			vec.remove(vec.begin(), vec.begin() + 1);
			EXPECT_TRUE(vec.get_size() == 0);
		}

		TEST("Is Empty")
		{
			Vector<int> vec;
			EXPECT_TRUE(vec.is_empty());
			vec.add(0);
			EXPECT_TRUE(!vec.is_empty());
			vec.remove(0);
			EXPECT_TRUE(vec.is_empty());
		}

		TEST("At")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.at(0) == 0);
			EXPECT_TRUE(vec.at(1) == 1);
			EXPECT_TRUE(vec.at(2) == 2);
			EXPECT_TRUE(vec.at(3) == 3);
			EXPECT_TRUE(vec.at(4) == 4);
			EXPECT_FAIL(vec.at(5));
			vec.at(0) = 5;
			EXPECT_TRUE(vec.at(0) == 5);
		}

		TEST("Const At")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.at(0) == 0);
			EXPECT_TRUE(vec.at(1) == 1);
			EXPECT_TRUE(vec.at(2) == 2);
			EXPECT_TRUE(vec.at(3) == 3);
			EXPECT_TRUE(vec.at(4) == 4);
			EXPECT_FAIL(vec.at(5));
		}

		TEST("Sub")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			Vector<int> sub = vec.sub(2, 2);
			EXPECT_TRUE(sub.get_size() == 2);
			EXPECT_TRUE(sub[0] == 2);
			EXPECT_TRUE(sub[1] == 3);
		}

		TEST("Find")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.find(0) == vec.begin());
			EXPECT_TRUE(vec.find(1) == vec.begin() + 1);
			EXPECT_TRUE(vec.find(2) == vec.begin() + 2);
			EXPECT_TRUE(vec.find(3) == vec.begin() + 3);
			EXPECT_TRUE(vec.find(4) == vec.begin() + 4);
			EXPECT_TRUE(vec.find(5) == vec.end());
		}

		TEST("Const Find")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.find(0) == vec.cbegin());
			EXPECT_TRUE(vec.find(1) == vec.cbegin() + 1);
			EXPECT_TRUE(vec.find(2) == vec.cbegin() + 2);
			EXPECT_TRUE(vec.find(3) == vec.cbegin() + 3);
			EXPECT_TRUE(vec.find(4) == vec.cbegin() + 4);
			EXPECT_TRUE(vec.find(5) == vec.cend());
		}

		TEST("Contains")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.contains(0));
			EXPECT_TRUE(vec.contains(1));
			EXPECT_TRUE(vec.contains(2));
			EXPECT_TRUE(vec.contains(3));
			EXPECT_TRUE(vec.contains(4));
			EXPECT_TRUE(!vec.contains(5));
		}

		TEST("Clear")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			vec.clear();
			EXPECT_TRUE(vec.get_size() == 0);
			EXPECT_TRUE(vec.get_capacity() == 5);
			EXPECT_TRUE(vec.get_data() != nullptr);
		}

		TEST("Begin")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.begin() == 0);
		}

		TEST("Const Begin")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.cbegin() == 0);
		}

		TEST("End")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.end() == vec.begin() + 5);
		}

		TEST("Const End")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.cend() == vec.cbegin() + 5);
		}

		TEST("Reverse Begin")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.rbegin() == 4);
		}

		TEST("Reverse End")
		{
			Vector<int> vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.rend() == vec.rbegin() + 5);
		}

		TEST("Const Reverse Begin")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*vec.crbegin() == 4);
		}

		TEST("Const Reverse End")
		{
			Vector<int> const vec({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(vec.crend() == vec.crbegin() + 5);
		}
	}
}