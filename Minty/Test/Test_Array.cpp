#include "Test_Array.h"
#include "Minty.h"

void test_Array(Test& _test)
{
	CATEGORY(Array::Iterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy(std::move(it));
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
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = it;
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
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = std::move(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
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
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.end();
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
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.end();
			EXPECT_TRUE(it - 3 == test.begin());
			EXPECT_TRUE(it - 2 == test.begin() + 1);
			EXPECT_TRUE(it - 1 == test.begin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::Iterator it = test.begin();
			Array<int, 3>::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(Array::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy(std::move(it));
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = it;
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = std::move(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cend();
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cend();
			EXPECT_TRUE(it - 3 == test.cbegin());
			EXPECT_TRUE(it - 2 == test.cbegin() + 1);
			EXPECT_TRUE(it - 1 == test.cbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.cbegin());
			EXPECT_TRUE(test.cbegin() == it);
			EXPECT_TRUE(copy == test.cbegin());
			EXPECT_TRUE(test.cbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstIterator it = test.cbegin();
			Array<int, 3>::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != it));
			EXPECT_TRUE(!(copy != test.cbegin()));
			EXPECT_TRUE(!(test.cbegin() != copy));
		}
	}

	CATEGORY(Array::ReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy(std::move(it));
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
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = it;
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
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = std::move(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
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
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rend();
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
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rend();
			EXPECT_TRUE(it - 3 == test.rbegin());
			EXPECT_TRUE(it - 2 == test.rbegin() + 1);
			EXPECT_TRUE(it - 1 == test.rbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.rbegin());
			EXPECT_TRUE(test.rbegin() == it);
			EXPECT_TRUE(copy == test.rbegin());
			EXPECT_TRUE(test.rbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ReverseIterator it = test.rbegin();
			Array<int, 3>::ReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != it));
			EXPECT_TRUE(!(copy != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != copy));
		}
	}

	CATEGORY(Array::ConstReverseIterator)
	{
		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy(std::move(it));
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = it;
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = std::move(it);
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crend();
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
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crend();
			EXPECT_TRUE(it - 3 == test.crbegin());
			EXPECT_TRUE(it - 2 == test.crbegin() + 1);
			EXPECT_TRUE(it - 1 == test.crbegin() + 2);
		}

		TEST("Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.crbegin());
			EXPECT_TRUE(test.crbegin() == it);
			EXPECT_TRUE(copy == test.crbegin());
			EXPECT_TRUE(test.crbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3>::ConstReverseIterator it = test.crbegin();
			Array<int, 3>::ConstReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != it));
			EXPECT_TRUE(!(copy != test.crbegin()));
			EXPECT_TRUE(!(test.crbegin() != copy));
		}
	}

	CATEGORY(Array)
	{
		TEST("Default Constructor")
		{
			Array<int, 3> test;
			EXPECT_TRUE(test.get_size() == 3);
		}

		TEST("Value Constructor")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test.at(0) == 5);
			EXPECT_TRUE(test.at(1) == 5);
			EXPECT_TRUE(test.at(2) == 5);
		}

		TEST("Initializer List Constructor")
		{
			Array<int, 3> test({ 0, 1, 2 });
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test.at(0) == 0);
			EXPECT_TRUE(test.at(1) == 1);
			EXPECT_TRUE(test.at(2) == 2);
		}

		TEST("Copy Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy(test);
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Move Constructor")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy(std::move(test));
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Copy Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy = test;
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Move Operator")
		{
			Array<int, 3> test(5);
			Array<int, 3> copy = std::move(test);
			EXPECT_TRUE(copy.get_size() == 3);
			EXPECT_TRUE(copy.at(0) == 5);
			EXPECT_TRUE(copy.at(1) == 5);
			EXPECT_TRUE(copy.at(2) == 5);
		}

		TEST("Index Operator")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test[0] == 5);
			EXPECT_TRUE(test[1] == 5);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_FAIL(test[3]);
		}

		TEST("Const Index Operator")
		{
			Array<int, 3> const test(5);
			EXPECT_TRUE(test[0] == 5);
			EXPECT_TRUE(test[1] == 5);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_FAIL(test[3]);
		}

		TEST("Get Size")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.get_size() == 3);
		}

		TEST("Get Data")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.get_data() != nullptr);
		}

		TEST("At")
		{
			Array<int, 3> test(5);
			EXPECT_TRUE(test.at(0) == 5);
			EXPECT_TRUE(test.at(1) == 5);
			EXPECT_TRUE(test.at(2) == 5);
			EXPECT_FAIL(test.at(3));
		}

		TEST("Const At")
		{
			Array<int, 3> const test(5);
			EXPECT_TRUE(test.at(0) == 5);
			EXPECT_TRUE(test.at(1) == 5);
			EXPECT_TRUE(test.at(2) == 5);
			EXPECT_FAIL(test.at(3));
		}

		TEST("Sub")
		{
			Array<int, 3> test(5);
			Array<int, 2> sub = test.sub<2>(0);
			EXPECT_TRUE(sub.get_size() == 2);
			EXPECT_TRUE(sub.at(0) == 5);
			EXPECT_TRUE(sub.at(1) == 5);
			EXPECT_FAIL(sub.at(2) == 5);
		}

		TEST("Find")
		{
			Array<int, 3> test({ 0, 1, 2 });
			EXPECT_TRUE(test.find(0) == test.begin());
			EXPECT_TRUE(test.find(1) == test.begin() + 1);
			EXPECT_TRUE(test.find(2) == test.begin() + 2);
			EXPECT_TRUE(test.find(3) == test.end());
		}

		TEST("Const Find")
		{
			Array<int, 3> const test({ 0, 1, 2 });
			EXPECT_TRUE(test.find(0) == test.cbegin());
			EXPECT_TRUE(test.find(1) == test.cbegin() + 1);
			EXPECT_TRUE(test.find(2) == test.cbegin() + 2);
			EXPECT_TRUE(test.find(3) == test.cend());
		}
	}
}