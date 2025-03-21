#include "Test_Set.h"
#include "Minty.h"

void test_Set(Test& _test)
{
	CATEGORY(Set::Iterator)
	{
		TEST("Dereference Operator")
		{
			Set<int> set;
			set.add(0);
			Set<int>::Iterator it = set.begin();
			EXPECT_TRUE((*it == 0));
			++it;
			EXPECT_FAILURE(*it);
		}

		TEST("Member Access Operator")
		{
			Set<String> set;
			set.add("0");
			Set<String>::Iterator it = set.begin();
			EXPECT_TRUE(it->get_size() == 1);
			++it;
			EXPECT_FAILURE(it->get_size());
		}

		TEST("Increment Operator")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			Set<int>::Iterator it = set.begin();
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_FAILURE(*it);
		}

		TEST("Addition Operator")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			Set<int>::Iterator it = set.begin();
			EXPECT_TRUE((*(it + 0) == 0) || (*(it + 0) == 1));
			EXPECT_TRUE((*(it + 1) == 0) || (*(it + 1) == 1));
			EXPECT_FAILURE(*(it + 2));
			EXPECT_TRUE(it + 2 == set.end());
		}

		TEST("Equal Operator")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			Set<int>::Iterator it = set.begin();
			Set<int>::Iterator it2 = set.begin();
			EXPECT_TRUE(it == it2);
			++it;
			EXPECT_TRUE(!(it == it2));
		}

		TEST("Not Equal Operator")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			Set<int>::Iterator it = set.begin();
			Set<int>::Iterator it2 = set.begin();
			EXPECT_TRUE(!(it != it2));
			++it;
			EXPECT_TRUE(it != it2);
		}
	}

	CATEGORY(Set::ConstIterator)
	{
		TEST("Dereference Operator")
		{
			Set<int> const set{ 0 };
			Set<int>::ConstIterator it = set.begin();
			EXPECT_TRUE((*it == 0));
			++it;
			EXPECT_FAILURE(*it);
		}

		TEST("Member Access Operator")
		{
			Set<String> const set{ "0" };
			Set<String>::ConstIterator it = set.begin();
			EXPECT_TRUE(it->get_size() == 1);
			++it;
			EXPECT_FAILURE(it->get_size());
		}

		TEST("Increment Operator")
		{
			Set<int> const set{ 0, 1 };
			Set<int>::ConstIterator it = set.begin();
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_FAILURE(*it);
		}

		TEST("Addition Operator")
		{
			Set<int> const set{ 0, 1 };
			Set<int>::ConstIterator it = set.begin();
			EXPECT_TRUE((*(it + 0) == 0) || (*(it + 0) == 1));
			EXPECT_TRUE((*(it + 1) == 0) || (*(it + 1) == 1));
			EXPECT_FAILURE(*(it + 2));
			EXPECT_TRUE(it + 2 == set.end());
		}

		TEST("Equal Operator")
		{
			Set<int> const set{ 0, 1 };
			Set<int>::ConstIterator it = set.begin();
			Set<int>::ConstIterator it2 = set.begin();
			EXPECT_TRUE(it == it2);
			++it;
			EXPECT_TRUE(!(it == it2));
		}

		TEST("Not Equal Operator")
		{
			Set<int> const set{ 0, 1 };
			Set<int>::ConstIterator it = set.begin();
			Set<int>::ConstIterator it2 = set.begin();
			EXPECT_TRUE(!(it != it2));
			++it;
			EXPECT_TRUE(it != it2);
		}
	}

	CATEGORY(Set)
	{
		TEST("Default Constructor")
		{
			Set<int> set;
			EXPECT_TRUE(set.get_capacity() == 0);
			EXPECT_TRUE(set.get_size() == 0);
		}

		TEST("Capacity Constructor")
		{
			Set<int> set(10);
			EXPECT_TRUE(set.get_capacity() == 10);
			EXPECT_TRUE(set.get_size() == 0);
			Set<int> set2(0);
			EXPECT_TRUE(set2.get_capacity() == 0);
			EXPECT_TRUE(set2.get_size() == 0);
		}

		TEST("Initializer List Constructor")
		{
			Set<int> set({ 0, 1, 2 });
			EXPECT_TRUE(set.get_capacity() >= 3);
			EXPECT_TRUE(set.get_size() == 3);
			EXPECT_TRUE(set.contains(0));
			EXPECT_TRUE(set.contains(1));
			EXPECT_TRUE(set.contains(2));
		}

		TEST("Copy Constructor")
		{
			Set<int> set({ 0, 1, 2 });
			Set<int> set2(set);
			EXPECT_TRUE(set2.get_capacity() >= 3);
			EXPECT_TRUE(set2.get_size() == 3);
			EXPECT_TRUE(set2.contains(0));
			EXPECT_TRUE(set2.contains(1));
			EXPECT_TRUE(set2.contains(2));
		}

		TEST("Move Constructor")
		{
			Set<int> set({ 0, 1, 2 });
			Set<int> set2(std::move(set));
			EXPECT_TRUE(set2.get_capacity() >= 3);
			EXPECT_TRUE(set2.get_size() == 3);
			EXPECT_TRUE(set2.contains(0));
			EXPECT_TRUE(set2.contains(1));
			EXPECT_TRUE(set2.contains(2));
		}

		TEST("Copy Assignment Operator")
		{
			Set<int> set({ 0, 1, 2 });
			Set<int> set2;
			set2 = set;
			EXPECT_TRUE(set2.get_capacity() >= 3);
			EXPECT_TRUE(set2.get_size() == 3);
			EXPECT_TRUE(set2.contains(0));
			EXPECT_TRUE(set2.contains(1));
			EXPECT_TRUE(set2.contains(2));
		}

		TEST("Move Assignment Operator")
		{
			Set<int> set({ 0, 1, 2 });
			Set<int> set2;
			set2 = std::move(set);
			EXPECT_TRUE(set2.get_capacity() >= 3);
			EXPECT_TRUE(set2.get_size() == 3);
			EXPECT_TRUE(set2.contains(0));
			EXPECT_TRUE(set2.contains(1));
			EXPECT_TRUE(set2.contains(2));
		}

		TEST("Index Operator")
		{
			Set<int> set;
			EXPECT_SUCCESS(set.add(0));
			EXPECT_SUCCESS(set.add(1));
			EXPECT_SUCCESS(set.add(2));
			EXPECT_SUCCESS(set.add(2));
			EXPECT_TRUE(set.get_capacity() >= 3);
			EXPECT_TRUE(set.get_size() == 3);
			EXPECT_TRUE(set.contains(0));
			EXPECT_TRUE(set.contains(1));
			EXPECT_TRUE(set.contains(2));
		}

		TEST("Const Index Operator")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			set.add(2);
			const Set<int>& set2 = set;
			EXPECT_TRUE(set2.contains(0));
			EXPECT_TRUE(set2.contains(1));
			EXPECT_TRUE(set2.contains(2));
		}

		TEST("Get Capacity")
		{
			Set<int> set;
			EXPECT_TRUE(set.get_capacity() == 0);
			set.add(0);
			EXPECT_TRUE(set.get_capacity() >= 1);
			set.add(1);
			EXPECT_TRUE(set.get_capacity() >= 2);
			set.add(2);
			EXPECT_TRUE(set.get_capacity() >= 3);
		}

		TEST("Get Size")
		{
			Set<int> set;
			EXPECT_TRUE(set.get_size() == 0);
			set.add(0);
			EXPECT_TRUE(set.get_size() == 1);
			set.add(1);
			EXPECT_TRUE(set.get_size() == 2);
			set.add(2);
			EXPECT_TRUE(set.get_size() == 3);
		}

		TEST("Reserve")
		{
			Set<int> set;
			set.reserve(10);
			EXPECT_TRUE(set.get_capacity() >= 10);
			EXPECT_TRUE(set.get_size() == 0);
			set.add(0);
			set.reserve(5);
			EXPECT_TRUE(set.get_capacity() >= 10);
			EXPECT_TRUE(set.get_size() == 1);
		}

		TEST("Add")
		{
			Set<String> set;
			String str = "0";
			EXPECT_TRUE(set.add(str) == true);
			str = "1";
			EXPECT_TRUE(set.add(str) == true);
			EXPECT_TRUE(set.get_capacity() >= 2);
			EXPECT_TRUE(set.get_size() == 2);
			EXPECT_TRUE(set.contains("0"));
			EXPECT_TRUE(set.contains("1"));
			EXPECT_TRUE(set.add("0") == false);
		}

		TEST("Remove")
		{
			Set<int> set;
			EXPECT_TRUE(set.remove(0) == false);
			set.add(0);
			set.add(1);
			set.add(2);
			EXPECT_TRUE(set.remove(3) == false);
			EXPECT_TRUE(set.remove(1) == true);
			EXPECT_TRUE(set.get_capacity() >= 2);
			EXPECT_TRUE(set.get_size() == 2);
			EXPECT_TRUE(set.contains(0));
			EXPECT_TRUE(set.contains(2));
			EXPECT_TRUE(set.remove(0) == true);
			EXPECT_TRUE(set.get_capacity() >= 2);
			EXPECT_TRUE(set.get_size() == 1);
			EXPECT_TRUE(set.contains(2));
			EXPECT_TRUE(set.remove(2) == true);
			EXPECT_TRUE(set.get_capacity() >= 2);
			EXPECT_TRUE(set.get_size() == 0);
		}

		TEST("Is Empty")
		{
			Set<int> set;
			EXPECT_TRUE(set.is_empty());
			set.add(0);
			EXPECT_TRUE(!set.is_empty());
			set.remove(0);
			EXPECT_TRUE(set.is_empty());
		}

		TEST("Find")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			set.add(2);
			EXPECT_TRUE(set.find(0) != set.end());
			EXPECT_TRUE(set.find(1) != set.end());
			EXPECT_TRUE(set.find(2) != set.end());
			EXPECT_TRUE(set.find(3) == set.end());
		}

		TEST("Const Find")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			set.add(2);
			const Set<int>& set2 = set;
			EXPECT_TRUE(set2.find(0) != set2.end());
			EXPECT_TRUE(set2.find(1) != set2.end());
			EXPECT_TRUE(set2.find(2) != set2.end());
			EXPECT_TRUE(set2.find(3) == set2.end());
		}

		TEST("Contains")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			set.add(2);
			EXPECT_TRUE(set.contains(0));
			EXPECT_TRUE(set.contains(1));
			EXPECT_TRUE(set.contains(2));
			EXPECT_TRUE(!set.contains(3));
		}

		TEST("Clear")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			set.add(2);
			set.clear();
			EXPECT_TRUE(set.get_capacity() >= 3);
			EXPECT_TRUE(set.get_size() == 0);
		}

		TEST("Begin")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			Set<int>::Iterator it = set.begin();
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_FAILURE(*it);
			Set<int> set2;
			EXPECT_TRUE(set2.begin() == set2.end());
		}

		TEST("End")
		{
			Set<int> set;
			set.add(0);
			set.add(1);
			Set<int>::Iterator it = set.begin() + 2;
			EXPECT_TRUE(it == set.end());
			Set<int> set2;
			EXPECT_TRUE(set2.begin() == set2.end());
		}

		TEST("Const Begin")
		{
			Set<int> const set{ 0, 1 };
			Set<int>::ConstIterator it = set.begin();
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_TRUE((*it == 0) || (*it == 1));
			++it;
			EXPECT_FAILURE(*it);
			Set<int> const set2;
			EXPECT_TRUE(set2.begin() == set2.end());
		}

		TEST("Const End")
		{
			Set<int> const set{ 0, 1 };
			Set<int>::ConstIterator it = set.begin() + 2;
			EXPECT_TRUE(it == set.end());
			Set<int> const set2;
			EXPECT_TRUE(set2.begin() == set2.end());
		}
	}
}
