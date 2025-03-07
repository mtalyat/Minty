#include "Test_Map.h"
#include "Minty.h"

void test_Map(Test& _test)
{
	CATEGORY(Map::Iterator)
	{
		TEST("Dereference Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			Map<int, int>::Iterator it = map.begin();
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)));
			++it;
			EXPECT_FAIL(*it);
		}

		TEST("Member Access Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			Map<int, int>::Iterator it = map.begin();
			EXPECT_TRUE(it->first == 0);
			EXPECT_TRUE(it->second == 0);
			++it;
			EXPECT_FAIL(it->first);
			EXPECT_FAIL(it->second);
		}

		TEST("Increment Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::Iterator it = map.begin();
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_FAIL(*it);
		}

		TEST("Addition Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::Iterator it = map.begin();
			EXPECT_TRUE((*(it + 0) == Pair<int, int>(0, 0)) || (*(it + 0) == Pair<int, int>(1, 1)));
			EXPECT_TRUE((*(it + 1) == Pair<int, int>(0, 0)) || (*(it + 1) == Pair<int, int>(1, 1)));
			EXPECT_FAIL(*(it + 2));
			EXPECT_TRUE(it + 2 == map.end());
		}

		TEST("Equal Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::Iterator it = map.begin();
			Map<int, int>::Iterator it2 = map.begin();
			EXPECT_TRUE(it == it2);
			++it;
			EXPECT_TRUE(!(it == it2));
		}

		TEST("Not Equal Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::Iterator it = map.begin();
			Map<int, int>::Iterator it2 = map.begin();
			EXPECT_TRUE(!(it != it2));
			++it;
			EXPECT_TRUE(it != it2);
		}
	}

	CATEGORY(Map::ConstIterator)
	{
		TEST("Dereference Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			Map<int, int>::ConstIterator it = map.cbegin();
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)));
			++it;
			EXPECT_FAIL(*it);
		}

		TEST("Member Access Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			Map<int, int>::ConstIterator it = map.cbegin();
			EXPECT_TRUE(it->first == 0);
			EXPECT_TRUE(it->second == 0);
			++it;
			EXPECT_FAIL(it->first);
			EXPECT_FAIL(it->second);
		}

		TEST("Increment Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::ConstIterator it = map.cbegin();
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_FAIL(*it);
		}

		TEST("Addition Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::ConstIterator it = map.cbegin();
			EXPECT_TRUE((*(it + 0) == Pair<int, int>(0, 0)) || (*(it + 0) == Pair<int, int>(1, 1)));
			EXPECT_TRUE((*(it + 1) == Pair<int, int>(0, 0)) || (*(it + 1) == Pair<int, int>(1, 1)));
			EXPECT_FAIL(*(it + 2));
			EXPECT_TRUE(it + 2 == map.cend());
		}

		TEST("Equal Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::ConstIterator it = map.cbegin();
			Map<int, int>::ConstIterator it2 = map.cbegin();
			EXPECT_TRUE(it == it2);
			++it;
			EXPECT_TRUE(!(it == it2));
		}

		TEST("Not Equal Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::ConstIterator it = map.cbegin();
			Map<int, int>::ConstIterator it2 = map.cbegin();
			EXPECT_TRUE(!(it != it2));
			++it;
			EXPECT_TRUE(it != it2);
		}
	}

	CATEGORY(Map)
	{
		TEST("Default Constructor")
		{
			Map<int, int> map;
			EXPECT_TRUE(map.get_capacity() == 0);
			EXPECT_TRUE(map.get_size() == 0);
		}

		TEST("Capacity Constructor")
		{
			Map<int, int> map(10);
			EXPECT_TRUE(map.get_capacity() == 10);
			EXPECT_TRUE(map.get_size() == 0);
			Map<int, int> map2(0);
			EXPECT_TRUE(map2.get_capacity() == 0);
			EXPECT_TRUE(map2.get_size() == 0);
		}

		TEST("Initializer List Constructor")
		{
			Map<int, int> map({ {0, 0}, {1, 1}, {2, 2} });
			EXPECT_TRUE(map.get_capacity() >= 3);
			EXPECT_TRUE(map.get_size() == 3);
			EXPECT_TRUE(map[0] == 0);
			EXPECT_TRUE(map[1] == 1);
			EXPECT_TRUE(map[2] == 2);
		}

		TEST("Copy Constructor")
		{
			Map<int, int> map({ {0, 0}, {1, 1}, {2, 2} });
			Map<int, int> map2(map);
			EXPECT_TRUE(map2.get_capacity() >= 3);
			EXPECT_TRUE(map2.get_size() == 3);
			EXPECT_TRUE(map2[0] == 0);
			EXPECT_TRUE(map2[1] == 1);
			EXPECT_TRUE(map2[2] == 2);
		}

		TEST("Move Constructor")
		{
			Map<int, int> map({ {0, 0}, {1, 1}, {2, 2} });
			Map<int, int> map2(std::move(map));
			EXPECT_TRUE(map2.get_capacity() >= 3);
			EXPECT_TRUE(map2.get_size() == 3);
			EXPECT_TRUE(map2[0] == 0);
			EXPECT_TRUE(map2[1] == 1);
			EXPECT_TRUE(map2[2] == 2);
		}

		TEST("Copy Assignment Operator")
		{
			Map<int, int> map({ {0, 0}, {1, 1}, {2, 2} });
			Map<int, int> map2;
			map2 = map;
			EXPECT_TRUE(map2.get_capacity() >= 3);
			EXPECT_TRUE(map2.get_size() == 3);
			EXPECT_TRUE(map2[0] == 0);
			EXPECT_TRUE(map2[1] == 1);
			EXPECT_TRUE(map2[2] == 2);
		}

		TEST("Move Assignment Operator")
		{
			Map<int, int> map({ {0, 0}, {1, 1}, {2, 2} });
			Map<int, int> map2;
			map2 = std::move(map);
			EXPECT_TRUE(map2.get_capacity() >= 3);
			EXPECT_TRUE(map2.get_size() == 3);
			EXPECT_TRUE(map2[0] == 0);
			EXPECT_TRUE(map2[1] == 1);
			EXPECT_TRUE(map2[2] == 2);
		}

		TEST("Index Operator")
		{
			Map<int, int> map;
			EXPECT_SUCCESS(map[0] = 0);
			EXPECT_SUCCESS(map[1] = 1);
			EXPECT_SUCCESS(map[2] = 3);
			EXPECT_SUCCESS(map[2] = 2);
			EXPECT_TRUE(map.get_capacity() >= 3);
			EXPECT_TRUE(map.get_size() == 3);
			EXPECT_TRUE(map[0] == 0);
			EXPECT_TRUE(map[1] == 1);
			EXPECT_TRUE(map[2] == 2);
		}

		TEST("Const Index Operator")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			const Map<int, int>& map2 = map;
			EXPECT_TRUE(map2[0] == 0);
			EXPECT_TRUE(map2[1] == 1);
			EXPECT_TRUE(map2[2] == 2);
		}

		TEST("Get Capacity")
		{
			Map<int, int> map;
			EXPECT_TRUE(map.get_capacity() == 0);
			map[0] = 0;
			EXPECT_TRUE(map.get_capacity() >= 1);
			map[1] = 1;
			EXPECT_TRUE(map.get_capacity() >= 2);
			map[2] = 2;
			EXPECT_TRUE(map.get_capacity() >= 3);
		}

		TEST("Get Size")
		{
			Map<int, int> map;
			EXPECT_TRUE(map.get_size() == 0);
			map[0] = 0;
			EXPECT_TRUE(map.get_size() == 1);
			map[1] = 1;
			EXPECT_TRUE(map.get_size() == 2);
			map[2] = 2;
			EXPECT_TRUE(map.get_size() == 3);
		}

		TEST("Reserve")
		{
			Map<int, int> map;
			map.reserve(10);
			EXPECT_TRUE(map.get_capacity() >= 10);
			EXPECT_TRUE(map.get_size() == 0);
			map[0] = 0;
			map.reserve(5);
			EXPECT_TRUE(map.get_capacity() >= 10);
			EXPECT_TRUE(map.get_size() == 1);
		}

		TEST("Add Copy")
		{
			Map<String, String> map;
			String str = "0";
			map.add("0", str);
			str = "1";
			map.add("1", str);
			EXPECT_TRUE(map.get_capacity() >= 2);
			EXPECT_TRUE(map.get_size() == 2);
			EXPECT_TRUE(map["0"] == "0");
			EXPECT_TRUE(map["1"] == "1");
			EXPECT_FAIL(map.add("0", "2"));
		}

		TEST("Add Move")
		{
			Map<String, String> map;
			String str = "0";
			map.add("0", std::move(str));
			str = "1";
			map.add("1", std::move(str));
			EXPECT_TRUE(map.get_capacity() >= 2);
			EXPECT_TRUE(map.get_size() == 2);
			EXPECT_TRUE(map["0"] == "0");
			EXPECT_TRUE(map["1"] == "1");
			str = "2";
			EXPECT_FAIL(map.add("0", std::move(str)));
		}

		TEST("Remove")
		{
			Map<int, int> map;
			EXPECT_TRUE(map.remove(0) == false);
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			EXPECT_TRUE(map.remove(3) == false);
			map.remove(1);
			EXPECT_TRUE(map.get_capacity() >= 2);
			EXPECT_TRUE(map.get_size() == 2);
			EXPECT_TRUE(map[0] == 0);
			EXPECT_TRUE(map[2] == 2);
			map.remove(0);
			EXPECT_TRUE(map.get_capacity() >= 2);
			EXPECT_TRUE(map.get_size() == 1);
			EXPECT_TRUE(map[2] == 2);
			map.remove(2);
			EXPECT_TRUE(map.get_capacity() >= 2);
			EXPECT_TRUE(map.get_size() == 0);
		}

		TEST("Is Empty")
		{
			Map<int, int> map;
			EXPECT_TRUE(map.is_empty());
			map[0] = 0;
			EXPECT_TRUE(!map.is_empty());
			map.remove(0);
			EXPECT_TRUE(map.is_empty());
		}

		TEST("At")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			EXPECT_TRUE(map.at(0) == 0);
			EXPECT_TRUE(map.at(1) == 1);
			EXPECT_TRUE(map.at(2) == 2);
			EXPECT_FAIL(map.at(3));
		}

		TEST("Const At")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			const Map<int, int>& map2 = map;
			EXPECT_TRUE(map2.at(0) == 0);
			EXPECT_TRUE(map2.at(1) == 1);
			EXPECT_TRUE(map2.at(2) == 2);
			EXPECT_FAIL(map2.at(3));
		}

		TEST("Find")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			EXPECT_TRUE(map.find(0) != map.end());
			EXPECT_TRUE(map.find(1) != map.end());
			EXPECT_TRUE(map.find(2) != map.end());
			EXPECT_TRUE(map.find(3) == map.end());
		}

		TEST("Const Find")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			const Map<int, int>& map2 = map;
			EXPECT_TRUE(map2.find(0) != map2.cend());
			EXPECT_TRUE(map2.find(1) != map2.cend());
			EXPECT_TRUE(map2.find(2) != map2.cend());
			EXPECT_TRUE(map2.find(3) == map2.cend());
		}

		TEST("Contains")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			EXPECT_TRUE(map.contains(0));
			EXPECT_TRUE(map.contains(1));
			EXPECT_TRUE(map.contains(2));
			EXPECT_TRUE(!map.contains(3));
		}

		TEST("Clear")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;
			map.clear();
			EXPECT_TRUE(map.get_capacity() >= 3);
			EXPECT_TRUE(map.get_size() == 0);
		}

		TEST("Begin")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::Iterator it = map.begin();
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_FAIL(*it);
		}

		TEST("End")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::Iterator it = map.begin() + 2;
			EXPECT_TRUE(it == map.end());
		}

		TEST("Const Begin")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::ConstIterator it = map.cbegin();
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_TRUE((*it == Pair<int, int>(0, 0)) || (*it == Pair<int, int>(1, 1)));
			++it;
			EXPECT_FAIL(*it);
		}

		TEST("Const End")
		{
			Map<int, int> map;
			map[0] = 0;
			map[1] = 1;
			Map<int, int>::ConstIterator it = map.cbegin() + 2;
			EXPECT_TRUE(it == map.cend());
		}
	}
}
