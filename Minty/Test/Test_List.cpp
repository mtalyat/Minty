#include "Test_List.h"
#include "Minty.h"

void test_List(Test& _test)
{
	CATEGORY(List::Iterator)
	{
		TEST("Copy Constructor")
		{
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			List<int>::Iterator copy(it);
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
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			List<int>::Iterator copy(std::move(it));
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
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			List<int>::Iterator copy = it;
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
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			List<int>::Iterator copy = std::move(it);
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
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
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
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin() + 2;
			EXPECT_TRUE(*(it - 1) == 5);
			EXPECT_TRUE(*(it - 2) == 5);
			EXPECT_TRUE(it - 2 == test.begin());
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(it == test.begin());
			it = test.begin() + 2;
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(it == test.begin());
		}

		TEST("Addition Operator")
		{
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin() + 2;
			EXPECT_TRUE(it - 2 == test.begin());
			EXPECT_TRUE(it - 1 == test.begin() + 1);
			EXPECT_TRUE(it - 0 == test.begin() + 2);
		}

		TEST("Equal Operator")
		{
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			List<int>::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			List<int> test(3, 5);
			List<int>::Iterator it = test.begin();
			List<int>::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(List::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			List<int>::ConstIterator copy(it);
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
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			List<int>::ConstIterator copy(std::move(it));
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
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			List<int>::ConstIterator copy = it;
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
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			List<int>::ConstIterator copy = std::move(it);
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
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
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
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin() + 2;
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(it == test.begin());
			it = test.begin() + 2;
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(it == test.begin());
		}

		TEST("Addition Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin() + 2;
			EXPECT_TRUE(it - 2 == test.begin());
			EXPECT_TRUE(it - 1 == test.begin() + 1);
			EXPECT_TRUE(it - 0 == test.begin() + 2);
		}

		TEST("Equal Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			List<int>::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstIterator it = test.begin();
			List<int>::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(List::ReverseIterator)
	{
		TEST("Copy Constructor")
		{
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			List<int>::ReverseIterator copy(it);
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
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			List<int>::ReverseIterator copy(std::move(it));
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
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			List<int>::ReverseIterator copy = it;
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
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			List<int>::ReverseIterator copy = std::move(it);
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
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
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
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin() + 2;
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(it == test.rbegin());
			it = test.rbegin() + 2;
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(it == test.rbegin());
		}

		TEST("Addition Operator")
		{
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin() + 2;
			EXPECT_TRUE(it - 2 == test.rbegin());
			EXPECT_TRUE(it - 1 == test.rbegin() + 1);
			EXPECT_TRUE(it - 0 == test.rbegin() + 2);
		}

		TEST("Equal Operator")
		{
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			List<int>::ReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.rbegin());
			EXPECT_TRUE(test.rbegin() == it);
			EXPECT_TRUE(copy == test.rbegin());
			EXPECT_TRUE(test.rbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			List<int> test(3, 5);
			List<int>::ReverseIterator it = test.rbegin();
			List<int>::ReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != it));
			EXPECT_TRUE(!(copy != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != copy));
		}
	}

	CATEGORY(List::ConstReverseIterator)
	{
		TEST("Copy Constructor")
		{
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			List<int>::ConstReverseIterator copy(it);
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
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			List<int>::ConstReverseIterator copy(std::move(it));
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
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			List<int>::ConstReverseIterator copy = it;
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
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			List<int>::ConstReverseIterator copy = std::move(it);
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
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Increment Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
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
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin() + 2;
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(*--it == 5);
			EXPECT_TRUE(it == test.rbegin());
			it = test.rbegin() + 2;
			it--;
			EXPECT_TRUE(*it-- == 5);
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(it == test.rbegin());
		}

		TEST("Addition Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			EXPECT_TRUE(*it == 5);
			EXPECT_TRUE(*(it + 1) == 5);
			EXPECT_TRUE(*(it + 2) == 5);
		}

		TEST("Subtraction Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin() + 2;
			EXPECT_TRUE(it - 2 == test.rbegin());
			EXPECT_TRUE(it - 1 == test.rbegin() + 1);
			EXPECT_TRUE(it - 0 == test.rbegin() + 2);
		}

		TEST("Equal Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			List<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.rbegin());
			EXPECT_TRUE(test.rbegin() == it);
			EXPECT_TRUE(copy == test.rbegin());
			EXPECT_TRUE(test.rbegin() == copy);
		}

		TEST("Not Equal Operator")
		{
			List<int> const test(3, 5);
			List<int>::ConstReverseIterator it = test.rbegin();
			List<int>::ConstReverseIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != it));
			EXPECT_TRUE(!(copy != test.rbegin()));
			EXPECT_TRUE(!(test.rbegin() != copy));
		}
	}

	CATEGORY(List)
	{
		TEST("Default Constructor")
		{
			List<int> test;
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Value Constructor")
		{
			List<int> test(10, 5);
			EXPECT_TRUE(test.get_size() == 10);
			for (Size i = 0; i < test.get_size(); i++)
			{
				EXPECT_TRUE(test[i] == 5);
			}

			List<int> test2(0, 0);
			EXPECT_TRUE(test2.get_size() == 0);
		}

		TEST("Initializer List Constructor")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.get_size() == 5);
			for (Size i = 0; i < test.get_size(); i++)
			{
				EXPECT_TRUE(test[i] == i);
			}

			List<int> test2({});
			EXPECT_TRUE(test2.get_size() == 0);
		}

		TEST("Copy Constructor")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> copy(test);
			EXPECT_TRUE(copy.get_size() == 5);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Move Constructor")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> copy(std::move(test));
			EXPECT_TRUE(copy.get_size() == 5);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Copy Operator")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> copy = test;
			EXPECT_TRUE(copy.get_size() == 5);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Move Operator")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> copy = std::move(test);
			EXPECT_TRUE(copy.get_size() == 5);
			for (Size i = 0; i < copy.get_size(); i++)
			{
				EXPECT_TRUE(copy[i] == i);
			}
		}

		TEST("Index Operator")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 2);
			EXPECT_TRUE(test[3] == 3);
			EXPECT_TRUE(test[4] == 4);
			EXPECT_FAIL(test[5]);
		}

		TEST("Const Index Operator")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 2);
			EXPECT_TRUE(test[3] == 3);
			EXPECT_TRUE(test[4] == 4);
			EXPECT_FAIL(test[5]);
		}

		TEST("Get Size")
		{
			List<int> test;
			EXPECT_TRUE(test.get_size() == 0);

			test.resize(5);
			EXPECT_TRUE(test.get_size() == 5);
		}

		TEST("Resize")
		{
			List<int> test;
			test.resize(5);
			EXPECT_TRUE(test.get_size() == 5);
			test.resize(10);
			EXPECT_TRUE(test.get_size() == 10);
			test.resize(0);
			EXPECT_TRUE(test.get_size() == 0);
			test.resize(20);
			EXPECT_TRUE(test.get_size() == 20);
		}

		TEST("Add Copy")
		{
			List<String> test;
			String str = "5";
			test.add(str);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == "5");
			str = "10";
			test.add(str);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[1] == "10");
		}

		TEST("Add Move")
		{
			List<String> test;
			String str = "5";
			test.add(std::move(str));
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == "5");
			str = "10";
			test.add(std::move(str));
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[1] == "10");
		}

		TEST("Add Range")
		{
			List<int> test;
			List<int> range({ 0, 1, 2, 3, 4 });
			test.add(range.begin(), range.end());
			EXPECT_TRUE(test.get_size() == 5);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 2);
			EXPECT_TRUE(test[3] == 3);
			EXPECT_TRUE(test[4] == 4);
		}

		TEST("Push Copy")
		{
			List<String> test;
			String str = "5";
			test.push(str);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == "5");
			str = "10";
			test.push(str);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[1] == "10");
		}

		TEST("Push Move")
		{
			List<String> test;
			String str = "5";
			test.push(std::move(str));
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == "5");
			str = "10";
			test.push(std::move(str));
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[1] == "10");
		}

		TEST("Insert Index Copy")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			test.insert(2, 5);
			EXPECT_TRUE(test.get_size() == 6);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_TRUE(test[3] == 2);
			EXPECT_TRUE(test[4] == 3);
			EXPECT_TRUE(test[5] == 4);
			test.insert(0, 6);
			EXPECT_TRUE(test.get_size() == 7);
			EXPECT_TRUE(test[0] == 6);
			EXPECT_TRUE(test[1] == 0);
			EXPECT_TRUE(test[2] == 1);
			EXPECT_TRUE(test[3] == 5);
			EXPECT_TRUE(test[4] == 2);
			EXPECT_TRUE(test[5] == 3);
			EXPECT_TRUE(test[6] == 4);
			test.insert(7, 7);
			EXPECT_TRUE(test.get_size() == 8);
			EXPECT_TRUE(test[0] == 6);
			EXPECT_TRUE(test[1] == 0);
			EXPECT_TRUE(test[2] == 1);
			EXPECT_TRUE(test[3] == 5);
			EXPECT_TRUE(test[4] == 2);
			EXPECT_TRUE(test[5] == 3);
			EXPECT_TRUE(test[6] == 4);
			EXPECT_TRUE(test[7] == 7);
		}

		TEST("Insert Index Move")
		{
			List<String> test({ "0", "1", "2", "3", "4" });
			String str = "5";
			test.insert(2, std::move(str));
			EXPECT_TRUE(test.get_size() == 6);
			EXPECT_TRUE(test[0] == "0");
			EXPECT_TRUE(test[1] == "1");
			EXPECT_TRUE(test[2] == "5");
			EXPECT_TRUE(test[3] == "2");
			EXPECT_TRUE(test[4] == "3");
			EXPECT_TRUE(test[5] == "4");
			str = "6";
			test.insert(0, std::move(str));
			EXPECT_TRUE(test.get_size() == 7);
			EXPECT_TRUE(test[0] == "6");
			EXPECT_TRUE(test[1] == "0");
			EXPECT_TRUE(test[2] == "1");
			EXPECT_TRUE(test[3] == "5");
			EXPECT_TRUE(test[4] == "2");
			EXPECT_TRUE(test[5] == "3");
			EXPECT_TRUE(test[6] == "4");
			str = "7";
			test.insert(7, std::move(str));
			EXPECT_TRUE(test.get_size() == 8);
			EXPECT_TRUE(test[0] == "6");
			EXPECT_TRUE(test[1] == "0");
			EXPECT_TRUE(test[2] == "1");
			EXPECT_TRUE(test[3] == "5");
			EXPECT_TRUE(test[4] == "2");
			EXPECT_TRUE(test[5] == "3");
			EXPECT_TRUE(test[6] == "4");
			EXPECT_TRUE(test[7] == "7");
		}

		TEST("Insert Iterator Copy")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> range({ 5, 6, 7 });
			test.insert(test.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(test.get_size() == 8);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_TRUE(test[3] == 6);
			EXPECT_TRUE(test[4] == 7);
			EXPECT_TRUE(test[5] == 2);
			EXPECT_TRUE(test[6] == 3);
			EXPECT_TRUE(test[7] == 4);
		}

		TEST("Insert Iterator Move")
		{
			List<String> test({ "0", "1", "2", "3", "4" });
			List<String> range({ "5", "6", "7" });
			test.insert(test.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(test.get_size() == 8);
			EXPECT_TRUE(test[0] == "0");
			EXPECT_TRUE(test[1] == "1");
			EXPECT_TRUE(test[2] == "5");
			EXPECT_TRUE(test[3] == "6");
			EXPECT_TRUE(test[4] == "7");
			EXPECT_TRUE(test[5] == "2");
			EXPECT_TRUE(test[6] == "3");
			EXPECT_TRUE(test[7] == "4");
		}

		TEST("Insert Index Range")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> range({ 5, 6, 7 });
			test.insert(2, range.begin(), range.end());
			EXPECT_TRUE(test.get_size() == 8);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_TRUE(test[3] == 6);
			EXPECT_TRUE(test[4] == 7);
			EXPECT_TRUE(test[5] == 2);
			EXPECT_TRUE(test[6] == 3);
			EXPECT_TRUE(test[7] == 4);
		}

		TEST("Insert Iterator Range")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> range({ 5, 6, 7 });
			test.insert(test.begin() + 2, range.begin(), range.end());
			EXPECT_TRUE(test.get_size() == 8);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 5);
			EXPECT_TRUE(test[3] == 6);
			EXPECT_TRUE(test[4] == 7);
			EXPECT_TRUE(test[5] == 2);
			EXPECT_TRUE(test[6] == 3);
			EXPECT_TRUE(test[7] == 4);
		}

		TEST("Remove Index")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			test.remove(2);
			EXPECT_TRUE(test.get_size() == 4);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 3);
			EXPECT_TRUE(test[3] == 4);
			test.remove(0);
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test[0] == 1);
			EXPECT_TRUE(test[1] == 3);
			EXPECT_TRUE(test[2] == 4);
			test.remove(2);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[0] == 1);
			EXPECT_TRUE(test[1] == 3);
			test.remove(1);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 1);
			test.remove(0);
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Remove Iterator")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			test.remove(test.begin() + 2);
			EXPECT_TRUE(test.get_size() == 4);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 3);
			EXPECT_TRUE(test[3] == 4);
			test.remove(test.begin());
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test[0] == 1);
			EXPECT_TRUE(test[1] == 3);
			EXPECT_TRUE(test[2] == 4);
			test.remove(test.begin() + 2);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[0] == 1);
			EXPECT_TRUE(test[1] == 3);
			test.remove(test.begin() + 1);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 1);
			test.remove(test.begin());
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Remove Index Range")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_FAIL(test.remove(0, 0));
			EXPECT_FAIL(test.remove(5, 1));
			EXPECT_FAIL(test.remove(0, 6));
			test.remove(1, 3);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 4);
			test.remove(0, 1);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 4);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 4);
			test.remove(0, 1);
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Remove Iterator Range")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_FAIL(test.remove(test.begin(), test.begin()));
			EXPECT_FAIL(test.remove(test.end(), test.end()));
			EXPECT_FAIL(test.remove(test.end(), test.begin()));
			test.remove(test.begin() + 1, test.begin() + 4);
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 4);
			test.remove(test.begin(), test.begin() + 1);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 4);
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 4);
			test.remove(test.begin(), test.begin() + 1);
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Pop")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			test.pop();
			EXPECT_TRUE(test.get_size() == 4);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 2);
			EXPECT_TRUE(test[3] == 3);
			test.pop();
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			EXPECT_TRUE(test[2] == 2);
			test.pop();
			EXPECT_TRUE(test.get_size() == 2);
			EXPECT_TRUE(test[0] == 0);
			EXPECT_TRUE(test[1] == 1);
			test.pop();
			EXPECT_TRUE(test.get_size() == 1);
			EXPECT_TRUE(test[0] == 0);
			test.pop();
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Is Empty")
		{
			List<int> test;
			EXPECT_TRUE(test.is_empty());
			test.add(0);
			EXPECT_TRUE(!test.is_empty());
			test.remove(0);
			EXPECT_TRUE(test.is_empty());
		}

		TEST("At")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.at(0) == 0);
			EXPECT_TRUE(test.at(1) == 1);
			EXPECT_TRUE(test.at(2) == 2);
			EXPECT_TRUE(test.at(3) == 3);
			EXPECT_TRUE(test.at(4) == 4);
			EXPECT_FAIL(test.at(5));
			test.at(0) = 5;
			EXPECT_TRUE(test.at(0) == 5);
		}

		TEST("Const At")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.at(0) == 0);
			EXPECT_TRUE(test.at(1) == 1);
			EXPECT_TRUE(test.at(2) == 2);
			EXPECT_TRUE(test.at(3) == 3);
			EXPECT_TRUE(test.at(4) == 4);
			EXPECT_FAIL(test.at(5));
		}

		TEST("Front")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.front() == 0);
			test.front() = 5;
			EXPECT_TRUE(test.front() == 5);
		}

		TEST("Const Front")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.front() == 0);
		}

		TEST("Back")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.back() == 4);
			test.back() = 5;
			EXPECT_TRUE(test.back() == 5);
		}

		TEST("Const Back")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.back() == 4);
		}

		TEST("Peek")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.peek() == 4);
			test.peek() = 5;
			EXPECT_TRUE(test.peek() == 5);
		}

		TEST("Const Peek")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.peek() == 4);
		}

		TEST("Sub")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			List<int> sub = test.sub(2, 2);
			EXPECT_TRUE(sub.get_size() == 2);
			EXPECT_TRUE(sub[0] == 2);
			EXPECT_TRUE(sub[1] == 3);
		}

		TEST("Find")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.find(0) == test.begin());
			EXPECT_TRUE(test.find(1) == test.begin() + 1);
			EXPECT_TRUE(test.find(2) == test.begin() + 2);
			EXPECT_TRUE(test.find(3) == test.begin() + 3);
			EXPECT_TRUE(test.find(4) == test.begin() + 4);
			EXPECT_TRUE(test.find(5) == test.end());
		}

		TEST("Const Find")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.find(0) == test.begin());
			EXPECT_TRUE(test.find(1) == test.begin() + 1);
			EXPECT_TRUE(test.find(2) == test.begin() + 2);
			EXPECT_TRUE(test.find(3) == test.begin() + 3);
			EXPECT_TRUE(test.find(4) == test.begin() + 4);
			EXPECT_TRUE(test.find(5) == test.end());
		}

		TEST("Contains")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.contains(0));
			EXPECT_TRUE(test.contains(1));
			EXPECT_TRUE(test.contains(2));
			EXPECT_TRUE(test.contains(3));
			EXPECT_TRUE(test.contains(4));
			EXPECT_TRUE(!test.contains(5));
		}

		TEST("Clear")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			test.clear();
			EXPECT_TRUE(test.get_size() == 0);
		}

		TEST("Begin")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*test.begin() == 0);
		}

		TEST("Const Begin")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*test.begin() == 0);
		}

		TEST("End")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.end() == test.begin() + 5);
		}

		TEST("Const End")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.end() == test.begin() + 5);
		}

		TEST("Reverse Begin")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*test.rbegin() == 4);
		}

		TEST("Reverse End")
		{
			List<int> test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.rend() == test.rbegin() + 5);
		}

		TEST("Const Reverse Begin")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(*test.rbegin() == 4);
		}

		TEST("Const Reverse End")
		{
			List<int> const test({ 0, 1, 2, 3, 4 });
			EXPECT_TRUE(test.rend() == test.rbegin() + 5);
		}
	}
}