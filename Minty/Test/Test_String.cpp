#include "Test_String.h"
#include "Minty.h"

void test_String(Test& _test)
{
	CATEGORY(String::Iterator)
	{
		TEST("Copy Constructor")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Constructor")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy(std::move(it));
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Copy Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = it;
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = std::move(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Dereference Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Increment Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Addition Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Equal Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			String test("abc");
			String::Iterator it = test.begin();
			String::Iterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(String::ConstIterator)
	{
		TEST("Copy Constructor")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			String::ConstIterator copy(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Constructor")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			String::ConstIterator copy(std::move(it));
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Copy Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			String::ConstIterator copy = it;
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			copy = it;
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Move Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			String::ConstIterator copy = std::move(it);
			EXPECT_TRUE(*copy == 'a');
			EXPECT_TRUE(*(copy + 1) == 'b');
			EXPECT_TRUE(*(copy + 2) == 'c');
			EXPECT_TRUE(copy + 3 == test.end());
			EXPECT_TRUE(*++copy == 'b');
			EXPECT_TRUE(*++copy == 'c');
			EXPECT_TRUE(++copy == test.end());
			it = test.begin();
			copy = std::move(it);
			EXPECT_TRUE(*copy++ == 'a');
			EXPECT_TRUE(*copy++ == 'b');
			EXPECT_TRUE(*copy++ == 'c');
			EXPECT_TRUE(copy == test.end());
		}

		TEST("Dereference Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Increment Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Addition Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Equal Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			String::ConstIterator copy = it;
			EXPECT_TRUE(it == copy);
			EXPECT_TRUE(copy == it);
			EXPECT_TRUE(it == test.begin());
			EXPECT_TRUE(test.begin() == it);
			EXPECT_TRUE(copy == test.begin());
			EXPECT_TRUE(test.begin() == copy);
		}

		TEST("Not Equal Operator")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			String::ConstIterator copy = it;
			EXPECT_TRUE(!(it != copy));
			EXPECT_TRUE(!(copy != it));
			EXPECT_TRUE(!(it != test.begin()));
			EXPECT_TRUE(!(test.begin() != it));
			EXPECT_TRUE(!(copy != test.begin()));
			EXPECT_TRUE(!(test.begin() != copy));
		}
	}

	CATEGORY(String)
	{
		TEST("Default Constructor")
		{
			String test;
			EXPECT_TRUE(test.get_capacity() == 0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() == nullptr);
		}

		TEST("Capacity Constructor")
		{
			String test(10);
			EXPECT_TRUE(test.get_capacity() == 10);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() != nullptr);
		}

		TEST("C String Constructor")
		{
			String test("Hello world!\n");

			EXPECT_TRUE(test.get_capacity() == 13);
			EXPECT_TRUE(test.get_size() == 13);
			EXPECT_TRUE(test.get_data() != nullptr);
			EXPECT_TRUE(test.get_data()[test.get_size()] == '\0');
		}

		TEST("Character Constructor")
		{
			String test('a', 3);

			EXPECT_TRUE(test.get_capacity() == 3);
			EXPECT_TRUE(test.get_size() == 3);
			EXPECT_TRUE(test.get_data() != nullptr);
			EXPECT_TRUE(test.get_data()[0] == 'a');
			EXPECT_TRUE(test.get_data()[1] == 'a');
			EXPECT_TRUE(test.get_data()[2] == 'a');
			EXPECT_TRUE(test.get_data()[test.get_size()] == '\0');
		}

		TEST("Copy Constructor")
		{
			String test("Hello world!\n");
			String copy(test);
			EXPECT_TRUE(copy.get_capacity() == test.get_capacity());
			EXPECT_TRUE(copy.get_size() == test.get_size());
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Move Constructor")
		{
			String test("Hello world!\n");
			String copy(std::move(test));
			EXPECT_TRUE(test.get_capacity() == 0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() == nullptr);
			EXPECT_TRUE(copy.get_capacity() == 13);
			EXPECT_TRUE(copy.get_size() == 13);
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Copy Operator")
		{
			String test("Hello world!\n");
			String copy = test;
			EXPECT_TRUE(copy.get_capacity() == test.get_capacity());
			EXPECT_TRUE(copy.get_size() == test.get_size());
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Move Operator")
		{
			String test("Hello world!\n");
			String copy = std::move(test);
			EXPECT_TRUE(test.get_capacity() == 0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_data() == nullptr);
			EXPECT_TRUE(copy.get_capacity() == 13);
			EXPECT_TRUE(copy.get_size() == 13);
			EXPECT_TRUE(copy.get_data() != nullptr);
		}

		TEST("Index Operator")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test[0] == 'H');
			EXPECT_TRUE(test[1] == 'e');
			EXPECT_TRUE(test[2] == 'l');
			EXPECT_TRUE(test[3] == 'l');
			EXPECT_TRUE(test[4] == 'o');
			EXPECT_TRUE(test[5] == ' ');
			EXPECT_TRUE(test[6] == 'w');
			EXPECT_TRUE(test[7] == 'o');
			EXPECT_TRUE(test[8] == 'r');
			EXPECT_TRUE(test[9] == 'l');
			EXPECT_TRUE(test[10] == 'd');
			EXPECT_TRUE(test[11] == '!');
			EXPECT_TRUE(test[12] == '\n');
			EXPECT_FAILURE(test[13]);
		}

		TEST("Equal Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(test == copy);

			copy = "bbbbbb";
			EXPECT_TRUE(!(test == copy));

			copy = "aaa";
			EXPECT_TRUE(test == copy);

			copy = "aaaa";
			EXPECT_TRUE(!(test == copy));
		}

		TEST("Not Equal Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(!(test != copy));

			copy = "bbbbbb";
			EXPECT_TRUE(test != copy);

			copy = "aaa";
			EXPECT_TRUE(!(test != copy));

			copy = "aaaa";
			EXPECT_TRUE(test != copy);
		}

		TEST("Less Than Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(!(test < copy));

			copy = "bbb";
			EXPECT_TRUE(test < copy);

			copy = "aaa";
			EXPECT_TRUE(!(test < copy));

			copy = "aaaa";
			EXPECT_TRUE(test < copy);

			copy = "aa";
			EXPECT_TRUE(!(test < copy));
		}

		TEST("Less Than Or Equal Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(test <= copy);

			copy = "bbb";
			EXPECT_TRUE(test <= copy);

			copy = "aaa";
			EXPECT_TRUE(test <= copy);

			copy = "aaaa";
			EXPECT_TRUE(test <= copy);

			copy = "aa";
			EXPECT_TRUE(!(test <= copy));
		}

		TEST("Greater Than Operator")
		{
			String test("aaa");
			String copy("aaa");
			EXPECT_TRUE(!(test > copy));

			copy = "bbb";
			EXPECT_TRUE(!(test > copy));

			copy = "aaa";
			EXPECT_TRUE(!(test > copy));

			copy = "ccc";
			EXPECT_TRUE(!(test > copy));

			copy = "aa";
			EXPECT_TRUE(test > copy);

			copy = "aaaa";
			EXPECT_TRUE(!(test > copy));
		}

		TEST("Greater Than Or Equal Operator")
		{
			String test("aaa\n");
			String copy("aaa\n");
			EXPECT_TRUE(test >= copy);

			copy = "bbb";
			EXPECT_TRUE(!(test >= copy));

			copy = "aaa";
			EXPECT_TRUE(test >= copy);

			copy = "ccc";
			EXPECT_TRUE(!(test >= copy));

			copy = "aa";
			EXPECT_TRUE(test >= copy);

			copy = "aaaa";
			EXPECT_TRUE(!(test >= copy));
		}

		TEST("Addition Operator")
		{
			String test("Hello ");
			String copy("world!\n");
			String result = test + copy;
			EXPECT_TRUE(result == "Hello world!\n");

			copy = "";
			result = test + copy;
			EXPECT_TRUE(result == "Hello ");

			test = "";
			result = test + copy;
			EXPECT_TRUE(result == "");
		}

		TEST("Stream Insertion Operator")
		{
			String test("Hello world!\n");
			{
				std::ostringstream stream;
				stream << test;
				EXPECT_TRUE(stream.str() == "Hello world!\n");
			}
			test = "";
			{
				std::ostringstream stream;
				stream << test;
				EXPECT_TRUE(stream.str() == "");
			}
		}

		TEST("Get Capacity")
		{
			String test(100);

			EXPECT_TRUE(test.get_capacity() == 100);
		}

		TEST("Get Size")
		{
			String test("Hello world!\n");

			EXPECT_TRUE(test.get_size() == 13);
		}

		TEST("Get Data")
		{
			String test("Hello world!\n");

			EXPECT_TRUE(test.get_data() != nullptr);
		}

		TEST("Reserve")
		{
			String test;

			test.reserve(0);
			EXPECT_TRUE(test.get_capacity() == 0);

			test.reserve(100);
			EXPECT_TRUE(test.get_capacity() == 100);

			test.reserve(10);
			EXPECT_TRUE(test.get_capacity() == 10);
		}

		TEST("Resize")
		{
			String test;

			test.resize(0);
			EXPECT_TRUE(test.get_size() == 0);
			EXPECT_TRUE(test.get_capacity() == 0);

			test.resize(100);
			EXPECT_TRUE(test.get_size() == 100);
			EXPECT_TRUE(test.get_capacity() == 100);

			test.resize(10);
			EXPECT_TRUE(test.get_size() == 10);
			EXPECT_TRUE(test.get_capacity() == 100);
		}

		TEST("Is Empty")
		{
			String test;
			EXPECT_TRUE(test.is_empty());

			test = "Hello world!\n";
			EXPECT_TRUE(!test.is_empty());
		}

		TEST("At")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.at(0) == 'H');
			EXPECT_TRUE(test.at(1) == 'e');
			EXPECT_TRUE(test.at(2) == 'l');
			EXPECT_TRUE(test.at(3) == 'l');
			EXPECT_TRUE(test.at(4) == 'o');
			EXPECT_TRUE(test.at(5) == ' ');
			EXPECT_TRUE(test.at(6) == 'w');
			EXPECT_TRUE(test.at(7) == 'o');
			EXPECT_TRUE(test.at(8) == 'r');
			EXPECT_TRUE(test.at(9) == 'l');
			EXPECT_TRUE(test.at(10) == 'd');
			EXPECT_TRUE(test.at(11) == '!');
			EXPECT_TRUE(test.at(12) == '\n');
			EXPECT_FAILURE(test.at(13));
		}

		TEST("Front")
		{
			String test("Hello world!\n");
			EXPECT_EQUAL(test.front(), 'H');

			test = "";
			EXPECT_FAILURE(test.front());
		}

		TEST("Back")
		{
			String test("Hello world!\n");
			EXPECT_EQUAL(test.back(), '\n');

			test = "";
			EXPECT_FAILURE(test.back());
		}

		TEST("Sub")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.sub(0, 5) == "Hello");
			EXPECT_TRUE(test.sub(6, 5) == "world");
			EXPECT_TRUE(test.sub(12, 1) == "\n");
			EXPECT_FAILURE(test.sub(13, 1));
		}

		TEST("Find")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.find("Hello") == 0);
			EXPECT_TRUE(test.find("world") == 6);
			EXPECT_TRUE(test.find("\n") == 12);
			EXPECT_TRUE(test.find("Hello world!\n") == 0);
			EXPECT_TRUE(test.find("aaa") == INVALID_INDEX);
			EXPECT_TRUE(test.find("") == INVALID_INDEX);

			test = "";
			EXPECT_TRUE(test.find("aaa") == INVALID_INDEX);
		}

		TEST("Contains")
		{
			String test("Hello world!\n");
			EXPECT_TRUE(test.contains("Hello"));
			EXPECT_TRUE(test.contains("world"));
			EXPECT_TRUE(test.contains("\n"));
			EXPECT_TRUE(test.contains("Hello world!\n"));
			EXPECT_TRUE(!test.contains("aaa"));
			EXPECT_TRUE(!test.contains(""));

			test = "";
			EXPECT_TRUE(!test.contains("aaa"));
		}

		TEST("Begin/End")
		{
			String test("abc");
			String::Iterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}

		TEST("Const Begin/End")
		{
			String const test("abc");
			String::ConstIterator it = test.begin();
			EXPECT_TRUE(*it == 'a');
			EXPECT_TRUE(*(it + 1) == 'b');
			EXPECT_TRUE(*(it + 2) == 'c');
			EXPECT_TRUE(it + 3 == test.end());
			EXPECT_TRUE(*++it == 'b');
			EXPECT_TRUE(*++it == 'c');
			EXPECT_TRUE(++it == test.end());
			it = test.begin();
			EXPECT_TRUE(*it++ == 'a');
			EXPECT_TRUE(*it++ == 'b');
			EXPECT_TRUE(*it++ == 'c');
			EXPECT_TRUE(it == test.end());
		}
	}

}